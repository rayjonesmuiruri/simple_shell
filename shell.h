#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_INPUT_LENGTH 1024
char *replace_variables(char *command, int last_command_status, pid_t shell_pid);
void execute_command(char *command, char **env, int *last_command_status, pid_t shell_pid);
int is_exit_command(char *command);
int is_env_command(char *command);
void print_environment(char **env);
int set_environment_variable(char **args);
int unset_environment_variable(char **args);
int change_directory(char **args);
#endif /* SHELL_H */
