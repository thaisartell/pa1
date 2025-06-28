#include "calculator.h"

/* Function prototypes */
/* Feel free to add your own helper functions */
void process_file(const char *file_path, int pipe_fd);
void write_results_to_file(const char *original_path, int count, long sum);
void send_results_via_pipe(int pipe_fd, int count, long sum);

int main(int argc, char *argv[]) {
    /* TODO: Task 3 - Receive file path from command line -> char* argv[1]*/
    /* Phase 1: Only file path is needed */
    
    /* Phase 2: Both file path and pipe fd are needed */
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s FILE_PATH [PIPE_FD]\n", argv[0]);
        exit(1);
    }
   
    const char *file_path;
    int pipe_fd = -1;
    /* TODO: Get path to the file */ 
    file_path = argv[1];

    /* TODO: Get the file descriptor from the command line in Phase 2 */

    /* Process the file */
    process_file(file_path, pipe_fd);
    
    return 0;
}

void process_file(const char *file_path, int pipe_fd){
    int count;
    long sum;

    count = 0;
    sum = 0;

    /* TODO: Task 3 - Open file and extract numbers */
    FILE* fp = fopen(file_path, "r");
        
    /* Read integers from file, one per line */
    int num;
    while (fscanf(fp, "%d", &num) == 1) {
        sum += num;
        count++;
    }

    /* Remember to close the file */
    fclose(fp);
    
    /* Phase 1: Write results to .results file */
    write_results_to_file(file_path, count, sum);
    
    /* Phase 2: Send results via pipe */
    /* TODO: Task 4 - Implement pipe communication */
    /* send_results_via_pipe(pipe_fd, count, sum); */
}

void write_results_to_file(const char *original_path, int count, long sum) {
    /* TODO: Create .results filename */
    FILE* fp = fopen(".results", "w");

    /* TODO: Write count and sum to results file */
    fprintf(fp, "count: %d", count);
    fprintf(fp, "sum: %ld", sum);

    /* Remember to close files and release resources */
    fclose(fp);
}

void send_results_via_pipe(int pipe_fd, int count, long sum){
    /* TODO: Task 4 - Send PipeMessage through pipe */
    /* This function will be implemented in Phase 2 */
    /* TODO: Write message to pipe */
    /* Hint: The pipe file descriptor should be passed somehow */
}
