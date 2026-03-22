#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define MAX 100

int main(int argc, char *argv[]) {
    char buf[MAX];
    int i = 0;
    char c;

    while (read(0, &c, 1) > 0) {
        if (c == '\n') {
            buf[i] = '\0';

            if (fork() == 0) {
                char *args[MAX];
                
                int j;
                for (j = 1; j < argc; j++) {
                    args[j-1] = argv[j];
                }

                args[j-1] = buf;
                args[j] = 0;

                exec(args[0], args);

                printf("exec failed\n");
                exit(1);
            } else {
                wait(0);
            }

            i = 0;
        } else {
            buf[i++] = c;
        }
    }

    exit(0);
}
