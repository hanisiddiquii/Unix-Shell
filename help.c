// help.c

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "help.h"
#include "header.h" // Include the shell header file for color definitions

// Define command structure
typedef struct {
    const char *name;
    const char *syntax;
    const char *description;
} Command;

// Array of available commands and their help messages
Command commands[] = {
    {"bg", "bg [job_num]", "Continue the execution of a stopped background process."},
    {"cd", "cd [directory]", "Change the current working directory."},
    {"echo", "echo [message]", "Display a message on the terminal."},
    {"fg", "fg [job_num]", "Bring a background process to the foreground."},
    {"history", "history [num]", "Display command history or a specific number of recent commands."},
    {"jobs", "jobs [-options]", "List all background jobs or filter by status (-r for running, -s for stopped)."},
    {"ls", "ls [-options] [file/directory]", "List files and directories in the current directory."},
    {"pinfo", "pinfo [pid]", "Display process information for the current shell or a specified process."},
    {"pwd", "pwd", "Print the current working directory."},
    {"replay", "replay -command <cmd> -interval <interval> -period <period>", "Repeat a command at intervals for a specified period."},
    {"repeat", "repeat <count> <cmd>", "Repeat a command a specified number of times."},
    {"sig", "sig <job_num> <signal>", "Send a signal to a background process."}
};

// Function to display help information
void display_help(const char *command_name) {
    if (command_name == NULL) {
        // Display list of all available commands
        printf("Available commands:\n");
        for (size_t i = 0; i < sizeof(commands) / sizeof(commands[0]); i++) {
            printf("%s - %s %s%s\n", PROMPT, commands[i].name, RESET, commands[i].description);
        }
    } else {
        // Find and display help message for the specified command
        for (size_t i = 0; i < sizeof(commands) / sizeof(commands[0]); i++) {
            if (strcmp(command_name, commands[i].name) == 0) {
                printf("%sUsage: %s%s\n%s%s\n", PROMPT, commands[i].syntax, RESET, YELLOW, commands[i].description);
                return;
            }
        }
        // Command not found
        printf("%sCommand '%s' not found. Use 'help' to see available commands.%s\n", ERROR, command_name, RESET);
    }
}

// Function to handle the help command
void help(int arg_count, char *argument[]) {
    if (arg_count == 1) {
        // Display general help information
        display_help(NULL);
    } else if (arg_count == 2) {
        // Display help for specified command
        display_help(argument[1]);
    } else {
        printf("%sUsage: help [command]%s\n", ERROR, RESET);
    }
}

