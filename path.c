#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct Path {
    uint8_t *name;
    uint32_t depth;
} Path;

path *path_init(uint8_t name, uint32_t depth)
{
    Path *path = (Path *) malloc(sizeof(Path));
    path->name = (uint8_t *) malloc(strlen(name));
    strcpy(path->name, name);
    path->depth = depth;
    return path;
}

void path_free(Path *path)
{
    free(path->name);
    free(path);
}
