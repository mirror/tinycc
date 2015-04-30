#include <stdio.h>

#define A(a,b...) g(a,##b,##b)
#define B(x...) x
#define C   \

#define D(x,y) x ## y
#define E(x,y,z) x ## y ## z
#define F(x) x
#define G C

#define STRINGIFY2(x) #x
#define STRINGIFY(x) STRINGIFY2(x)

int main(void)
{
  printf("%s\n", STRINGIFY()); // should produce the empty string
  printf("%s\n", STRINGIFY(C)); // should produce the empty string
  printf("%s\n", STRINGIFY(
                           A(a,)
                           A(a,b)
                           A(a,b,c)
                           )); // should produce g(a ) g(a,b,b)g(a,b,c,b,c)
  printf("%s\n", STRINGIFY(B())); // should produce the empty string
  printf("%s\n", STRINGIFY(B(C))); // should produce the empty string
  printf("%s\n", STRINGIFY(D(,))); // should produce the empty string
  printf("%s\n", STRINGIFY(E(1,,))); // should produce 1
  printf("%s\n", STRINGIFY(E(,2,))); // should produce 2
  printf("%s\n", STRINGIFY(E(,,3))); // should produce 3
  printf("%s\n", STRINGIFY(E(1,2,3))); // should produce 123

  // should produce g(a ) g(a )g(a )g(a )g(a )
  printf("%s\n", STRINGIFY(A(a,F()) A(a,C) A(a,G) A(a,) A(a)));

  return 0;
}
