#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 1000 

#define COMMAND(com) struct blocked_##com{\
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
    return 0;\
}\


COMMAND(float)
COMMAND(double)

typedef struct blocked_int
{
    int block[BLOCK_SIZE];
    struct blocked_int * next;
} Block;
//COMMAND(int)

typedef struct blocked_int Block;

Block * new_block();

void setitem(Block * in, 
            int indx,
            int el)
{
    if(indx < BLOCK_SIZE)
    {
        in->block[indx] = el;
        return;
    }
    if(in->next==NULL)
    {
        in->next = new_block();
        setitem(in->next,indx-BLOCK_SIZE,el);
        return;
    }
    if(in->next!=NULL)
    {
        setitem(in->next,indx-BLOCK_SIZE,el);
        return;
    }
}

int getitem(Block * in, 
            int indx)
{
    if(indx < BLOCK_SIZE)
    {
        return in->block[indx];
    }
    if(in->next!=NULL)
    {
        return getitem(in->next,indx-BLOCK_SIZE);
    }
    return 0;
}



Block * new_block(void)
{
    Block * new = NULL;
    new = (Block *)malloc(sizeof(Block));   
    new->next = NULL;
    return new;
}


int main()
{
    int k ; 
    Block * b = new_block();
    struct blocked_float * b2 = new_block_float();
    struct blocked_double* b3 = new_block_double();
    setitem_double(b3,8,9.0);
    printf("%f\n",getitem_double(b3,8));
    for(int i = 0; i < 10000; ++i)
    {
        setitem(b,i,2);
    }
    k = 0;
    for(int i = 0; i < 10000; ++i)
    {
        k+=getitem(b,i);
    }
    printf("%d\n",k);
    return 0;
}


