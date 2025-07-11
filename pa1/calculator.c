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
    int (*pipes)[2] = malloc(numFiles * sizeof(int[2]));

    if (!childPids || !pipes) {
        perror("malloc failed");
        closedir(dir);
        exit(EXIT_FAILURE);
    }

    /* Read directory entries */
    int childIndex = 0;
    while ((entry = readdir(dir)) != NULL) {
        // Skipping "." and ".." here
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        // char full_path[PATH_MAX];
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);

        struct stat path_stat;
        if (stat(full_path, &path_stat) == -1 || !S_ISREG(path_stat.st_mode)) {
            continue;
        }

        if (pipe(pipes[childIndex]) < 0) {
            perror("pipe failed");
            continue;
        }

        pid_t pid = fork();
        if (pid < 0) {
            perror("failed fork");
            continue;
        } else if (pid == 0) {
            close(pipes[childIndex][0]);

            char fd_str[10];
            snprintf(fd_str, sizeof(fd_str), "%d", pipes[childIndex][1]);

            execl("./child", "./child", full_path, fd_str, (char *)NULL);
            perror("execl failed");
            exit(EXIT_FAILURE);
        } else {
            close(pipes[childIndex][1]);
            childPids[childIndex] = pid;
            childIndex++;
        }
    }
    closedir(dir);
        
    /* TODO: Task 2 - Wait for all child processes to complete */

    long sum = 0;
    int count = 0;
    for (int i = 0; i < childIndex; i++) {
        int file_count;
        long file_sum;
        // char filename[64];

        int status;
        waitpid(childPids[i], &status, 0);

        if (read(pipes[i][0], &file_count, sizeof(int)) != sizeof(int)) {
            fprintf(stderr, "Failed to read count from child %d\n", i);
            file_count = 0;
        }
        if (read(pipes[i][0], &file_sum, sizeof(long)) != sizeof(long)) {
            fprintf(stderr, "Failed to read sum from child %d\n", i);
            file_sum = 0;
        }

        close(pipes[i][0]);

        count += file_count;
        sum += file_sum;

        printf("File_%d: %d, %ld\n", i+1, file_count, file_sum);
    }

    /* Calculate and print final results */
    printf("Sum: %ld\n", sum);
    if (count > 0)
        printf("Average: %ld\n", sum / count);
    else
        printf("Average: 0\n");
    
    /* TODO: Remember to deallocate any memory */
    free(childPids);
    free(pipes);
}

int count_files_in_directory(const char *dir_path) {
    DIR *dir = opendir(dir_path);

    if (dir == NULL) {
        exit(EXIT_FAILURE);
    }

    int count = 0;

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        // char full_path[PATH_MAX];
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);

        struct stat path_stat;
        if (stat(full_path, &path_stat) == 0 && S_ISREG(path_stat.st_mode)) {
            count++;
        }
    }

    closedir(dir);

    return count;
}
