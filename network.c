#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <error.h>
#include <signal.h>

#include "mytool.h"
#include "network.h"
#include "parse.h"


#define PORT 9999



void catch_SIGCHLD(int signo) {
    pid_t child_pid = 0;
    do {
        int child_ret;
        child_pid = waitpid(-1, &child_ret, WNOHANG);
    } while (child_pid > 0);
}

void set_SIGCHLD(void) {
    struct sigaction act = {0};
    act.sa_handler = catch_SIGCHLD;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_NOCLDSTOP | SA_RESTART;
    sigaction(SIGCHLD, &act, NULL);
}

void socksend(const char *str, int sock) {
    int ret = send(sock, str, strlen(str), 0);
    if (ret == -1)
        error_handler();
}
    
void request_handler(char *str, struct Request *req, int sock) {
    parse(str, req);
    show_req(req);
    if (strcmp(req->method, "GET") == 0)
        GET_request(sock, req);
    else if (strcmp(req->method, "POST") == 0)
        POST_request(sock, req);
    else
        send_400(sock);
}

void GET_request(int sock, struct Request *req) {
    send_200(sock);
    printf("get\n");
}

void POST_request(int sock, struct Request *req) {
    send_200(sock);
    printf("post\n");
}

void send_400(int sock) {
    char *msg = "HTTP/1.1 400 Bad Request\n";
    socksend(msg, sock);
    printf("[Response]:%s", msg);
}
    
void send_200(int sock) {
    char *msg = "HTTP/1.1 200 OK\n";
    socksend(msg, sock);
    printf("[Response]:%s", msg);
}

void error_handler() {
    perror("[ERROR]");
    exit(1);
}


int main() {
    int sock;
    struct sockaddr_in addr = {0,};
    socklen_t yes = 1;


    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        error_handler();

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)); 

    if (bind(sock, (struct sockaddr *) &addr, sizeof(struct sockaddr)) == -1)
        error_handler();

    if (listen(sock, 5) == -1) 
        error_handler();

    struct sockaddr_in client_addr;
    socklen_t addrlen = sizeof(client_addr);

    int client;
    int pid;
    struct Request req[5];

    set_SIGCHLD();

    pid = fork();

    if (pid == 0) {
        printf("[Manager]:start to accept a client\n");
        char input[16];
        int id = 0;
        for (;;) {
            scanf("%16s %d", input, &id);
            if (strcmp(input, "kill") == 0) {
                if (id == 0) {
                    printf("[Manager]: exit program\n");
                    kill(0, SIGTERM);
                } else {
                    printf("[Manager]: kill a process (%d)\n", id);
                    kill(id, SIGTERM);
                }
            }
        }
    }

    for (int i = 0;i < 5;i++) {
        if ((client = accept(sock, (struct sockaddr *) &client_addr, &addrlen)) == -1) {
            error_handler();
        } else {
            pid = fork();
        }

        if (pid < 0)
            error_handler();

        if (pid == 0) {
            pid = getpid();

            printf("[%d]:connected from %s\n", pid, inet_ntoa(client_addr.sin_addr));

            u_char buffer[9000];
            int recv_len;

            for (;;) {
                memset(buffer, '\0', sizeof(buffer));
                recv_len = recv(client, buffer, sizeof(buffer), 0);
                if (recv_len == -1) {
                    error_handler();
                } else if (recv_len == 0) {
                    fprintf(stderr, "[%d]:finish\n", pid);
                    break;
                }

                printf("[%d]:recieved %d byte\n", pid, recv_len);
                dump(buffer, recv_len);
                request_handler(buffer, &(req[i]), client);
            }
            close(client);
            exit(0);
        }
    }
}
