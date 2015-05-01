#include <stdio.h>
#include <stdarg.h>

void myprintf(const char *format,
             unsigned long arg1,
             unsigned long arg2,
             unsigned long arg3,
             unsigned long arg4,
             unsigned long arg5,
             unsigned long arg6,
             unsigned long arg7,
             ...)
{
  va_list ap;

  va_start(ap, arg7);

  unsigned long arg8 = va_arg(ap, unsigned long);

  if (arg8 == 8)
      printf("OK\n");
  else
      printf("NOT OK\n");

  va_end(ap);
}

int main(void)
{
  myprintf("%ld %ld %ld %ld  %ld %ld %ld %ld\n",
           1, 2, 3, 4,
           5, 6, 7, 8);

  return 0;
}
