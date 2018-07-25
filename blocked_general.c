#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 256 

#define dynamic_block(com) struct blocked_##com{\
    com block[BLOCK_SIZE];\
    struct blocked_##com * next;\
};\
\
struct blocked_##com * new_block_##com(void){\
    struct blocked_##com * new = NULL;\
    new = (struct blocked_##com *)malloc(sizeof(struct blocked_##com));\
    new->next = NULL;\
    return new;\
}\
\
void setitem_##com(struct blocked_##com * in, int indx, com el){\
    if(indx < BLOCK_SIZE){\
        in->block[indx] = el;\
        return;\
    }\
    if(in->next==NULL){\
        in->next = new_block_##com();\
        setitem_##com(in->next,indx-BLOCK_SIZE,el);\
        return;\
    }\
    if(in->next!=NULL){\
        setitem_##com(in->next,indx-BLOCK_SIZE,el);\
        return;\
    }\
}\
\
com getitem_##com(struct blocked_##com * in, int indx){\
    if(indx < BLOCK_SIZE){\
        return in->block[indx];\
    }\
    if(in->next!=NULL){\
        return getitem_##com(in->next,indx-BLOCK_SIZE);\
    }\
}\

typedef struct point{
    int x;
    int y;
} Point;

typedef struct __str{
    char value[256];
} String;

dynamic_block(float);
dynamic_block(double);
dynamic_block(int);
dynamic_block(char);
dynamic_block(String);

int main()
{
    float k ;
    struct blocked_float * b  = new_block_float();
    struct blocked_double* b2 = new_block_double();
    struct blocked_String * b3 = new_block_String();
    void * test;
    int * test2 = (int *)calloc(8,sizeof(int));
    test = test2;
    test2 = (int *)test;
    printf("%d\n",test2[0]);
    String s = {"Hello World"};
    setitem_String(b3,0,s);
    printf("%s\n",getitem_String(b3,0).value);
    for(int i = 0; i < 10000; ++i)
    {
        setitem_float(b,i,2);
    }
    k = 0.0;
    for(int i = 0; i < 10000; ++i)
    {
        k+=getitem_float(b,i);
    }
    printf("%f\n",k);
    return 0;
}


