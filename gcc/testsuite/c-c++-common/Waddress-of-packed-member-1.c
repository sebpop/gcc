/* { dg-do compile } */
/* { dg-options "-Waddress-of-packed-member" } */

struct t {
  char a;
  int b;
  int *c;
  int d[10];
} __attribute__((packed));

struct t t0;
struct t t10[10];
struct t t100[10][10];
struct t *t1;
struct t **t2;
struct t *bar();
struct t (*baz())[10];
struct t (*bazz())[10][10];
int *i1;
__UINTPTR_TYPE__ u1;
__UINTPTR_TYPE__ baa();

void foo (void)
{
  t1 = &t0;                    /* { dg-bogus "may result in an unaligned pointer value" } */
  t1 = t10;                    /* { dg-bogus "may result in an unaligned pointer value" } */
  t2 = &t1;                    /* { dg-bogus "may result in an unaligned pointer value" } */
  t2 = t2;                     /* { dg-bogus "may result in an unaligned pointer value" } */
  t2 = (struct t**)t2;         /* { dg-bogus "may result in an unaligned pointer value" } */
  t1 = (struct t*)t2;          /* { dg-bogus "may result in an unaligned pointer value" } */
  t1 = bar();                  /* { dg-bogus "may result in an unaligned pointer value" } */
  t1 = (struct t*) baz();      /* { dg-bogus "may result in an unaligned pointer value" } */
  t1 = (struct t*) bazz();     /* { dg-bogus "may result in an unaligned pointer value" } */
  t1 = *baz();                 /* { dg-bogus "may result in an unaligned pointer value" } */
  t1 = **bazz();               /* { dg-bogus "may result in an unaligned pointer value" } */
  t1 = (struct t*) baa();      /* { dg-bogus "may result in an unaligned pointer value" } */
  t2 = (struct t**) baa();     /* { dg-bogus "may result in an unaligned pointer value" } */
  i1 = t0.c;                   /* { dg-bogus "may result in an unaligned pointer value" } */
  i1 = t1->c;                  /* { dg-bogus "may result in an unaligned pointer value" } */
  i1 = t10[0].c;               /* { dg-bogus "may result in an unaligned pointer value" } */
  u1 = (__UINTPTR_TYPE__) &t0; /* { dg-bogus "may result in an unaligned pointer value" } */
  u1 = (__UINTPTR_TYPE__) t1;  /* { dg-bogus "may result in an unaligned pointer value" } */
  t2 = (struct t**) t10;     /* { dg-warning "may result in an unaligned pointer value" } */
  t2 = (struct t**) t100;    /* { dg-warning "may result in an unaligned pointer value" } */
  t2 = (struct t**) t1;      /* { dg-warning "may result in an unaligned pointer value" } */
  t2 = (struct t**) bar();   /* { dg-warning "may result in an unaligned pointer value" } */
  t2 = (struct t**) baz();   /* { dg-warning "may result in an unaligned pointer value" } */
  t2 = (struct t**) bazz();  /* { dg-warning "may result in an unaligned pointer value" } */
  i1 = &t0.b;                /* { dg-warning "may result in an unaligned pointer value" } */
  i1 = &t1->b;               /* { dg-warning "may result in an unaligned pointer value" } */
  i1 = &t10[0].b;            /* { dg-warning "may result in an unaligned pointer value" } */
  i1 = t0.d;                 /* { dg-warning "may result in an unaligned pointer value" } */
  i1 = t1->d;                /* { dg-warning "may result in an unaligned pointer value" } */
  i1 = t10[0].d;             /* { dg-warning "may result in an unaligned pointer value" } */
}
