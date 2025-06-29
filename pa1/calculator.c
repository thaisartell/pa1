#include "calculator.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/* Function prototypes */
/* Feel free to add your own helper functions */
void process_directory(const char *dir_path);
int count_files_in_directory(const char *dir_path);

int main(int argc, char *argv[]) {
    /* TODO: Task 1 - Argument parsing */
    if (argc != 2) {
        fprintf(stderr, "Usage: %s PATH_TO_DIR\n", argv[0]);
        exit(1);
    }
    
    const char *dir_path = argv[1];
    /* TODO: Get the path to the directory from command line options */ 

    /* TODO: Process the directory */
    process_directory(dir_path);
    
    return 0;
}

void process_directory(const char *dir_path) {
    /* TODO: Task 1 - Directory handling */
    
    /* Open directory */
    DIR *dir = opendir(dir_path);
    struct dirent *entry;
    pid_t *childPids = NULL;
    /* Count files first to allocate memory */
    
    int numFiles = count_files_in_directory(dir_path);
    if (numFiles == 0) {
        closedir(dir);
        return; // No files to process
    }
    /* TODO: Allocate memory for results */
    childPids = malloc(numFiles * sizeof(pid_t));
    /* Phase 2: Create pipes for communication */
    /* TODO: Task 4 - Create pipes here */
    
    /* Read directory entries */
    int childIndex = 0;
    while ((entry = readdir(dir)) != NULL) {
        // Skipping "." and ".." here
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char full_path[PATH_MAX];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);

        struct stat path_stat;
        if (stat(full_path, &path_stat) == -1 || !S_ISREG(path_stat.st_mode)) {
            continue;
        }

        pid_t pid = fork();
        if (pid < 0) {
            perror("failed fork");
            continue;
        } else if (pid == 0) {
            execl("./child", "./child", full_path, (char *)NULL);
            perror("execl failed");
            exit(EXIT_FAILURE);
        } else {
            childPids[childIndex] = pid;
            childIndex++;
        }
    }
        
    /* TODO: Task 2 - Wait for all child processes to complete */
    for (int i = 0; i < childIndex; i++) {
        int status;
        waitpid(childPids[i], &status, 0);
    }
    
    /* TODO: Close directory here */
    closedir(dir);
    /* Calculate and print final results */
   
    /* TODO: Remember to deallocate any memory */
    free(childPids);
}

int count_files_in_directory(const char *dir_path) {
    DIR *dir = opendir(dir_path);
    int count = 0;

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char full_path[PATH_MAX];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);

        struct stat path_stat;
        if (stat(full_path, &path_stat) == 0 && S_ISREG(path_stat.st_mode)) {
            count++;
        }
    }

    closedir(dir);

    return count;
}
