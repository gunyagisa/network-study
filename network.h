#ifndef NETWORK_H_
#define NETWORK_H_

#include "parse.h"

void GET_request(int sock, struct Request *req);
void POST_request(int sock, struct Request *req);
void send_400(int sock);
void send_200(int sock);

void error_handler();

#endif
