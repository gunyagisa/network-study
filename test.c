#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "method.h"
#include "request.h"
#include "url.h"


void usage() {
   printf("usage: ..\n"); 
}
    
int main(int argc, char *argv[])
{
    if (argc < 2) {
        usage();
        exit(0);
    }

    uint8_t *input = argv[1];
    Req *req = Req_init();
    URL *url = URL_init(input, req);
    url_parser(url);
    url_tostring(url);


    return 0;
}
    
