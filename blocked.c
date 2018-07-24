#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 1000 

#define COMMAND(comm) fun_##comm(void){\
return 90;}\

COMMAND(int)


typedef struct blocked_int
{
    int block[BLOCK_SIZE];
    struct blocked_int * next;
} Block;

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
    int k = fun_int();
    Block * b = new_block();
    setitem(b,0,5);
    setitem(b,257,k);
    printf("%d\n",getitem(b,257));
    setitem(b,600,8);
    printf("yeet %d\n",getitem(b,600));
    setitem(b,270,7);
    for(int i = 0; i < 10000; ++i)
    {
        setitem(b,i,i);
        k = getitem(b,i);
    }
    printf("%d\n",getitem(b,5000));
    return 0;
}


