#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum Method { GET, POST } Method;

typedef struct URL {
    uint8_t *url;
    uint8_t *scheme;
    uint8_t *host;
    uint16_t port;
    uint8_t *path;
} URL;

typedef struct Req {
    struct URL *req_url;
    enum Method meth;
    uint32_t status;
} Req;


void url_parser(URL *u)
{
    uint8_t tmp[strlen(u->url)];
    strcpy((char *)tmp, (char *)u->url);
    char *saveptr, *token;

    token = strtok_r((char *)tmp, ":", &saveptr);
    u->scheme = malloc(strlen(token));
    strcpy(u->scheme, token);
    
    token = strtok_r(NULL, "/", &saveptr);
    u->host = malloc(strlen(token));
    strcpy(u->host, token);

    u->path = malloc((uint8_t *) saveptr - tmp + 1);
    strcpy(u->path, saveptr);
}

void URL_tostring(URL *url)
{
    if (url->host == NULL)
        exit(1);
    printf("url: %s\n", url->url);
    printf("Scheme: %s\n", url->scheme);
    printf("port: %d\n", url->port);
    printf("path: %s\n", url->path);
}


Req *Req_init()
{
    Req *req = (Req *) malloc(sizeof(Req));
    return req;
}

URL *URL_init(const uint8_t *str, Req *req)
{
    URL *url = (URL *) malloc(sizeof(URL));
    req->req_url = url;
    size_t size = strlen((char *)str);
    url->url = (uint8_t *) malloc(size);
    url->url = str;
    url->path = NULL;
    url->host = NULL;
    return url;
}

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
    URL_tostring(url);


    return 0;
}
    
