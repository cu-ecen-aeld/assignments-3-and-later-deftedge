#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <syslog.h>


// Function to write text to a file
void write_to_file(const char *file_path, const char *text) {
    FILE *file = fopen(file_path, "w"); // Open file in write mode
    
    if (file == NULL) {
        // Failed to open file
        syslog(LOG_ERR, "Failed to open file: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Write text to the file
    fprintf(file, "%s", text);
    
    // Close the file
    fclose(file);
}


int main(int argc, char *argv[]) {
    openlog(NULL, 0, LOG_USER);

    // Ensure 3 arguments (script-name, full-file-path, string-to-write-to-file)
    if (argc != 3) {
        fprintf(stderr, "%s: Invalid number of arguments\n", argv[0]);
        fprintf(stderr, "1) File Path.\n");
        fprintf(stderr, "2) String to be entered in the file.\n");
        syslog(LOG_ERR, "Invalid number of arguments");
        closelog();
        exit(EXIT_FAILURE);
    }

    const char *file_path = argv[1];
    const char *text = argv[2];

    // Write text to the file
    write_to_file(file_path, text);

    // Log success
    syslog(LOG_INFO, "Text successfully written to %s", file_path);

    // Close syslog
    closelog();

    return 0;
}
