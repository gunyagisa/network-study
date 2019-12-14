typedef struct Req {
    uint8_t *request;
    struct URL *req_url;
    enum Method meth;
    uint32_t status;
    uint8_t check;
} Req;
