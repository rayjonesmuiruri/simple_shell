#include "shell.h"
#include <unistd.h>
int main(void) {
    char input[MAX_INPUT_LENGTH];
    const char *prompt = "$ ";
    char *command;
	int last_command_status = 0;
    while (1) {
        printf("%s", prompt);

        if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) {
            if (feof(stdin)) {
                printf("\n");
                break;
            }
        }

        command = input;

        if (command == NULL)
            continue;

        if (is_exit_command(command))
            break;

        if (is_env_command(command)) {
            print_environment(environ);
            continue;
        }

        char *args[MAX_INPUT_LENGTH];
        int i = 0;
        args[i] = strtok(command, " ");
        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (set_environment_variable(args)) {
            continue;
        }

        if (unset_environment_variable(args)) {
            continue;
        }

        if (change_directory(args)) {
            continue;
        }

        execute_command(command, environ, &last_command_status, getpid());
    }

    return 0;
}
