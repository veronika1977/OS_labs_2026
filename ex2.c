#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;
    int n = atoi(argv[1]);
    
    for (int i = 0; i < n; i++) {
        fork();
        sleep(5);
    }
    
    while (wait(NULL) > 0);
    return 0;
}

