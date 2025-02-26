// { dg-do run }
// { dg-options "-O -fopenmp-simd -ftree-loop-if-convert -fno-ssa-phiopt" }

#pragma omp declare simd simdlen(4) notinbranch
__attribute__((noinline)) int
foo (double c1, double c2)
{
  double z1 = c1, z2 = c2;
  int res = 100, i;

  for (i = 0; i < 5; i++)
    {
      res = (z1 * z1 + z2 * z2 > 4.0) ? (i < res ? i : res) : res;
      z1 = c1 + z1 * z1 - z2 * z2;
      z2 = c2 + 2.0 * z1 * z2;
      c1 += 0.5;
      c2 += 0.5;
    }
  return res;
}
// { dg-warning "GCC does not currently support mixed size types for 'simd' functions" "" { target aarch64-*-* } .-15 }

__attribute__((noinline, noclone)) void
bar (double *x, double *y)
{
  asm volatile ("" : : "rm" (x), "rm" (y) : "memory");
}

int
main ()
{
  int i;
  double c[4] = { 0.0, 1.0, 0.0, 1.0 };
  double d[4] = { 0.0, 1.0, 2.0, 0.0 };
  int e[4];
  bar (c, d);
#pragma omp simd safelen(4)
  for (i = 0; i < 4; i++)
    e[i] = foo (c[i], d[i]);
  if (e[0] != 3 || e[1] != 1 || e[2] != 1 || e[3] != 2)
    __builtin_abort ();
  return 0;
}
