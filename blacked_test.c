#include <stdlib.h>
#include <stdio.h>

#define voodoo(dtype) typedef struct dt_##dtype{\
    dtype (*get)(int);\
} Eric_##dtype;

voodoo(int)

#undef voodoo

#define getter(class,indx) (class.data[indx])


#define make_class(dtype) typedef struct hold_##dtype{\
    dtype data[10];\
    dtype (*get)( int);\
}Eric3;\

make_class(int);

#undef make_class

typedef struct holder{
   void (*f)(int);
} Eric;

void test(int a){
   printf("Haha, yes\n");
}

int test2(int a){
   return 5;
}

void doit(Eric e){
   e.f(7);
}


int main()
{
   Eric e;
   e.f = test;
   doit(e);
   Eric_int e2;
   e2.get = test2;
   int a = e2.get(5); 
   printf("%d\n",a);
   Eric3 e3;
   e3.data[3] = 6;
   int zz = getter(e3,3);
   printf("%d\n",zz);
   return 1;
}
