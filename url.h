#ifndef _URLPARSER_H_
#define _URLPARSER_H_

typedef struct URL {
    uint8_t *url;
    uint8_t *scheme;
    uint8_t *host;
    uint16_t port;
    uint8_t *path;
    uint16_t check;
} URL;

void url_parser(URL *u);
void url_tostring(URL *url);
URL *URL_init(const uint8_t *str, Req *req);

#endif
