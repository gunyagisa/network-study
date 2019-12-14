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

    //check
    url->check = 1;
}

void url_tostring(URL *url)
{
    if (url->check == 0) {
        fprintf(stderr, "[url_tostring]not parsed\n");
        exit(1);
    }
    printf("url: %s\n", url->url);
    printf("Scheme: %s\n", url->scheme);
    printf("port: %d\n", url->port);
    printf("path: %s\n", url->path);
}

URL *URL_init(const uint8_t *str)
{
    URL *url = (URL *) malloc(sizeof(URL));
    size_t size = strlen((char *)str);
    url->url = (uint8_t *) malloc(size);
    strcpy(url->url, str);
    url->path = NULL;
    url->host = NULL;
    url->check = 0;
    return url;
}
