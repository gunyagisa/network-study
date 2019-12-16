#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "url.h"

URL *URL_init()
{
    URL *url = (URL *) malloc(sizeof(URL));
    url->path = NULL;
    url->host = NULL;
    url->check = 0;
    return url;
}

void url_free(URL *url)
{
    free(url->url);
    free(url->scheme);
    free(url->host);
    free(url->path);
}

void url_parser(URL *u)
{
    printf("%s\n", u->url);
    uint8_t tmp[strlen(u->url)];
    strcpy((char *)tmp, (char *)u->url);
    char *saveptr, *token;

    //scheme parse
    token = strtok_r((char *)tmp, ":", &saveptr);
    u->scheme = malloc(strlen(token));
    strcpy(u->scheme, token);
    
    //host parse
    token = strtok_r(NULL, "/", &saveptr);
    u->host = malloc(strlen(token));
    strcpy(u->host, token);

    //path parse
    token = strtok_r(NULL, ":", &saveptr);
    u->path = malloc(strlen(token));
    strcpy(u->path, token);

    //port parse
    u->port = atoi(saveptr);

    //check
    u->check = 1;
}

void url_tostring(URL *url)
{
    if (url->check == 0) {
        fprintf(stderr, "[url_tostring]not parsed\n");
        exit(1);
    }
    printf("url: %s\n", url->url);
    printf("scheme: %s\n", url->scheme);
    printf("port: %d\n", url->port);
    printf("path: %s\n", url->path);
}

