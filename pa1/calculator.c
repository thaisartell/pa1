#include "calculator.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    DIR *dir = opendir(dir_path);
    /* Open directory */
        
    /* Count files first to allocate memory */
    int num_files = count_files_in_directory(dir_path);
    if (num_files == 0) {
        closedir(dir);
        return; // No files to process
    }
    /* TODO: Allocate memory for results */
    child_pids = malloc(num_files * sizeof(pid_t));
    /* Phase 2: Create pipes for communication */
    /* TODO: Task 4 - Create pipes here */
    
    /* Read directory entries */
        
    /* TODO: Task 2 - Wait for all child processes to complete */
    
    /* TODO: Close directory here */
    closedir(dir);
    /* Calculate and print final results */
   
    /* TODO: Remember to deallocate any memory */
}

int count_files_in_directory(const char *dir_path) {
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
