#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void execute_procmon() {
    DIR *proc_dir;
    struct dirent *entry;
    FILE *status_file;
    char proc_path[256];
    char status_path[256];
    char line[256];

    // Open the /proc directory
    proc_dir = opendir("/proc");
    if (proc_dir == NULL) {
        perror("Error opening /proc directory");
        return;
    }

    // Traverse the /proc directory
    printf("PID\tPROCESS\n");
    while ((entry = readdir(proc_dir)) != NULL) {
        // Check if the entry is a directory and represents a process
        if (entry->d_type == DT_DIR && atoi(entry->d_name) != 0) {
            // Construct the path to the process status file
            snprintf(status_path, sizeof(status_path), "/proc/%s/status", entry->d_name);

            // Open the process status file
            status_file = fopen(status_path, "r");
            if (status_file != NULL) {
                // Read the process name from the status file
                while (fgets(line, sizeof(line), status_file) != NULL) {
                    if (strncmp(line, "Name:", 5) == 0) {
                        // Print the process ID and process name
                        printf("%s\t%s", entry->d_name, line + 6);
                        break;
                    }
                }
                fclose(status_file);
                printf("\n");
            }
        }
    }

    // Close the /proc directory
    closedir(proc_dir);
}

