#include "shell.h"

int change_directory(char **args) {
    char *home_dir = getenv("HOME");
    char *old_pwd = getenv("PWD");

    if (args[1] == NULL || strcmp(args[1], "~") == 0) {
        if (chdir(home_dir) == -1) {
            perror("cd");
            return 1;
        }
    } else if (strcmp(args[1], "-") == 0) {
        if (old_pwd == NULL) {
            fprintf(stderr, "cd: OLDPWD not set\n");
            return 1;
        }
        if (chdir(old_pwd) == -1) {
            perror("cd");
            return 1;
        }
        printf("%s\n", old_pwd);
    } else {
        if (chdir(args[1]) == -1) {
            perror("cd");
            return 1;
        }
    }

    char cwd[MAX_INPUT_LENGTH];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd");
        return 1;
    }

    if (setenv("PWD", cwd, 1) == -1) {
        perror("setenv");
        return 1;
    }

    return 0;
}
