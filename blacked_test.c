#include <stdlib.h>
#include <stdio.h>

#define voodoo(dtype) struct dt_##dtype{\
    dtype data[10];\
    dtype (*get)(struct dt_##dtype, int);\
    void  (*set)(struct dt_##dtype, int, dtype el);\
};\
dtype get_##dtype(struct dt_##dtype d, int indx){\
    return d.data[indx];\
}\
struct dt_##dtype new_##dtype(void){\
   struct dt_##dtype d;\
   d.get = get_##dtype;\
   return d;\
}\

voodoo(int)
voodoo(float)

#undef voodoo


#define getter(class,indx) (class.get(class,indx))

int main()
{
   struct dt_int e4 = new_int();
   e4.data[4] = 8;
   printf("%d\n",getter(e4,4));
   struct dt_float e3 = new_float();
   e3.data[3] = 8.8;
   printf("%f\n",getter(e3,3));
   return 1;
}
