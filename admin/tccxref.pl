#!/usr/bin/perl
# ----------------------------------------------------------------
#
# how to run:
#
# - apply tcc xref patch to tcc.c and make
#
# run:
#   $ ./tcc -vvvv -D__inline= tcc.c -ldl > xref.out
#   $ perl admin/tccxref.pl xref.out main 
# or for instance to generate an xref for the preprocessor only:
#   $ perl admin/tccxref.pl xref.out next -- error warning expr_const
#
# If you have an IDE with an output window that can run these
#  commands, you can click the linenumbers to jump to the source.
#
#
# ----------------------------------------------------------------
# global variables

my $usage = "Usage: tccxref.pl output-from-tcc-vvvv start-symbol -- [exclude-sym ...]";

# file to parse
my $file;

# top symbol to start xref
my $sym;

# prune function tree at these functions (for example):
my $exclude_syms = {};

# array of all files
my @p_files = ();

# array of all global data
my @p_data = ();

# array of all functions
my @p_func = ();

# hash for functions/data with line-number and prototype
my $globals = {};

# hash for functions with their calls and variable refs
my $func_table = {};

# ----------------------------------------------------------------
# subroutines

sub parse_args {
    my $e;
    foreach $a (@ARGV) {
        if ($e) {
            $exclude_syms->{$a} = 1;
        } elsif ($a =~ "--") {
            $e = 1;
        } elsif ($file) {
            $sym = $a;
        } else {
            $file = $a;
        }
    }
    if (! $sym ) {
        print STDERR $usage,"\n";
        exit 1;
    }
}

sub ln_sort {
    my $l1 = $globals->{$a};
    my $l2 = $globals->{$b};
    return $l1->[2] <=> $l2->[2];
}

sub read_log {

    my ($fl) = @_;

    open INF, $fl or die "could not open for reading: $fl";
    my @dat = <INF>;
    close INF;

    my $index = 0;
    my $srcs = {};

    foreach $ln (@dat) {
        if ($ln =~ /^(\S\S[^\s:]+):(\d+): +(function|data) (\w+)/) {
            $file = $1;
            $line = $2;
            $f = $4;
            $index = $index + 1;

            if (! @{$srcs->{$file}} ) {
                if (open INF, $file) {
                    @{$srcs->{$file}} = <INF> ;
                    close INF;
                    push @p_files, $file;
                }
            }

            # scan sourcefile to get the prototype at $line
            my $proto = "";

            if ( @{$srcs->{$file}} ) {

                while ($line > 1) {
                    my $l = $line - 1;
                    my $s = $srcs->{$file}[$l];
                    if ( $s =~ /^\{/ ) {

                    } elsif ( $s =~ /^\s+(.+\S)\s*$/ ) {
                        $s = $1;
                        $proto = " $s$proto";

                    } elsif ( $s =~ /^(.+\S)\s*$/ ) {
                        $s = $1;
                        $proto = "$s$proto";
                        last;
                    }

                    $line = $line - 1;
                }

                # strip trailing comments
                if ( $proto =~ /^([^\/]+[^\/\s])\s*\/\*/ ) {
                    $proto = $1;
                }

                # strip trailing =
                if ( $proto =~ /^([^=]+[^=\s])\s*=/ ) {
                    $proto = $1;
                }

                # add ;
                if ( ! ($proto =~ /;\s*$/) ) {
                    $proto = "$proto;";
                }
            }

            # print "$file:$line: $f\t$proto\n";
            $globals->{$f} = [ $file, $line, $index, $proto ];
        }
    }

    my $calls, $refs, $rec;

    foreach $ln (@dat) {
        if ($ln =~ /^(\S\S[^\s:]+):(\d+): +(\w+) (\w+)/) {
            $f = $3;
            $a = $4;
            if ($f =~ "function") {
                push @p_func, $a;
                $rec = { REF => [], CALL => [] };
                $func_table{$a} = $rec;
                $calls = {};
                $refs = {};

            } elsif ($f =~ "data") {
                push @p_data, $a;

            } elsif (!$globals->{$a}) {
                # external function/data (from libc)

            } elsif ($f =~ "call") {
                if (!$calls->{$a}) {
                    $calls->{$a} = 1;
                    push @{$rec->{CALL}}, $a;
                }

            } elsif ($f =~ "ref") {
                if (!$refs->{$a}) {
                    $refs->{$a} = 1;
                    push @{$rec->{REF}}, $a;
                }
            }
        }
    }

    foreach $a (@p_func) {
        $rec = $func_table{$a};
        @{$rec->{REF}} = sort ln_sort @{$rec->{REF}};
        @{$rec->{CALL}} = sort ln_sort @{$rec->{CALL}};
    }

}

sub is_global {
    my ($f1) = @_;
    my $s1 = @{$globals->{$f1}}[0];
    foreach $f2 (@p_func) {
        my $s2 = @{$globals->{$f2}}[0];
        if (! ($s1 =~ $s2)) {
            my $rec = $func_table{$f2};
            foreach $a (@{$rec->{CALL}}) {
                if ($a =~ $f1) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

sub print_id {
    my ($func,$long) = @_;
    my ($file, $line, $index, $proto) = @{$globals->{$func}};
    if ($long) {
        print "$file:$line: $func - $proto\n";
    } else {
        print "$file:$line: $func\n";
    }
}

sub print_fn {
    my ($f) = @_;
    my $rec = $func_table{$f};

    #if (!(@{$rec->{CALL}} || @{$rec->{REF}})) {
    #    return;
    #}

    print "--------------------------------------\n";
    print_id($f,1);
    if (@{$rec->{REF}}) {
        print "\n\tref:\n";
        foreach $a (@{$rec->{REF}}) {
            print "\t\t$a\n";
            # print "\t\t"; print_id($a);
            if (!$refs->{$a}) {
                $refs->{$a} = 1;
                push @p_ref, $a;
            }
        }
    }

    if (@{$rec->{CALL}}) {
        print "\n\tcall:\n";
        foreach $a (@{$rec->{CALL}}) {
            print "\t\t$a\n";
            # print "\t\t"; print_id($a);
        }
    }

    print "\n";
    foreach $a (@{$rec->{CALL}}) {
        if (!$calls->{$a}) {
            $calls->{$a} = 1;
            push @p_call, $a;
            print_fn($a);
        }
    }
}

sub print_refs {
    my ($f,$excl) = @_;

    @p_call = ();
    @p_ref = ();
    $calls = $excl or {};
    $refs = {};

    print_fn($f);

    print "\n";
    print "-------------------------------------------------------------\n";
    print "all referenced globals from \"$f\" and its subroutines:\n";
    print "\n";
    print_id($f);

    $n = @p_ref;
    print "\nref ($n):\n\n";
    foreach $a (sort ln_sort @p_ref) {
        print_id($a);
    }

    $n = @p_call;
    print "\ncall ($n):\n\n";
    foreach $a (sort ln_sort @p_call) {
        print_id($a);
    }

    print "\n\n";
    foreach $src (@p_files) {
        $src =~ /(.+\/)?([^\/]+)/;
        my $s = $2;

        print "/* ------------ $s ------------ */\n";
        print "\n/* data: */\n";
        foreach $data (@p_data) {
            if ($refs->{$data}) {
                my ($file, $line, $index, $proto) = @{$globals->{$data}};
                if ($file =~ $src) {
                    my $g = is_global($data);
                    print "$g - $proto\n";
                }
            }
        }
        print "\n/* functions: */\n";
        foreach $func (@p_func) {
            if ($calls->{$func}) {
                my ($file, $line, $index, $proto) = @{$globals->{$func}};
                if ($file =~ $src) {
                    my $g = is_global($func);
                    print "$g - $proto\n";
                }
            }
        }
        print "\n";
    }
}

# ----------------------------------------------------------------
# do something

parse_args;
read_log($file);
print_refs($sym, $exclude_syms);
exit 0;

