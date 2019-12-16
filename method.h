#ifndef _METHOD_H_
#define _METHOD_H_

#include <stdlib.h>
typedef struct Method {
    enum { GET, POST } meth;
    uint32_t check;
} Method;

Method *method_init();
void method_free(Method *meth);
void method_parser(Method *meth, uint8_t *token);
void method_tostring(Method *meth);

#endif
