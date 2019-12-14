#include "url.h"

Req *Req_init(const uint32_t *request, URL *url)
{
    Req *req = (Req *) malloc(sizeof(Req));
    size_t size = strlen(request);
    req->req-url = url;
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
    method_parser(req, token);

    strcpy(req->req_url->url, saveptr);
    url_parser(req->req_url);
}

void req_tostring(Req *req)
{
    printf("Request:\n");
    

    
