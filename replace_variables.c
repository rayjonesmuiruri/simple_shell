#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
char *replace_variables(char *command, int last_command_status, pid_t shell_pid) {
    char *replaced_command = malloc(strlen(command) * sizeof(char));
    if (replaced_command == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    char *variable_name;
    while ((variable_name = strstr(command, "$")) != NULL) {
        if (strncmp(variable_name, "$LAST_COMMAND_STATUS", 20) == 0) {
            sprintf(replaced_command, "%.*s%d%s", (int)(variable_name - command), command,
                    last_command_status, variable_name + 20);
        } else if (strncmp(variable_name, "$SHELL_PID", 10) == 0) {
            sprintf(replaced_command, "%.*s%d%s", (int)(variable_name - command), command,
                    shell_pid, variable_name + 10);
        } else {
            perror("Unknown variable");
            exit(EXIT_FAILURE);
        }
        command = replaced_command;
    }

    return replaced_command;
}

int main() {
    int last_command_status = 0;
    pid_t shell_pid = getpid();
    char command[] = "echo $LAST_COMMAND_STATUS is the exit status. My pid is $SHELL_PID";
    char *replaced_command = replace_variables(command, last_command_status, shell_pid);
    printf("Replaced command: %s\n", replaced_command);
    free(replaced_command);
    return 0;
}
