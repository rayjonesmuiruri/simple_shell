#include "shell.h"

void execute_command(char *command, char **env, int *last_command_status, pid_t shell_pid) {
    char *modified_command = replace_variables(command, *last_command_status, shell_pid);
    char *args[MAX_INPUT_LENGTH / 2 + 1];
    int i = 0;
    char *token = strtok(modified_command, " \n");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " \n");
    }
    args[i] = NULL;

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        if (execve(args[0], args, env) == -1) {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    } else {
        int status;
        waitpid(pid, &status, 0);
        *last_command_status = WIFEXITED(status) ? WEXITSTATUS(status) : 1;
    }

    free(modified_command);
}
