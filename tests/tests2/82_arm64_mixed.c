// This program is designed to test some arm64-specific things, such as the
// calling convention, but should give the same results on any architecture.

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

struct s1 { char x[1]; } s1 = { "0" };
struct s2 { char x[2]; } s2 = { "12" };
struct s3 { char x[3]; } s3 = { "345" };
struct s4 { char x[4]; } s4 = { "6789" };
struct s5 { char x[5]; } s5 = { "abcde" };
struct s6 { char x[6]; } s6 = { "fghijk" };
struct s7 { char x[7]; } s7 = { "lmnopqr" };
struct s8 { char x[8]; } s8 = { "stuvwxyz" };
struct s9 { char x[9]; } s9 = { "ABCDEFGHI" };
struct s10 { char x[10]; } s10 = { "JKLMNOPQRS" };
struct s11 { char x[11]; } s11 = { "TUVWXYZ0123" };
struct s12 { char x[12]; } s12 = { "456789abcdef" };
struct s13 { char x[13]; } s13 = { "ghijklmnopqrs" };
struct s14 { char x[14]; } s14 = { "tuvwxyzABCDEFG" };
struct s15 { char x[15]; } s15 = { "HIJKLMNOPQRSTUV" };
struct s16 { char x[16]; } s16 = { "WXYZ0123456789ab" };
struct s17 { char x[17]; } s17 = { "cdefghijklmnopqrs" };

const char *format(const char *type)
{
    if(strcmp(type, "float") == 0)
        return "%.0f";
    else if(strcmp(type, "double") == 0)
        return "%.0f";
    else if(strcmp(type, "long double") == 0)
        return "%.0Lf";
    else if(strcmp(type, "int") == 0)
        return "%d";
    else if(strcmp(type, "long long") == 0)
        return "%lld";
}

#define S(major,minor,type1,type2,type3,type4,type5)                            \
    struct t_##major##00 { } t_##major##00 = { };                               \
    struct t_##major##11 { type1 a1; } t_##major##11 = { 100*major + 10 * 1 + 1 }; \
    struct t_##major##22 { type1 a1; type2 a2; } t_##major##2##2 = { 100*major + 10 * 2 + 1,100*major + 10 * 2 + 2 }; \
    struct t_##major##33 { type1 a1; type2 a2; type3 a3; } t_##major##3##3 = { 100*major + 10 * 3 + 1,100*major + 10 * 3 + 2,100*major + 10 * 3 + 3 }; \
    struct t_##major##44 { type1 a1; type2 a2; type3 a3; type4 a4; } t_##major##4##4 = { 100*major + 10 * 4 + 1,100*major + 10 * 4 + 2,100*major + 10 * 4 + 3,100*major + 10 * 4 + 4 }; \
    struct t_##major##55 { type1 a1; type2 a2; type3 a3; type4 a4; type5 a5; } t_##major##5##5 = { 100*major + 10 * 5 + 1,100*major + 10 * 5 + 2,100*major + 10 * 5 + 3,100*major + 10 * 5 + 4,100*major + 10 * 5 + 5 }; \
                                                                                \
void print_##major##0##0(struct t_##major##0##0 a1) {                           \
    printf("\n");                                                               \
}                                                                               \
                                                                                \
void print_##major##1##1(struct t_##major##1##1 a1) {                           \
    printf("%d [%s] = ", major##1##1, #type1);\
    printf(format(#type1), a1.a1);                                              \
    printf("\n");                                                               \
}                                                                               \
                                                                                \
void print_##major##2##2(struct t_##major##2##2 a5) {                           \
    printf("%d [%s] = ", major##2##1, #type1); \
    printf(format(#type1), a5.a1);                                              \
    printf(" ");                                                                \
    printf("%d [%s] = ", major##2##2, #type2);                                               \
    printf(format(#type2), a5.a2);                                              \
    printf("\n");                                                               \
}                                                                               \
                                                                                \
void print_##major##3##3(struct t_##major##3##3 a5) {                           \
    printf("%d [%s] = ", major##3##1, #type1);                                               \
    printf(format(#type1), a5.a1);                                              \
    printf(" ");                                                                \
    printf("%d [%s] = ", major##3##2, #type2);                                               \
    printf(format(#type2), a5.a2);                                              \
    printf(" ");                                                                \
    printf("%d [%s] = ", major##3##3, #type3);                                               \
    printf(format(#type3), a5.a3);                                              \
    printf("\n");                                                               \
}                                                                               \
                                                                                \
void print_##major##4##4(struct t_##major##4##4 a5) {                           \
    printf("%d [%s] = ", major##4##1, #type1);                                               \
    printf(format(#type1), a5.a1);                                              \
    printf(" ");                                                                \
    printf("%d [%s] = ", major##4##2, #type2);                                               \
    printf(format(#type2), a5.a2);                                              \
    printf(" ");                                                                \
    printf("%d [%s] = ", major##4##3, #type3);                                               \
    printf(format(#type3), a5.a3);                                              \
    printf(" ");                                                                \
    printf("%d [%s] = ", major##4##4, #type4);                                               \
    printf(format(#type4), a5.a4);                                              \
    printf("\n");                                                               \
}                                                                               \
                                                                                \
void print_##major##5##5(struct t_##major##5##5 a5) {                           \
    printf("%d [%s] = ", major##5##1, #type1);                                               \
    printf(format(#type1), a5.a1);                                              \
    printf(" ");                                                                \
    printf("%d [%s] = ", major##5##2, #type2);                                               \
    printf(format(#type2), a5.a2);                                              \
    printf(" ");                                                                \
    printf("%d [%s] = ", major##5##3, #type3);                                               \
    printf(format(#type3), a5.a3);                                              \
    printf(" ");                                                                \
    printf("%d [%s] = ", major##5##4, #type4);                                               \
    printf(format(#type4), a5.a4);                                              \
    printf(" ");                                                                \
    printf("%d [%s] = ", major##5##5, #type5);                                               \
    printf(format(#type5), a5.a5);                                              \
    printf("\n");                                                               \
}

#define TEST(i, code1, code2, code3, code4, code5, code6, code7, code8, code9, i2) \
void test_##i##_9_0(int ign,                                                        \
                struct t_##code1 c1,                                            \
                struct t_##code2 c2,                                            \
                struct t_##code3 c3,                                            \
                struct t_##code4 c4,                                            \
                struct t_##code5 c5,                                            \
                struct t_##code6 c6,                                            \
                struct t_##code7 c7,                                            \
                struct t_##code8 c8,                                            \
                struct t_##code9 c9,                                            \
                int last)                                                       \
{                                                                               \
    printf("%05d %d %d:\n", i, 9, 0);                                           \
    print_##code1(c1);                                                          \
    print_##code2(c2);                                                          \
    print_##code3(c3);                                                          \
    print_##code4(c4);                                                          \
    print_##code5(c5);                                                          \
    print_##code6(c6);                                                          \
    print_##code7(c7);                                                          \
    print_##code8(c8);                                                          \
    print_##code9(c9);                                                          \
    printf("\n");                                                               \
}                                                                               \
                                                                                \
void test_##i##_1_8(int ign,                                                        \
                struct t_##code1 c1,                                            \
                    ...) \
{                                                                               \
    va_list ap;                                                                 \
    va_start(ap, c1);                                                          \
                                                                                \
    printf("%05d %d %d:\n", i, 1, 8);                                           \
    print_##code1(c1);                                                          \
    { struct t_##code2 c2 = va_arg(ap, struct t_##code2); print_##code2(c2); }  \
    { struct t_##code3 c3 = va_arg(ap, struct t_##code3); print_##code3(c3); }  \
    { struct t_##code4 c4 = va_arg(ap, struct t_##code4); print_##code4(c4); }  \
    { struct t_##code5 c5 = va_arg(ap, struct t_##code5); print_##code5(c5); }  \
    { struct t_##code6 c6 = va_arg(ap, struct t_##code6); print_##code6(c6); }  \
    { struct t_##code7 c7 = va_arg(ap, struct t_##code7); print_##code7(c7); }  \
    { struct t_##code8 c8 = va_arg(ap, struct t_##code8); print_##code8(c8); }  \
    { struct t_##code9 c9 = va_arg(ap, struct t_##code9); print_##code9(c9); }  \
    va_end(ap); \
    printf("\n");                                                               \
}                                                                               \
                                                                                \
void test_##i##_2_7(int ign,                                                        \
                struct t_##code1 c1,                                            \
                struct t_##code2 c2,                                            \
                    ...) \
{                                                                               \
    va_list ap;                                                                 \
    va_start(ap, c2);                                                          \
                                                                                \
    printf("%05d %d %d:\n", i, 2, 7);                                           \
    print_##code1(c1);                                                          \
    print_##code2(c2);                                                          \
    { struct t_##code3 c3 = va_arg(ap, struct t_##code3); print_##code3(c3); }  \
    { struct t_##code4 c4 = va_arg(ap, struct t_##code4); print_##code4(c4); }  \
    { struct t_##code5 c5 = va_arg(ap, struct t_##code5); print_##code5(c5); }  \
    { struct t_##code6 c6 = va_arg(ap, struct t_##code6); print_##code6(c6); }  \
    { struct t_##code7 c7 = va_arg(ap, struct t_##code7); print_##code7(c7); }  \
    { struct t_##code8 c8 = va_arg(ap, struct t_##code8); print_##code8(c8); }  \
    { struct t_##code9 c9 = va_arg(ap, struct t_##code9); print_##code9(c9); }  \
    va_end(ap); \
    printf("\n");                                                               \
}                                                                               \
                                                                                \
void test_##i##_3_6(int ign,                                                        \
                struct t_##code1 c1,                                            \
                struct t_##code2 c2,                                            \
                struct t_##code3 c3,                                            \
                    ...) \
{                                                                               \
    va_list ap;                                                                 \
    va_start(ap, c3);                                                          \
                                                                                \
    printf("%05d %d %d:\n", i, 3, 6);                                           \
    print_##code1(c1);                                                          \
    print_##code2(c2);                                                          \
    print_##code3(c3);                                                          \
    { struct t_##code4 c4 = va_arg(ap, struct t_##code4); print_##code4(c4); }  \
    { struct t_##code5 c5 = va_arg(ap, struct t_##code5); print_##code5(c5); }  \
    { struct t_##code6 c6 = va_arg(ap, struct t_##code6); print_##code6(c6); }  \
    { struct t_##code7 c7 = va_arg(ap, struct t_##code7); print_##code7(c7); }  \
    { struct t_##code8 c8 = va_arg(ap, struct t_##code8); print_##code8(c8); }  \
    { struct t_##code9 c9 = va_arg(ap, struct t_##code9); print_##code9(c9); }  \
    va_end(ap); \
    printf("\n");                                                               \
}                                                                               \
                                                                                \
void test_##i##_4_5(int ign,                                                        \
                struct t_##code1 c1,                                            \
                struct t_##code2 c2,                                            \
                struct t_##code3 c3,                                            \
                struct t_##code4 c4,                                            \
                    ...) \
{                                                                               \
    va_list ap;                                                                 \
    va_start(ap, c4);                                                          \
                                                                                \
    printf("%05d %d %d:\n", i, 4, 5);                                           \
    print_##code1(c1);                                                          \
    print_##code2(c2);                                                          \
    print_##code3(c3);                                                          \
    print_##code4(c4);                                                          \
    { struct t_##code5 c5 = va_arg(ap, struct t_##code5); print_##code5(c5); }  \
    { struct t_##code6 c6 = va_arg(ap, struct t_##code6); print_##code6(c6); }  \
    { struct t_##code7 c7 = va_arg(ap, struct t_##code7); print_##code7(c7); }  \
    { struct t_##code8 c8 = va_arg(ap, struct t_##code8); print_##code8(c8); }  \
    { struct t_##code9 c9 = va_arg(ap, struct t_##code9); print_##code9(c9); }  \
    va_end(ap); \
    printf("\n");                                                               \
}                                                                               \
                                                                                \
void test_##i##_5_4(int ign,                                                        \
                struct t_##code1 c1,                                            \
                struct t_##code2 c2,                                            \
                struct t_##code3 c3,                                            \
                struct t_##code4 c4,                                            \
                struct t_##code5 c5,                                            \
                    ...) \
{                                                                               \
    va_list ap;                                                                 \
    va_start(ap, c5);                                                          \
                                                                                \
    printf("%05d %d %d:\n", i, 5, 4);                                           \
    print_##code1(c1);                                                          \
    print_##code2(c2);                                                          \
    print_##code3(c3);                                                          \
    print_##code4(c4);                                                          \
    print_##code5(c5);                                                          \
    { struct t_##code6 c6 = va_arg(ap, struct t_##code6); print_##code6(c6); }  \
    { struct t_##code7 c7 = va_arg(ap, struct t_##code7); print_##code7(c7); }  \
    { struct t_##code8 c8 = va_arg(ap, struct t_##code8); print_##code8(c8); }  \
    { struct t_##code9 c9 = va_arg(ap, struct t_##code9); print_##code9(c9); }  \
    va_end(ap); \
    printf("\n");                                                               \
}                                                                               \
                                                                                \
void test_##i##_6_3(int ign,                                                        \
                struct t_##code1 c1,                                            \
                struct t_##code2 c2,                                            \
                struct t_##code3 c3,                                            \
                struct t_##code4 c4,                                            \
                struct t_##code5 c5,                                            \
                struct t_##code6 c6,                                            \
                    ...) \
{                                                                               \
    va_list ap;                                                                 \
    va_start(ap, c6);                                                          \
                                                                                \
    printf("%05d %d %d:\n", i, 6, 3);                                           \
    print_##code1(c1);                                                          \
    print_##code2(c2);                                                          \
    print_##code3(c3);                                                          \
    print_##code4(c4);                                                          \
    print_##code5(c5);                                                          \
    print_##code6(c6);                                                          \
    { struct t_##code7 c7 = va_arg(ap, struct t_##code7); print_##code7(c7); }  \
    { struct t_##code8 c8 = va_arg(ap, struct t_##code8); print_##code8(c8); }  \
    { struct t_##code9 c9 = va_arg(ap, struct t_##code9); print_##code9(c9); }  \
    va_end(ap); \
    printf("\n");                                                               \
}                                                                               \
                                                                                \
void test_##i##_7_2(int ign,                                                        \
                struct t_##code1 c1,                                            \
                struct t_##code2 c2,                                            \
                struct t_##code3 c3,                                            \
                struct t_##code4 c4,                                            \
                struct t_##code5 c5,                                            \
                struct t_##code6 c6,                                            \
                struct t_##code7 c7,                                            \
                    ...) \
{                                                                               \
    va_list ap;                                                                 \
    va_start(ap, c7);                                                          \
                                                                                \
    printf("%05d %d %d:\n", i, 7, 2);                                           \
    print_##code1(c1);                                                          \
    print_##code2(c2);                                                          \
    print_##code3(c3);                                                          \
    print_##code4(c4);                                                          \
    print_##code5(c5);                                                          \
    print_##code6(c6);                                                          \
    print_##code7(c7);                                                          \
    { struct t_##code8 c8 = va_arg(ap, struct t_##code8); print_##code8(c8); }  \
    { struct t_##code9 c9 = va_arg(ap, struct t_##code9); print_##code9(c9); }  \
    va_end(ap); \
    printf("\n");                                                               \
}                                                                               \
                                                                                \
void test_##i##_8_1(int ign,                                                    \
                struct t_##code1 c1,                                            \
                struct t_##code2 c2,                                            \
                struct t_##code3 c3,                                            \
                struct t_##code4 c4,                                            \
                struct t_##code5 c5,                                            \
                struct t_##code6 c6,                                            \
                struct t_##code7 c7,                                            \
                struct t_##code8 c8,                                            \
                   ...) \
{                                                                               \
    va_list ap;                                                                 \
    va_start(ap, c8);                                                          \
                                                                                \
    printf("%05d %d %d:\n", i, 8, 1);                                           \
    print_##code1(c1);                                                          \
    print_##code2(c2);                                                          \
    print_##code3(c3);                                                          \
    print_##code4(c4);                                                          \
    print_##code5(c5);                                                          \
    print_##code6(c6);                                                          \
    print_##code7(c7);                                                          \
    print_##code8(c8);                                                          \
    { struct t_##code9 c9 = va_arg(ap, struct t_##code9); print_##code9(c9); }  \
    va_end(ap); \
    printf("\n");                                                               \
}                                                                               \
                                                                                \
void test_##i##_0_9(int ign, ...)                                                  \
{                                                                               \
    va_list ap;                                                                 \
    va_start(ap, ign);                                                          \
                                                                                \
    printf("%05d %d %d:\n", i, 9, 0);                                           \
    { struct t_##code1 c1 = va_arg(ap, struct t_##code1); print_##code1(c1); }  \
    { struct t_##code2 c2 = va_arg(ap, struct t_##code2); print_##code2(c2); }  \
    { struct t_##code3 c3 = va_arg(ap, struct t_##code3); print_##code3(c3); }  \
    { struct t_##code4 c4 = va_arg(ap, struct t_##code4); print_##code4(c4); }  \
    { struct t_##code5 c5 = va_arg(ap, struct t_##code5); print_##code5(c5); }  \
    { struct t_##code6 c6 = va_arg(ap, struct t_##code6); print_##code6(c6); }  \
    { struct t_##code7 c7 = va_arg(ap, struct t_##code7); print_##code7(c7); }  \
    { struct t_##code8 c8 = va_arg(ap, struct t_##code8); print_##code8(c8); }  \
    { struct t_##code9 c9 = va_arg(ap, struct t_##code9); print_##code9(c9); }  \
    va_end(ap); \
    printf("\n");                                                               \
}

/*
cat <<EOF >typelist
int
long long
float
double
long double
EOF
for i in $(seq 1 99); do
    shuf < typelist |
    (read a1; read a2; read a3; read a4; read a5; echo "S($i,1,$a1,$a2,$a3,$a4,$a5)")
done


*/

S(1,1,long double,float,long long,double,int)
S(2,1,double,long double,float,long long,int)
S(3,1,int,double,long double,long long,float)
S(4,1,int,float,long long,double,long double)
S(5,1,double,int,long double,float,long long)
S(6,1,float,int,long double,double,long long)
S(7,1,long long,float,int,long double,double)
S(8,1,long double,float,long long,double,int)
S(9,1,float,double,long long,int,long double)
S(10,1,double,long double,float,int,long long)
S(11,1,double,float,long double,long long,int)
S(12,1,long long,long double,double,int,float)
S(13,1,float,int,long double,long long,double)
S(14,1,long double,long long,int,float,double)
S(15,1,double,float,int,long long,long double)
S(16,1,float,long long,int,long double,double)
S(17,1,int,long long,float,double,long double)
S(18,1,long double,long long,double,float,int)
S(19,1,float,long double,int,double,long long)
S(20,1,long double,float,double,int,long long)
S(21,1,long double,long long,double,float,int)
S(22,1,long long,int,double,float,long double)
S(23,1,double,float,long long,long double,int)
S(24,1,long long,double,float,long double,int)
S(25,1,double,long double,long long,int,float)
S(26,1,float,long long,long double,double,int)
S(27,1,float,long long,int,long double,double)
S(28,1,int,float,long double,double,long long)
S(29,1,long double,float,double,int,long long)
S(30,1,double,long long,int,float,long double)
S(31,1,int,long double,double,long long,float)
S(32,1,long long,int,float,double,long double)
S(33,1,double,long double,float,long long,int)
S(34,1,float,int,double,long long,long double)
S(35,1,long long,long double,float,int,double)
S(36,1,float,double,int,long long,long double)
S(37,1,float,long long,double,int,long double)
S(38,1,long long,int,float,double,long double)
S(39,1,int,long long,double,float,long double)
S(40,1,long double,double,int,long long,float)
S(41,1,double,long long,int,long double,float)
S(42,1,long long,float,long double,int,double)
S(43,1,int,long double,double,float,long long)
S(44,1,float,int,double,long long,long double)
S(45,1,double,float,long long,long double,int)
S(46,1,double,int,long double,float,long long)
S(47,1,double,float,long double,int,long long)
S(48,1,double,long long,int,long double,float)
S(49,1,long long,double,int,long double,float)
S(50,1,long long,float,int,long double,double)
S(51,1,double,long long,int,float,long double)
S(52,1,long double,double,float,int,long long)
S(53,1,int,long long,double,long double,float)
S(54,1,double,long long,float,int,long double)
S(55,1,long double,long long,double,int,float)
S(56,1,int,float,long long,double,long double)
S(57,1,double,float,int,long double,long long)
S(58,1,long long,int,long double,float,double)
S(59,1,int,double,long double,long long,float)
S(60,1,float,int,double,long long,long double)
S(61,1,long long,long double,float,double,int)
S(62,1,long long,double,long double,int,float)
S(63,1,float,long long,double,long double,int)
S(64,1,long long,float,int,long double,double)
S(65,1,long double,double,float,int,long long)
S(66,1,float,long long,double,int,long double)
S(67,1,float,long double,double,long long,int)
S(68,1,double,long double,long long,int,float)
S(69,1,float,int,long long,long double,double)
S(70,1,double,long double,float,long long,int)
S(71,1,double,long long,int,long double,float)
S(72,1,int,long double,double,long long,float)
S(73,1,long long,long double,float,int,double)
S(74,1,long long,double,long double,float,int)
S(75,1,float,long long,int,double,long double)
S(76,1,int,float,long double,double,long long)
S(77,1,double,float,int,long long,long double)
S(78,1,float,long long,long double,double,int)
S(79,1,int,long double,long long,float,double)
S(80,1,long double,float,int,long long,double)
S(81,1,float,int,double,long double,long long)
S(82,1,float,double,int,long double,long long)
S(83,1,float,int,double,long double,long long)
S(84,1,double,long double,long long,int,float)
S(85,1,long long,long double,double,float,int)
S(86,1,long double,int,float,double,long long)
S(87,1,int,long long,long double,float,double)
S(88,1,long double,int,double,float,long long)
S(89,1,float,int,long double,double,long long)
S(90,1,double,long double,long long,int,float)
S(91,1,int,long double,double,long long,float)
S(92,1,float,double,long long,int,long double)
S(93,1,int,float,long long,long double,double)
S(94,1,long long,double,int,float,long double)
S(95,1,long long,double,float,long double,int)
S(96,1,float,long long,double,long double,int)
S(97,1,float,double,long long,int,long double)
S(98,1,double,long long,float,long double,int)
S(99,1,double,float,long double,long long,int)

TEST(1,5633,7155,5033,8944,4755,8000,1633,3800,6655,0)
TEST(2,2655,7511,8633,6633,5211,6822,5800,222,2944,0)
TEST(3,6700,4633,9400,6255,4922,100,6233,222,1433,0)
TEST(4,4055,1333,4744,6055,7022,9000,8300,3344,733,0)
TEST(5,211,2255,3800,4133,2411,5100,8655,8400,3933,0)
TEST(6,9100,3944,3911,4711,9200,4344,8355,3055,4522,0)
TEST(7,5211,6822,3911,6622,4200,4800,5855,5855,4422,0)
TEST(8,2611,5311,3900,7211,8033,9733,7400,944,4511,0)
TEST(9,1233,8255,344,9955,2722,1055,3800,7044,8255,0)
TEST(10,7922,1933,5711,6400,5955,8211,9422,433,7644,0)
TEST(11,7944,6855,5322,4711,4211,5933,4111,3755,3055,0)
TEST(12,5933,1722,8544,7011,2411,6033,7744,1611,733,0)
TEST(13,1100,2622,5500,1055,1244,7600,9955,5133,4100,0)
TEST(14,1655,7333,7244,8922,6011,8522,744,3644,7533,0)
TEST(15,155,5733,2755,4155,9522,2733,5711,7855,4122,0)
TEST(16,8544,6333,5911,6644,933,9900,3844,4455,3522,0)
TEST(17,6222,2822,4033,5200,8455,8522,9411,3444,9922,0)
TEST(18,3055,2800,6855,6300,4944,9122,9922,3011,9533,0)
TEST(19,1633,2400,400,7111,7111,3544,9644,8455,4355,0)
TEST(20,2511,9122,5044,5100,5000,6800,4900,8922,611,0)
TEST(21,6344,6055,3422,5644,7611,2011,3422,5122,4833,0)
TEST(22,2844,9055,9055,3711,5111,9622,5455,9133,7255,0)
TEST(23,2500,233,1900,3555,7711,5933,2955,4844,1411,0)
TEST(24,9433,9544,6211,7155,7555,4755,8322,3200,4700,0)
TEST(25,7133,6500,4844,4644,900,8111,5044,6400,2144,0)
TEST(26,7500,922,3155,3933,1255,1722,8455,855,3622,0)
TEST(27,7200,8700,2055,4400,8255,5511,2255,5122,6733,0)
TEST(28,811,4533,4800,5855,1455,4422,9455,500,3233,0)
TEST(29,2655,8455,2400,6111,2022,1033,755,6033,1444,0)
TEST(30,7211,8355,8844,911,5733,3511,5311,933,1711,0)
TEST(31,9044,6244,8855,8211,7333,6233,933,333,1622,0)
TEST(32,4033,2411,355,5622,8722,5822,2511,9855,200,0)
TEST(33,2611,6922,155,6222,8800,6433,6033,4044,3933,0)
TEST(34,8755,922,2733,4855,7455,5755,3733,8733,8822,0)
TEST(35,155,7433,8644,555,8500,2944,7100,9600,7711,0)
TEST(36,855,8722,3955,4111,8244,655,3822,3011,7233,0)
TEST(37,1033,5744,7444,4955,7800,3544,6833,6433,233,0)
TEST(38,3433,1822,2633,7133,8922,6344,9144,4955,6355,0)
TEST(39,1855,5233,2944,6511,7933,100,4233,5700,6933,0)
TEST(40,5800,4333,2622,244,4333,1111,7944,2655,2211,0)
TEST(41,4811,6700,2155,9600,1944,2022,9622,6055,7533,0)
TEST(42,9344,9300,1522,4600,6000,7833,8633,8811,8122,0)
TEST(43,8300,3222,5755,1644,4933,5155,5944,4122,3022,0)
TEST(44,3700,233,9944,8855,5111,3400,3855,411,900,0)
TEST(45,7333,7855,2255,9311,2122,9722,3755,8744,7211,0)
TEST(46,1700,1055,2433,2255,9933,7822,7011,2933,4033,0)
TEST(47,4244,6833,7955,9255,2255,9155,1311,1844,3355,0)
TEST(48,2833,9000,1544,9222,1244,8111,7144,5611,1122,0)
TEST(49,6122,7122,8533,6033,944,644,4500,4744,911,0)
TEST(50,3555,4855,5200,2955,3500,1555,5300,7600,4533,0)
TEST(51,9433,6122,7644,8355,8900,8600,2500,6122,4200,0)
TEST(52,6855,4722,4933,6822,5600,2322,911,5122,8800,0)
TEST(53,9222,2122,3022,9300,4455,1111,3322,7044,4011,0)
TEST(54,9444,1155,7000,9455,9700,2611,3500,1222,933,0)
TEST(55,8455,6011,3422,9022,3955,4411,822,1955,2111,0)
TEST(56,9155,711,8455,8755,3333,1344,3744,2400,6922,0)
TEST(57,1755,5422,6311,3911,4411,4833,1744,2900,5400,0)
TEST(58,8044,3811,6200,8000,9422,6422,5855,1044,6055,0)
TEST(59,5444,7911,1122,5455,4244,5355,633,4055,5722,0)
TEST(60,4544,1555,1522,3322,2611,3144,7322,6733,9611,0)
TEST(61,1633,4555,4055,5344,9455,9822,1122,5133,9800,0)
TEST(62,5711,6433,8133,1055,6811,6400,744,1122,2500,0)
TEST(63,9833,5822,6322,9055,4744,5955,355,6733,6222,0)
TEST(64,5733,755,4411,7211,5700,5733,5722,1800,4444,0)
TEST(65,522,7533,4400,9355,911,5755,833,9155,3700,0)
TEST(66,2400,4555,4855,4811,5244,6222,3200,2922,6044,0)
TEST(67,9822,2655,5811,3222,5944,2511,4044,5944,611,0)
TEST(68,6244,5533,1944,1955,533,4200,9322,2844,100,0)
TEST(69,8544,3022,6900,4233,1011,9855,4811,1711,5822,0)
TEST(70,8244,4055,8411,3522,6044,7455,6344,8022,7700,0)
TEST(71,9222,4855,9300,8633,8500,344,7122,2311,2200,0)
TEST(72,6133,4411,622,1222,9744,5800,6400,233,3044,0)
TEST(73,733,6833,7644,6200,8122,8955,5111,1233,6900,0)
TEST(74,2800,6622,8144,1844,1644,7211,5522,1155,2111,0)
TEST(75,3700,2300,2922,5422,9533,3811,8833,555,3011,0)
TEST(76,8955,5622,3533,8022,6655,233,7833,9555,2311,0)
TEST(77,8400,3255,2011,9144,3111,4722,9944,6533,8455,0)
TEST(78,8444,4611,5111,7222,6433,3144,844,7844,2744,0)
TEST(79,4611,5855,844,7044,7400,4844,5922,9522,5255,0)
TEST(80,2855,2933,1000,133,5955,2711,7122,1244,4800,0)
TEST(81,5100,3622,4400,3311,1455,5155,9555,7633,5511,0)
TEST(82,722,9222,1844,5622,2511,300,7222,3622,1244,0)
TEST(83,3155,5744,7411,700,5955,7255,4722,1555,7755,0)
TEST(84,922,4922,3844,3022,7500,1633,6322,6600,822,0)
TEST(85,2944,6555,822,2700,6500,1700,5333,9944,133,0)
TEST(86,9522,1155,9933,3200,2500,7100,7244,1633,8033,0)
TEST(87,4255,7044,1500,8933,2100,7455,733,8111,8855,0)
TEST(88,8133,4322,4744,1633,4200,7944,222,6822,5422,0)
TEST(89,2655,7300,9955,944,8411,8811,7522,711,9955,0)
TEST(90,1544,6433,9833,5811,8744,3900,7911,7333,9922,0)
TEST(91,455,8322,5144,6633,6044,4833,2844,6900,6611,0)
TEST(92,4233,5955,1222,3344,5922,6111,9055,6411,7622,0)
TEST(93,3944,1344,922,7244,3611,7622,7244,9300,7833,0)
TEST(94,8333,7511,4155,1844,6155,1000,444,4844,1933,0)
TEST(95,8300,444,755,3533,5344,544,1444,9822,7400,0)
TEST(96,2100,5155,2044,7522,3111,1811,1522,5544,9633,0)
TEST(97,2255,8955,155,3655,2211,4500,544,8955,3100,0)
TEST(98,4633,244,3500,9544,2055,8455,5833,133,5744,0)
TEST(99,2144,911,4555,1133,7855,6344,4811,3622,2233,0)
/*
for i in $(seq 1 99); do
   echo -n TEST\($i,
   for j in $(seq 1 9); do
       major=$(($RANDOM%99+1))
       minor=$(($RANDOM%6))
       echo -n ${major}${minor}${minor},
   done
   echo 0\)
done
*/


void randomized(void)
    {
#undef TEST
#define TEST(i, code1, code2, code3, code4, code5, code6, code7, code8, code9, i2) \
        printf("test %d codes %d %d %d %d %d %d %d %d %d\n",                    \
        i,                                                                      \
            code1,                                                              \
            code2,                                                              \
            code3,                                                              \
            code4,                                                              \
            code5,                                                              \
            code6,                                                              \
            code7,                                                              \
            code8,                                                              \
            code9                                                               \
              );                                                                \
        test_##i##_0_9(i,                                                       \
                       t_##code1,                                               \
                       t_##code2,                                               \
                       t_##code3,                                               \
                       t_##code4,                                               \
                       t_##code5,                                               \
                       t_##code6,                                               \
                       t_##code7,                                               \
                       t_##code8,                                               \
                       t_##code9,                                               \
                       i2                                                       \
                      );                                                        \
                                                                                \
        test_##i##_1_8(i,                                                       \
                       t_##code1,                                               \
                       t_##code2,                                               \
                       t_##code3,                                               \
                       t_##code4,                                               \
                       t_##code5,                                               \
                       t_##code6,                                               \
                       t_##code7,                                               \
                       t_##code8,                                               \
                       t_##code9,                                               \
                       i2                                                       \
                      );                                                        \
                                                                                \
        test_##i##_2_7(i,                                                       \
                       t_##code1,                                               \
                       t_##code2,                                               \
                       t_##code3,                                               \
                       t_##code4,                                               \
                       t_##code5,                                               \
                       t_##code6,                                               \
                       t_##code7,                                               \
                       t_##code8,                                               \
                       t_##code9,                                               \
                       i2                                                       \
                      );                                                        \
                                                                                \
        test_##i##_4_5(i,                                                       \
                       t_##code1,                                               \
                       t_##code2,                                               \
                       t_##code3,                                               \
                       t_##code4,                                               \
                       t_##code5,                                               \
                       t_##code6,                                               \
                       t_##code7,                                               \
                       t_##code8,                                               \
                       t_##code9,                                               \
                       i2                                                       \
                      );                                                        \
                                                                                \
        test_##i##_3_6(i,                                                       \
                       t_##code1,                                               \
                       t_##code2,                                               \
                       t_##code3,                                               \
                       t_##code4,                                               \
                       t_##code5,                                               \
                       t_##code6,                                               \
                       t_##code7,                                               \
                       t_##code8,                                               \
                       t_##code9,                                               \
                       i2                                                       \
                      );                                                        \
                                                                                \
        test_##i##_5_4(i,                                                       \
                       t_##code1,                                               \
                       t_##code2,                                               \
                       t_##code3,                                               \
                       t_##code4,                                               \
                       t_##code5,                                               \
                       t_##code6,                                               \
                       t_##code7,                                               \
                       t_##code8,                                               \
                       t_##code9,                                               \
                       i2                                                       \
                      );                                                        \
                                                                                \
        test_##i##_6_3(i,                                                       \
                       t_##code1,                                               \
                       t_##code2,                                               \
                       t_##code3,                                               \
                       t_##code4,                                               \
                       t_##code5,                                               \
                       t_##code6,                                               \
                       t_##code7,                                               \
                       t_##code8,                                               \
                       t_##code9,                                               \
                       i2                                                       \
                      );                                                        \
                                                                                \
        test_##i##_7_2(i,                                                       \
                       t_##code1,                                               \
                       t_##code2,                                               \
                       t_##code3,                                               \
                       t_##code4,                                               \
                       t_##code5,                                               \
                       t_##code6,                                               \
                       t_##code7,                                               \
                       t_##code8,                                               \
                       t_##code9,                                               \
                       i2                                                       \
                      );                                                        \
                                                                                \
        test_##i##_8_1(i,                                                       \
                       t_##code1,                                               \
                       t_##code2,                                               \
                       t_##code3,                                               \
                       t_##code4,                                               \
                       t_##code5,                                               \
                       t_##code6,                                               \
                       t_##code7,                                               \
                       t_##code8,                                               \
                       t_##code9,                                               \
                       i2                                                       \
                      );                                                        \
                                                                                \
        test_##i##_9_0(i,                                                       \
                       t_##code1,                                               \
                       t_##code2,                                               \
                       t_##code3,                                               \
                       t_##code4,                                               \
                       t_##code5,                                               \
                       t_##code6,                                               \
                       t_##code7,                                               \
                       t_##code8,                                               \
                       t_##code9,                                               \
                       i2                                                       \
                      );

TEST(1,5633,7155,5033,8944,4755,8000,1633,3800,6655,0)
TEST(2,2655,7511,8633,6633,5211,6822,5800,222,2944,0)
TEST(3,6700,4633,9400,6255,4922,100,6233,222,1433,0)
TEST(4,4055,1333,4744,6055,7022,9000,8300,3344,733,0)
TEST(5,211,2255,3800,4133,2411,5100,8655,8400,3933,0)
TEST(6,9100,3944,3911,4711,9200,4344,8355,3055,4522,0)
TEST(7,5211,6822,3911,6622,4200,4800,5855,5855,4422,0)
TEST(8,2611,5311,3900,7211,8033,9733,7400,944,4511,0)
TEST(9,1233,8255,344,9955,2722,1055,3800,7044,8255,0)
TEST(10,7922,1933,5711,6400,5955,8211,9422,433,7644,0)
TEST(11,7944,6855,5322,4711,4211,5933,4111,3755,3055,0)
TEST(12,5933,1722,8544,7011,2411,6033,7744,1611,733,0)
TEST(13,1100,2622,5500,1055,1244,7600,9955,5133,4100,0)
TEST(14,1655,7333,7244,8922,6011,8522,744,3644,7533,0)
TEST(15,155,5733,2755,4155,9522,2733,5711,7855,4122,0)
TEST(16,8544,6333,5911,6644,933,9900,3844,4455,3522,0)
TEST(17,6222,2822,4033,5200,8455,8522,9411,3444,9922,0)
TEST(18,3055,2800,6855,6300,4944,9122,9922,3011,9533,0)
TEST(19,1633,2400,400,7111,7111,3544,9644,8455,4355,0)
TEST(20,2511,9122,5044,5100,5000,6800,4900,8922,611,0)
TEST(21,6344,6055,3422,5644,7611,2011,3422,5122,4833,0)
TEST(22,2844,9055,9055,3711,5111,9622,5455,9133,7255,0)
TEST(23,2500,233,1900,3555,7711,5933,2955,4844,1411,0)
TEST(24,9433,9544,6211,7155,7555,4755,8322,3200,4700,0)
TEST(25,7133,6500,4844,4644,900,8111,5044,6400,2144,0)
TEST(26,7500,922,3155,3933,1255,1722,8455,855,3622,0)
TEST(27,7200,8700,2055,4400,8255,5511,2255,5122,6733,0)
TEST(28,811,4533,4800,5855,1455,4422,9455,500,3233,0)
TEST(29,2655,8455,2400,6111,2022,1033,755,6033,1444,0)
TEST(30,7211,8355,8844,911,5733,3511,5311,933,1711,0)
TEST(31,9044,6244,8855,8211,7333,6233,933,333,1622,0)
TEST(32,4033,2411,355,5622,8722,5822,2511,9855,200,0)
TEST(33,2611,6922,155,6222,8800,6433,6033,4044,3933,0)
TEST(34,8755,922,2733,4855,7455,5755,3733,8733,8822,0)
TEST(35,155,7433,8644,555,8500,2944,7100,9600,7711,0)
TEST(36,855,8722,3955,4111,8244,655,3822,3011,7233,0)
TEST(37,1033,5744,7444,4955,7800,3544,6833,6433,233,0)
TEST(38,3433,1822,2633,7133,8922,6344,9144,4955,6355,0)
TEST(39,1855,5233,2944,6511,7933,100,4233,5700,6933,0)
TEST(40,5800,4333,2622,244,4333,1111,7944,2655,2211,0)
TEST(41,4811,6700,2155,9600,1944,2022,9622,6055,7533,0)
TEST(42,9344,9300,1522,4600,6000,7833,8633,8811,8122,0)
TEST(43,8300,3222,5755,1644,4933,5155,5944,4122,3022,0)
TEST(44,3700,233,9944,8855,5111,3400,3855,411,900,0)
TEST(45,7333,7855,2255,9311,2122,9722,3755,8744,7211,0)
TEST(46,1700,1055,2433,2255,9933,7822,7011,2933,4033,0)
TEST(47,4244,6833,7955,9255,2255,9155,1311,1844,3355,0)
TEST(48,2833,9000,1544,9222,1244,8111,7144,5611,1122,0)
TEST(49,6122,7122,8533,6033,944,644,4500,4744,911,0)
TEST(50,3555,4855,5200,2955,3500,1555,5300,7600,4533,0)
TEST(51,9433,6122,7644,8355,8900,8600,2500,6122,4200,0)
TEST(52,6855,4722,4933,6822,5600,2322,911,5122,8800,0)
TEST(53,9222,2122,3022,9300,4455,1111,3322,7044,4011,0)
TEST(54,9444,1155,7000,9455,9700,2611,3500,1222,933,0)
TEST(55,8455,6011,3422,9022,3955,4411,822,1955,2111,0)
TEST(56,9155,711,8455,8755,3333,1344,3744,2400,6922,0)
TEST(57,1755,5422,6311,3911,4411,4833,1744,2900,5400,0)
TEST(58,8044,3811,6200,8000,9422,6422,5855,1044,6055,0)
TEST(59,5444,7911,1122,5455,4244,5355,633,4055,5722,0)
TEST(60,4544,1555,1522,3322,2611,3144,7322,6733,9611,0)
TEST(61,1633,4555,4055,5344,9455,9822,1122,5133,9800,0)
TEST(62,5711,6433,8133,1055,6811,6400,744,1122,2500,0)
TEST(63,9833,5822,6322,9055,4744,5955,355,6733,6222,0)
TEST(64,5733,755,4411,7211,5700,5733,5722,1800,4444,0)
TEST(65,522,7533,4400,9355,911,5755,833,9155,3700,0)
TEST(66,2400,4555,4855,4811,5244,6222,3200,2922,6044,0)
TEST(67,9822,2655,5811,3222,5944,2511,4044,5944,611,0)
TEST(68,6244,5533,1944,1955,533,4200,9322,2844,100,0)
TEST(69,8544,3022,6900,4233,1011,9855,4811,1711,5822,0)
TEST(70,8244,4055,8411,3522,6044,7455,6344,8022,7700,0)
TEST(71,9222,4855,9300,8633,8500,344,7122,2311,2200,0)
TEST(72,6133,4411,622,1222,9744,5800,6400,233,3044,0)
TEST(73,733,6833,7644,6200,8122,8955,5111,1233,6900,0)
TEST(74,2800,6622,8144,1844,1644,7211,5522,1155,2111,0)
TEST(75,3700,2300,2922,5422,9533,3811,8833,555,3011,0)
TEST(76,8955,5622,3533,8022,6655,233,7833,9555,2311,0)
TEST(77,8400,3255,2011,9144,3111,4722,9944,6533,8455,0)
TEST(78,8444,4611,5111,7222,6433,3144,844,7844,2744,0)
TEST(79,4611,5855,844,7044,7400,4844,5922,9522,5255,0)
TEST(80,2855,2933,1000,133,5955,2711,7122,1244,4800,0)
TEST(81,5100,3622,4400,3311,1455,5155,9555,7633,5511,0)
TEST(82,722,9222,1844,5622,2511,300,7222,3622,1244,0)
TEST(83,3155,5744,7411,700,5955,7255,4722,1555,7755,0)
TEST(84,922,4922,3844,3022,7500,1633,6322,6600,822,0)
TEST(85,2944,6555,822,2700,6500,1700,5333,9944,133,0)
TEST(86,9522,1155,9933,3200,2500,7100,7244,1633,8033,0)
TEST(87,4255,7044,1500,8933,2100,7455,733,8111,8855,0)
TEST(88,8133,4322,4744,1633,4200,7944,222,6822,5422,0)
TEST(89,2655,7300,9955,944,8411,8811,7522,711,9955,0)
TEST(90,1544,6433,9833,5811,8744,3900,7911,7333,9922,0)
TEST(91,455,8322,5144,6633,6044,4833,2844,6900,6611,0)
TEST(92,4233,5955,1222,3344,5922,6111,9055,6411,7622,0)
TEST(93,3944,1344,922,7244,3611,7622,7244,9300,7833,0)
TEST(94,8333,7511,4155,1844,6155,1000,444,4844,1933,0)
TEST(95,8300,444,755,3533,5344,544,1444,9822,7400,0)
TEST(96,2100,5155,2044,7522,3111,1811,1522,5544,9633,0)
TEST(97,2255,8955,155,3655,2211,4500,544,8955,3100,0)
TEST(98,4633,244,3500,9544,2055,8455,5833,133,5744,0)
TEST(99,2144,911,4555,1133,7855,6344,4811,3622,2233,0)
    }






struct hfa11 { int a; } hfa11 = { 111 };
struct hfa12 { int a, b; } hfa12 = { 121, 122 };
struct hfa13 { int a, b, c; } hfa13 = { 131, 132, 133 };
struct hfa14 { int a, b, c, d; } hfa14 = { 141, 142, 143, 144 };

struct hfa21 { long long a; } hfa21 = { 211 };
struct hfa22 { long long a, b; } hfa22 = { 221, 222 };
struct hfa23 { long long a, b, c; } hfa23 = { 231, 232, 233 };
struct hfa24 { long long a, b, c, d; } hfa24 = { 241, 242, 243, 244 };

struct hfa31 { long double a; } hfa31 = { 31.1 };
struct hfa32 { long double a, b; } hfa32 = { 32.1, 32.2 };
struct hfa33 { long double a, b, c; } hfa33 = { 33.1, 33.2, 33.3 };
struct hfa34 { long double a, b, c, d; } hfa34 = { 34.1, 34.2, 34.3, 34.4 };

void fa_s1(struct s1 a) { printf("%.1s\n", a.x); }
void fa_s2(struct s2 a) { printf("%.2s\n", a.x); }
void fa_s3(struct s3 a) { printf("%.3s\n", a.x); }
void fa_s4(struct s4 a) { printf("%.4s\n", a.x); }
void fa_s5(struct s5 a) { printf("%.5s\n", a.x); }
void fa_s6(struct s6 a) { printf("%.6s\n", a.x); }
void fa_s7(struct s7 a) { printf("%.7s\n", a.x); }
void fa_s8(struct s8 a) { printf("%.8s\n", a.x); }
void fa_s9(struct s9 a) { printf("%.9s\n", a.x); }
void fa_s10(struct s10 a) { printf("%.10s\n", a.x); }
void fa_s11(struct s11 a) { printf("%.11s\n", a.x); }
void fa_s12(struct s12 a) { printf("%.12s\n", a.x); }
void fa_s13(struct s13 a) { printf("%.13s\n", a.x); }
void fa_s14(struct s14 a) { printf("%.14s\n", a.x); }
void fa_s15(struct s15 a) { printf("%.15s\n", a.x); }
void fa_s16(struct s16 a) { printf("%.16s\n", a.x); }
void fa_s17(struct s17 a) { printf("%.17s\n", a.x); }

void fa_hfa11(struct hfa11 a)
{ printf("%d\n", a.a); }
void fa_hfa12(struct hfa12 a)
{ printf("%d %d\n", a.a, a.a); }
void fa_hfa13(struct hfa13 a)
{ printf("%d %d %d\n", a.a, a.b, a.c); }
void fa_hfa14(struct hfa14 a)
{ printf("%d %d %d %d\n", a.a, a.b, a.c, a.d); }

void fa_hfa21(struct hfa21 a)
{ printf("%lld\n", a.a); }
void fa_hfa22(struct hfa22 a)
{ printf("%lld %lld\n", a.a, a.a); }
void fa_hfa23(struct hfa23 a)
{ printf("%lld %lld %lld\n", a.a, a.b, a.c); }
void fa_hfa24(struct hfa24 a)
{ printf("%lld %lld %lld %lld\n", a.a, a.b, a.c, a.d); }

void fa_hfa31(struct hfa31 a)
{ printf("%.1Lf\n", a.a); }
void fa_hfa32(struct hfa32 a)
{ printf("%.1Lf %.1Lf\n", a.a, a.a); }
void fa_hfa33(struct hfa33 a)
{ printf("%.1Lf %.1Lf %.1Lf\n", a.a, a.b, a.c); }
void fa_hfa34(struct hfa34 a)
{ printf("%.1Lf %.1Lf %.1Lf %.1Lf\n", a.a, a.b, a.c, a.d); }

void fa1(struct s8 a, struct s9 b, struct s10 c, struct s11 d,
         struct s12 e, struct s13 f)
{
    printf("%.3s %.3s %.3s %.3s %.3s %.3s\n", a.x, b.x, c.x, d.x, e.x, f.x);
}

/* XXX add a test with the full string */
void fa2(struct s9 a, struct s10 b, struct s11 c, struct s12 d,
         struct s13 e, struct s14 f)
{
    printf("%.3s %.3s %.3s %.3s %.3s %.3s\n", a.x, b.x, c.x, d.x, e.x, f.x);
}

void fa3(struct hfa14 a, struct hfa23 b, struct hfa32 c)
{
    printf("%d %d %lld %lld %.1Lf %.1Lf\n",
           a.a, a.d, b.a, b.c, c.a, c.b);
}

void fa4(struct s1 a, struct hfa14 b, struct s2 c, struct hfa24 d,
         struct s3 e, struct hfa34 f)
{
    printf("%.1s %d %d %.2s %lld %lld %.3s %.1Lf %.1Lf\n",
           a.x, b.a, b.d, c.x, d.a, d.d, e.x, f.a, f.d);
}

void arg(void)
{
    printf("Arguments:\n");
    fa_s1(s1);
    fa_s2(s2);
    fa_s3(s3);
    fa_s4(s4);
    fa_s5(s5);
    fa_s6(s6);
    fa_s7(s7);
    fa_s8(s8);
    fa_s9(s9);
    fa_s10(s10);
    fa_s11(s11);
    fa_s12(s12);
    fa_s13(s13);
    fa_s14(s14);
    fa_s15(s15);
    fa_s16(s16);
    fa_s17(s17);
    fa_hfa11(hfa11);
    fa_hfa12(hfa12);
    fa_hfa13(hfa13);
    fa_hfa14(hfa14);
    fa_hfa21(hfa21);
    fa_hfa22(hfa22);
    fa_hfa23(hfa23);
    fa_hfa24(hfa24);
    fa_hfa31(hfa31);
    fa_hfa32(hfa32);
    fa_hfa33(hfa33);
    fa_hfa34(hfa34);
    fa1(s8, s9, s10, s11, s12, s13);
    fa2(s9, s10, s11, s12, s13, s14);
    fa3(hfa14, hfa23, hfa32);
    fa4(s1, hfa14, s2, hfa24, s3, hfa34);
}

struct s1 fr_s1(void) { return s1; }
struct s2 fr_s2(void) { return s2; }
struct s3 fr_s3(void) { return s3; }
struct s4 fr_s4(void) { return s4; }
struct s5 fr_s5(void) { return s5; }
struct s6 fr_s6(void) { return s6; }
struct s7 fr_s7(void) { return s7; }
struct s8 fr_s8(void) { return s8; }
struct s9 fr_s9(void) { return s9; }
struct s10 fr_s10(void) { return s10; }
struct s11 fr_s11(void) { return s11; }
struct s12 fr_s12(void) { return s12; }
struct s13 fr_s13(void) { return s13; }
struct s14 fr_s14(void) { return s14; }
struct s15 fr_s15(void) { return s15; }
struct s16 fr_s16(void) { return s16; }
struct s17 fr_s17(void) { return s17; }

struct hfa11 fr_hfa11(void) { return hfa11; }
struct hfa12 fr_hfa12(void) { return hfa12; }
struct hfa13 fr_hfa13(void) { return hfa13; }
struct hfa14 fr_hfa14(void) { return hfa14; }

struct hfa21 fr_hfa21(void) { return hfa21; }
struct hfa22 fr_hfa22(void) { return hfa22; }
struct hfa23 fr_hfa23(void) { return hfa23; }
struct hfa24 fr_hfa24(void) { return hfa24; }

struct hfa31 fr_hfa31(void) { return hfa31; }
struct hfa32 fr_hfa32(void) { return hfa32; }
struct hfa33 fr_hfa33(void) { return hfa33; }
struct hfa34 fr_hfa34(void) { return hfa34; }

void ret(void)
{
    struct s1 t1 = fr_s1();
    struct s2 t2 = fr_s2();
    struct s3 t3 = fr_s3();
    struct s4 t4 = fr_s4();
    struct s5 t5 = fr_s5();
    struct s6 t6 = fr_s6();
    struct s7 t7 = fr_s7();
    struct s8 t8 = fr_s8();
    struct s9 t9 = fr_s9();
    struct s10 t10 = fr_s10();
    struct s11 t11 = fr_s11();
    struct s12 t12 = fr_s12();
    struct s13 t13 = fr_s13();
    struct s14 t14 = fr_s14();
    struct s15 t15 = fr_s15();
    struct s16 t16 = fr_s16();
    struct s17 t17 = fr_s17();
    printf("Return values:\n");
    printf("%.1s\n", t1.x);
    printf("%.2s\n", t2.x);
    printf("%.3s\n", t3.x);
    printf("%.4s\n", t4.x);
    printf("%.5s\n", t5.x);
    printf("%.6s\n", t6.x);
    printf("%.7s\n", t7.x);
    printf("%.8s\n", t8.x);
    printf("%.9s\n", t9.x);
    printf("%.10s\n", t10.x);
    printf("%.11s\n", t11.x);
    printf("%.12s\n", t12.x);
    printf("%.13s\n", t13.x);
    printf("%.14s\n", t14.x);
    printf("%.15s\n", t15.x);
    printf("%.16s\n", t16.x);
    printf("%.17s\n", t17.x);
    printf("%d\n", fr_hfa11().a);
    printf("%d %d\n", fr_hfa12().a, fr_hfa12().b);
    printf("%d %d\n", fr_hfa13().a, fr_hfa13().c);
    printf("%d %d\n", fr_hfa14().a, fr_hfa14().d);
    printf("%lld\n", fr_hfa21().a);
    printf("%lld %lld\n", fr_hfa22().a, fr_hfa22().b);
    printf("%lld %lld\n", fr_hfa23().a, fr_hfa23().c);
    printf("%lld %lld\n", fr_hfa24().a, fr_hfa24().d);
    printf("%.1Lf\n", fr_hfa31().a);
    printf("%.1Lf %.1Lf\n", fr_hfa32().a, fr_hfa32().b);
    printf("%.1Lf %.1Lf\n", fr_hfa33().a, fr_hfa33().c);
    printf("%.1Lf %.1Lf\n", fr_hfa34().a, fr_hfa34().d);
}

int match(const char **s, const char *f)
{
    const char *p = *s;
    for (p = *s; *f && *f == *p; f++, p++)
        ;
    if (!*f) {
        *s = p - 1;
        return 1;
    }
    return 0;
}

void myprintf(const char *format, ...)
{
    const char *s;
    va_list ap;
    va_start(ap, format);
    for (s = format; *s; s++) {
        if (match(&s, "%7s")) {
            struct s7 t7 = va_arg(ap, struct s7);
            printf("%.7s", t7.x);
        }
        else if (match(&s, "%9s")) {
            struct s9 t9 = va_arg(ap, struct s9);
            printf("%.9s", t9.x);
        }
        else if (match(&s, "%hfa11")) {
            struct hfa11 x = va_arg(ap, struct hfa11);
            printf("%d,%d", x.a, x.a);
        }
        else if (match(&s, "%hfa12")) {
            struct hfa12 x = va_arg(ap, struct hfa12);
            printf("%d,%d", x.a, x.b);
        }
        else if (match(&s, "%hfa13")) {
            struct hfa13 x = va_arg(ap, struct hfa13);
            printf("%d,%d", x.a, x.c);
        }
        else if (match(&s, "%hfa14")) {
            struct hfa14 x = va_arg(ap, struct hfa14);
            printf("%d,%d", x.a, x.d);
        }
        else if (match(&s, "%hfa21")) {
            struct hfa21 x = va_arg(ap, struct hfa21);
            printf("%lld,%lld", x.a, x.a);
        }
        else if (match(&s, "%hfa22")) {
            struct hfa22 x = va_arg(ap, struct hfa22);
            printf("%lld,%lld", x.a, x.b);
        }
        else if (match(&s, "%hfa23")) {
            struct hfa23 x = va_arg(ap, struct hfa23);
            printf("%lld,%lld", x.a, x.c);
        }
        else if (match(&s, "%hfa24")) {
            struct hfa24 x = va_arg(ap, struct hfa24);
            printf("%lld,%lld", x.a, x.d);
        }
        else if (match(&s, "%hfa31")) {
            struct hfa31 x = va_arg(ap, struct hfa31);
            printf("%.1Lf,%.1Lf", x.a, x.a);
        }
        else if (match(&s, "%hfa32")) {
            struct hfa32 x = va_arg(ap, struct hfa32);
            printf("%.1Lf,%.1Lf", x.a, x.b);
        }
        else if (match(&s, "%hfa33")) {
            struct hfa33 x = va_arg(ap, struct hfa33);
            printf("%.1Lf,%.1Lf", x.a, x.c);
        }
        else if (match(&s, "%hfa34")) {
            struct hfa34 x = va_arg(ap, struct hfa34);
            printf("%.1Lf,%.1Lf", x.a, x.d);
        }
        else
            putchar(*s);
    }
    putchar('\n');
}

void stdarg(void)
{
    printf("stdarg:\n");
    myprintf("%9s %9s %9s %9s %9s %9s", s9, s9, s9, s9, s9, s9);
    myprintf("%7s %9s %9s %9s %9s %9s", s7, s9, s9, s9, s9, s9);

    myprintf("HFA long double:");
    myprintf("%hfa34 %hfa34 %hfa34 %hfa34", hfa34, hfa34, hfa34, hfa34);
    myprintf("%hfa33 %hfa34 %hfa34 %hfa34", hfa33, hfa34, hfa34, hfa34);
    myprintf("%hfa32 %hfa34 %hfa34 %hfa34", hfa32, hfa34, hfa34, hfa34);
    myprintf("%hfa31 %hfa34 %hfa34 %hfa34", hfa31, hfa34, hfa34, hfa34);

    myprintf("%hfa32 %hfa33 %hfa33 %hfa33 %hfa33",
             hfa32, hfa33, hfa33, hfa33, hfa33);
    myprintf("%hfa31 %hfa33 %hfa33 %hfa33 %hfa33",
             hfa31, hfa33, hfa33, hfa33, hfa33);
    myprintf("%hfa33 %hfa33 %hfa33 %hfa33",
             hfa33, hfa33, hfa33, hfa33);

    myprintf("%hfa34 %hfa32 %hfa32 %hfa32 %hfa32",
             hfa34, hfa32, hfa32, hfa32, hfa32);
    myprintf("%hfa33 %hfa32 %hfa32 %hfa32 %hfa32",
             hfa33, hfa32, hfa32, hfa32, hfa32);

    myprintf("%hfa34 %hfa32 %hfa31 %hfa31 %hfa31 %hfa31",
             hfa34, hfa32, hfa31, hfa31, hfa31, hfa31);

    myprintf("HFA long long:");
    myprintf("%hfa24 %hfa24 %hfa24 %hfa24", hfa24, hfa24, hfa24, hfa24);
    myprintf("%hfa23 %hfa24 %hfa24 %hfa24", hfa23, hfa24, hfa24, hfa24);
    myprintf("%hfa22 %hfa24 %hfa24 %hfa24", hfa22, hfa24, hfa24, hfa24);
    myprintf("%hfa21 %hfa24 %hfa24 %hfa24", hfa21, hfa24, hfa24, hfa24);

    myprintf("%hfa22 %hfa23 %hfa23 %hfa23 %hfa23",
             hfa22, hfa23, hfa23, hfa23, hfa23);
    myprintf("%hfa21 %hfa23 %hfa23 %hfa23 %hfa23",
             hfa21, hfa23, hfa23, hfa23, hfa23);
    myprintf("%hfa23 %hfa23 %hfa23 %hfa23",
             hfa23, hfa23, hfa23, hfa23);

    myprintf("%hfa24 %hfa22 %hfa22 %hfa22 %hfa22",
             hfa24, hfa22, hfa22, hfa22, hfa22);
    myprintf("%hfa23 %hfa22 %hfa22 %hfa22 %hfa22",
             hfa23, hfa22, hfa22, hfa22, hfa22);

    myprintf("%hfa24 %hfa22 %hfa21 %hfa21 %hfa21 %hfa21",
             hfa24, hfa22, hfa21, hfa21, hfa21, hfa21);

    myprintf("HFA int:");
    myprintf("%hfa14 %hfa14 %hfa14 %hfa14", hfa14, hfa14, hfa14, hfa14);
    myprintf("%hfa13 %hfa14 %hfa14 %hfa14", hfa13, hfa14, hfa14, hfa14);
    myprintf("%hfa12 %hfa14 %hfa14 %hfa14", hfa12, hfa14, hfa14, hfa14);
    myprintf("%hfa11 %hfa14 %hfa14 %hfa14", hfa11, hfa14, hfa14, hfa14);

    if (0) {
        myprintf("%hfa12 %hfa13 %hfa13 %hfa13 %hfa13 %hfa13",
                 hfa12, hfa13, hfa13, hfa13, hfa13, hfa13);
        myprintf("%hfa11 %hfa13 %hfa13 %hfa13 %hfa13 %hfa13",
                 hfa11, hfa13, hfa13, hfa13, hfa13, hfa13);
    }
    myprintf("%hfa12 %hfa13 %hfa13 %hfa13 %hfa13",
             hfa12, hfa13, hfa13, hfa13, hfa13);
    myprintf("%hfa11 %hfa13 %hfa13 %hfa13 %hfa13",
             hfa11, hfa13, hfa13, hfa13, hfa13);
    myprintf("%hfa13 %hfa13 %hfa13 %hfa13",
             hfa13, hfa13, hfa13, hfa13);

    myprintf("%hfa14 %hfa12 %hfa12 %hfa12 %hfa12",
             hfa14, hfa12, hfa12, hfa12, hfa12);
    myprintf("%hfa13 %hfa12 %hfa12 %hfa12 %hfa12",
             hfa13, hfa12, hfa12, hfa12, hfa12);

    myprintf("%hfa14 %hfa12 %hfa11 %hfa11 %hfa11 %hfa11",
             hfa14, hfa12, hfa11, hfa11, hfa11, hfa11);
}

void pll(unsigned long long x)
{
    printf("%llx\n", x);
}

void movi(void)
{
    printf("MOVI:\n");
    pll(0);
    pll(0xabcd);
    pll(0xabcd0000);
    pll(0xabcd00000000);
    pll(0xabcd000000000000);
    pll(0xffffabcd);
    pll(0xabcdffff);
    pll(0xffffffffffffabcd);
    pll(0xffffffffabcdffff);
    pll(0xffffabcdffffffff);
    pll(0xabcdffffffffffff);
    pll(0xaaaaaaaa);
    pll(0x5555555555555555);
    pll(0x77777777);
    pll(0x3333333333333333);
    pll(0xf8f8f8f8);
    pll(0x1e1e1e1e1e1e1e1e);
    pll(0x3f803f80);
    pll(0x01ff01ff01ff01ff);
    pll(0x007fffc0);
    pll(0x03fff80003fff800);
    pll(0x0007fffffffffe00);

    pll(0xabcd1234);
    pll(0xabcd00001234);
    pll(0xabcd000000001234);
    pll(0xabcd12340000);
    pll(0xabcd000012340000);
    pll(0xabcd123400000000);
    pll(0xffffffffabcd1234);
    pll(0xffffabcdffff1234);
    pll(0xabcdffffffff1234);
    pll(0xffffabcd1234ffff);
    pll(0xabcdffff1234ffff);
    pll(0xabcd1234ffffffff);

    pll(0xffffef0123456789);
    pll(0xabcdef012345ffff);

    pll(0xabcdef0123456789);
}

static uint32_t addip0(uint32_t x) { return x + 0; }
static uint64_t sublp0(uint64_t x) { return x - 0; }
static uint32_t addip123(uint32_t x) { return x + 123; }
static uint64_t addlm123(uint64_t x) { return x + -123; }
static uint64_t sublp4095(uint64_t x) { return x - 4095; }
static uint32_t subim503808(uint32_t x) { return x - -503808; }
static uint64_t addp12345(uint64_t x) { return x + 12345; }
static uint32_t subp12345(uint32_t x) { return x - 12345; }

static uint32_t mvni(uint32_t x) { return 0xffffffff - x; }
static uint64_t negl(uint64_t x) { return 0 - x; }
static uint32_t rsbi123(uint32_t x) { return 123 - x; }
static uint64_t rsbl123(uint64_t x) { return 123 - x; }

static uint32_t andi0(uint32_t x) { return x & 0; }
static uint64_t andlm1(uint64_t x) { return x & -1; }
static uint64_t orrl0(uint64_t x) { return x | 0; }
static uint32_t orrim1(uint32_t x) { return x | -1; }
static uint32_t eori0(uint32_t x) { return x ^ 0; }
static uint64_t eorlm1(uint64_t x) { return x ^ -1; }
static uint32_t and0xf0(uint32_t x) { return x & 0xf0; }
static uint64_t orr0xf0(uint64_t x) { return x | 0xf0; }
static uint64_t eor0xf0(uint64_t x) { return x ^ 0xf0; }

static uint32_t lsli0(uint32_t x) { return x << 0; }
static uint32_t lsri0(uint32_t x) { return x >> 0; }
static int64_t asrl0(int64_t x) { return x >> 0; }
static uint32_t lsli1(uint32_t x) { return x << 1; }
static uint32_t lsli31(uint32_t x) { return x << 31; }
static uint64_t lsll1(uint64_t x) { return x << 1; }
static uint64_t lsll63(uint64_t x) { return x << 63; }
static uint32_t lsri1(uint32_t x) { return x >> 1; }
static uint32_t lsri31(uint32_t x) { return x >> 31; }
static uint64_t lsrl1(uint64_t x) { return x >> 1; }
static uint64_t lsrl63(uint64_t x) { return x >> 63; }
static int32_t asri1(int32_t x) { return x >> 1; }
static int32_t asri31(int32_t x) { return x >> 31; }
static int64_t asrl1(int64_t x) { return x >> 1; }
static int64_t asrl63(int64_t x) { return x >> 63; }

void opi(void)
{
    int x = 1000;
    pll(addip0(x));
    pll(sublp0(x));
    pll(addip123(x));
    pll(addlm123(x));
    pll(sublp4095(x));
    pll(subim503808(x));
    pll(addp12345(x));
    pll(subp12345(x));
    pll(mvni(x));
    pll(negl(x));
    pll(rsbi123(x));
    pll(rsbl123(x));
    pll(andi0(x));
    pll(andlm1(x));
    pll(orrl0(x));
    pll(orrim1(x));
    pll(eori0(x));
    pll(eorlm1(x));
    pll(and0xf0(x));
    pll(orr0xf0(x));
    pll(eor0xf0(x));
    pll(lsli0(x));
    pll(lsri0(x));
    pll(asrl0(x));
    pll(lsli1(x));
    pll(lsli31(x));
    pll(lsll1(x));
    pll(lsll63(x));
    pll(lsri1(x));
    pll(lsri31(x));
    pll(lsrl1(x));
    pll(lsrl63(x));
    pll(asri1(x));
    pll(asri31(x));
    pll(asrl1(x));
    pll(asrl63(x));
}

void pcs(void)
{
    arg();
    ret();
    stdarg();
    movi();
    opi();
    randomized();
}

int main()
{
    pcs();
    return 0;
}
