#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 256 

typedef int bool;
#define true 1
#define false 0 

#define dynamic_block(dtype) struct blocked_##dtype{\
    dtype block[BLOCK_SIZE];\
    struct blocked_##dtype * next;\
    dtype (*get)(struct blocked_##dtype *, int);\
    void  (*set)(struct blocked_##dtype *, int, dtype el);\
};\
struct blocked_##dtype * new_block_##dtype(void);\
void setitem_##dtype(struct blocked_##dtype * in, int indx, dtype el){\
    if(indx < BLOCK_SIZE){\
        in->block[indx] = el;\
    }\
    else if(in->next==NULL){\
        in->next = new_block_##dtype();\
        setitem_##dtype(in->next,indx-BLOCK_SIZE,el);\
    }\
    else if(in->next!=NULL){\
        setitem_##dtype(in->next,indx-BLOCK_SIZE,el);\
    }\
}\
\
dtype getitem_##dtype(struct blocked_##dtype * in, int indx){\
    if(indx < BLOCK_SIZE){\
        return in->block[indx];\
    }\
    if(in->next!=NULL){\
        return getitem_##dtype(in->next,indx-BLOCK_SIZE);\
    }\
}\
struct blocked_##dtype * new_block_##dtype(void){\
    struct blocked_##dtype * new = (struct blocked_##dtype *)malloc(sizeof(struct blocked_##dtype));\
    new->next = NULL;\
    new->get = getitem_##dtype;\
    new->set = setitem_##dtype;\
    return new;\
}\
\

#define getter(class, ind) (class->get(class,ind))
#define setter(class, ind, el) (class->set(class,ind,el))
#define swap(class1,class2,ind) (setter(class1,ind,getter(class2,ind)))

typedef struct point{
    int x;
    int y;
} Point;

dynamic_block(float);
dynamic_block(int);
dynamic_block(Point);

int main(){
    float k ;
    int   k2;
    Point p = {1,2};
    struct blocked_float * b  = new_block_float();
    struct blocked_int   * b2 = new_block_int();
    struct blocked_Point * b3 = new_block_Point();
    setter(b3,0,p);
    p = getter(b3,0);
    for(int i = 0; i < 10000; ++i)
    {
        setter(b2,i,3);
        setter(b,i,getter(b2,i));
    }
    k  = 0.0;
    k2 = 0;
    for(int i = 0; i < 10000; ++i)
    {
        k2+=getter(b2,i);
        k+=getter(b,i);
    }
    printf("sum %f\n",k);
    printf("sum %d\n",k2);
    return 0;
}