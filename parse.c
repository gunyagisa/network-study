#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parse.h"

void divide_str(char **str, char **buf) {
    char tmp[strlen(*str) + 1];
    int i = 0;
    while (**str != ' ' && **str != '\0') {
        if (**str == '\n') {
            *str = *str + 1;
            continue;
        }
        tmp[i] = **str;
        i++;
        *str = *str + 1;
    }
    if (**str == ' ')
        *str = *str + 1;
    tmp[i] = '\0';

    *buf = malloc(strlen(tmp) + 1);
    strcpy(*buf, tmp);
}


void parse(char *str, struct Request *req) {
    divide_str(&str, &(req->method));
    divide_str(&str, &(req->url));
    divide_str(&str, &(req->http_version));
}

void show_req(struct Request *req) {
    printf("Method: %s\n", req->method);
    printf("URL: %s\n", req->url);
    printf("http_version: %s\n", req->http_version);
}

void free_req(struct Request *req) {
    free(req->method);
    free(req->url);
    free(req->http_version);
}

/*
int main() {
    char *str = "GET http://google.com HTTP/1.1";
    struct Request req;

    parse(str, &req);
    show_req(&req);
    free_req(&req);
}
*/
