#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "static_blocks.h"

typedef struct point{
    int x;
    int y;
} Point;

dynamic_block(float);
dynamic_block(int);
dynamic_block(Point);

typedef char* str;

dynamic_block(str);

int main(){
    float k ;
    int   k2;
    Point p = {1,2};
    struct blocked_float * b  = new_block_float();
    struct blocked_int   * b2 = new_block_int();
    struct blocked_Point * b3 = new_block_Point();
    struct blocked_str   * str_block = new_block_str();
    char hello[] = "Hello!";
    str_block->block[0] = (char*)malloc(sizeof(hello));
    str_block->block[0] = hello;
    printf("%s\n",str_block->block[0]);
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
    printf("length = %d\n",b2->length);
    return 0;
}
