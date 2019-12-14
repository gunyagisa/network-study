#include "method.h"
#include <string.h>

void method_parser(Req *req, uint32_t *token)
{
    if(strcmp("GET", token))
        req->meth = GET;
    else if (strcmp("POST", token))
            req->meth = POST;
    else {
        fprintf(stderr, "invalid method\n");
        req->meth = NULL;
        exit(1);
    }
}
        
            
