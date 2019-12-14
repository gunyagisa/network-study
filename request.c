#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "request.h"
#include "url.h"

Req *Req_init(const uint8_t *request, URL *url, Method *meth)
{
    Req *req = (Req *) malloc(sizeof(Req));
    size_t size = strlen(request);
    req->req_url = url;
    req->req_method = meth;
    req->check = 0;
    return req;
}

void req_parser(Req *req)
{
    uint8_t tmp[strlen(req->request)];
    char *saveptr;
    strcpy(tmp, req->request);

    uint8_t *token;
    token = strtok_r(tmp, " ", &saveptr);
    method_parser(req->req_method, token);

    strcpy(req->req_url->url, saveptr);
    url_parser(req->req_url);

    if (req->req_url->check == 1 && req->req_method->check == 1)
        req->check = 1;
    else {
        fprintf(stderr, "[req_parser] parse failed\n");
        exit(1);
    }
}

void req_tostring(Req *req)
{
    printf("Request:\n");
    url_tostring(req->req_url);
    method_tostring(req->req_method);
    printf("status code: %d\n", req->status);
}
    

    
