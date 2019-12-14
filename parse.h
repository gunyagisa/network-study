#ifndef PARSE_H_
#define PARSE_H_

struct Request {
    char *method;
    char *url;
    char *http_version;
};

void divide_str(char **str, char **buf);
void parse(char *str, struct Request *req);
void show_req(struct Request *req);

#endif
