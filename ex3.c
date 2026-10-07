#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int read_input(char *buf, int size) {
    printf("my_shell> ");
    fflush(stdout);
    if (!fgets(buf, size, stdin)) return 0;
    buf[strcspn(buf, "\n")] = 0;
    if (strcmp(buf, "exit") == 0) return 0;
    return 1;
}

int main() {
    char input[100];
    while (read_input(input, sizeof(input))) {
        if (strlen(input) == 0) continue;

        char cmd[50] = {0}, arg[50] = {0}, bg_char[10] = {0};
        int num = sscanf(input, "%s %s %s", cmd, arg, bg_char);
        int bg = (strcmp(bg_char, "&") == 0 || strcmp(arg, "&") == 0);

        char *args[3];
        args[0] = cmd;
        args[1] = (num > 1 && strcmp(arg, "&") != 0) ? arg : NULL;
        args[2] = NULL;

        if (fork() == 0) {
            execvp(cmd, args);
            printf("Command not found!\n");
            exit(1);
        } else if (!bg) {
            wait(NULL);
        }
    }
    return 0;
}

