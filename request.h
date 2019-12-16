#ifndef _REQUEST_H_
#define _REQUEST_H_

#include <stdint.h>
#include "url.h"
#include "method.h"

typedef struct Req {
    uint8_t *request;
    URL *req_url;
    Method *req_method;
    uint32_t status;
    uint8_t check;
} Req;

Req *Req_init(const uint8_t *request, URL *url, Method *meth);
void req_free(Req *req);
void req_parser(Req *req);
void req_tostring(Req *req);

#endif
