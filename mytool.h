#include <stdio.h>

#define DEVIDE_SIZE 16

void dump(const unsigned char *buffer, const unsigned int len) {
    for (int i = 0;i < len;i++) {
        printf("%02x ", buffer[i]);
        if (i % DEVIDE_SIZE == DEVIDE_SIZE - 1) {
            printf("| ");
            for (int j = i - (DEVIDE_SIZE - 1);j <= i;j++) {
                if (buffer[j] >= 0x20 && buffer[j] <= 0x7e)
                    printf("%c", buffer[j]);
                else
                    printf(".");
            }
            printf("\n");
        } else if (i == len - 1) {
            for (int j = 0;j < DEVIDE_SIZE - ((i % DEVIDE_SIZE) + 1);j++)
                printf(".. ");
            printf("| ");
            for (int j = i / DEVIDE_SIZE * DEVIDE_SIZE;j <= i;j++) {
                if (buffer[j] >= 0x20 && buffer[j] <= 0x7e)
                    printf("%c", buffer[j]);
                else
                    printf(".");
            }
            printf("\n");
        }
    }
}

