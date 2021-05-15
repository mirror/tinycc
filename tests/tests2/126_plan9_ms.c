#include <stdio.h>

typedef struct { int x1, x2, x3; } Inner;
typedef struct {
    int x0;
    Inner;
    // int Inner; // an error with -fplan9-extensions, but not with -fms-extensions
} Outer;

void set_x2(Inner *i) {
    i->x2 = 2;
}

void warn() {
    struct { const Inner; } tmp;
    Inner *i = &tmp; /* warning: assignment discards qualifiers from pointer target type */
}

int main() {
    Outer o;
    Inner *i = &o;
    i->x1 = 1;
    set_x2(&o);
    o.x3 = 3;
    o.x0 = 10;
    printf("%d\n", o.x1 + o.x2 + o.x3);
    return 0;
}
