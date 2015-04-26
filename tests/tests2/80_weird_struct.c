/*
 * This test sometimes works. It probably fails to work in most cases,
 * causing spurious segfaults, but the idea is that we put a 12-byte
 * structure in the last 12 bytes of valid memory; if our structure
 * passing code is correct, we can dereference it, but if we
 * incorrectly try to read 16 bytes, we'll get a segfault.
 */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

typedef struct shortstruct_s {
    float x;
    float y;
    float z;
} shortstruct;

void f(shortstruct s)
{
}

void segv_handler(int dummy)
{
    printf("SEGV OK\n");
    fflush(stdout);
    exit(0);
}

struct sigaction sa = {
    segv_handler,
};

int main(void)
{
    brk((void *)0x8000000);
    void *end = sbrk(0);
    shortstruct *s = (shortstruct *)(end-12);

    f(*s);

    printf("OK\n"); /* if we fail, it's most likely with a segfault */
    fflush(stdout);
    sigaction(SIGSEGV, &sa, NULL);

    *(int *)end = 0;

    return 1;
}
