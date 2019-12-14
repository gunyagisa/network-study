#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "method.h"

Method *method_init()
{
    Method *meth = (Method *) malloc(sizeof(Method));
    meth->check = 0;
    return meth;
}
void method_parser(Method *meth, uint8_t *token)
{
    if(strcmp("GET", token))
        meth->meth = GET;
    else if (strcmp("POST", token))
            meth->meth = POST;
    else {
        fprintf(stderr, "invalid method\n");
        exit(1);
    }
}

void method_tostring(Method *meth)
{
    if (meth->check != 1) {
        fprintf(stderr, "[method_tostring]parse not finish\n");
        exit(1);
    }
    if (meth->meth == GET)
        printf("method: %s\n", "GET");
    else if (meth->meth == POST)
        printf("method %s\n", "POST");
    else
        printf("method: unrecognized status code\n");
}
        
            
