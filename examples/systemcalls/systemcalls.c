#include "systemcalls.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdarg.h>
#include <fcntl.h>

/**
 * @param cmd the command to execute with system()
 * @return true if the command in @param cmd was executed
 *   successfully using the system() call, false if an error occurred,
 *   either in invocation of the system() call, or if a non-zero return
 *   value was returned by the command issued in @param cmd.
*/
bool do_system(const char *cmd)
{
    int ret = system(cmd);

    // return false if system() call failed
    if (ret == -1) {
        return false;
    } else {
        // Opt. check for actual cmd status
        // if (WIFEXITED(ret)) {
        //     int process_ret = WEXITSTATUS(ret);
        //     if (process_ret == 0) {
        //         // process success
        //         return true;
        //     } else {
        //         // process failure
        //         return false;
        //     }
        // }
        return true;
    }

    return true;
}

/**
* @param count -The numbers of variables passed to the function. The variables are command to execute.
*   followed by arguments to pass to the command
*   Since exec() does not perform path expansion, the command to execute needs
*   to be an absolute path.
* @param ... - A list of 1 or more arguments after the @param count argument.
*   The first is always the full path to the command to execute with execv()
*   The remaining arguments are a list of arguments to pass to the command in execv()
* @return true if the command @param ... with arguments @param arguments were executed successfully
*   using the execv() call, false if an error occurred, either in invocation of the
*   fork, waitpid, or execv() command, or if a non-zero return value was returned
*   by the command issued in @param arguments with the specified arguments.
*/

bool do_exec(int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int i;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;

    pid_t pid = fork();
    if (pid == -1) {
        // fork failed
        return false;
    } else if (pid == 0) {
        // Child process
        execv(command[0], command);

        // execv only returns on error
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            // Child process exited normally
            int exit_status = WEXITSTATUS(status);
            if (exit_status == 0) {
                // Command executed successfully
                return true;
            } else {
                // Command returned failure
                return false;
            }
        } else {
            // Child process did not exit normally
            return false;
        }
    }

    return true;
}

/**
* @param outputfile - The full path to the file to write with command output.
*   This file will be closed at completion of the function call.
* All other parameters, see do_exec above
*/
bool do_exec_redirect(const char *outputfile, int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int i;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;

    // Create file descriptor for output file
    int fd = open(outputfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        return false;
    }

    pid_t pid = fork();
    if (pid == -1) {
        // fork failed
        return false;
    } else if (pid == 0) {
        if (dup2(fd, 1) < 0) {
            exit(EXIT_FAILURE);
        }
        close(fd);
        // Child process
        execv(command[0], command);
        // execv only returns on error
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            // Child process exited normally
            int exit_status = WEXITSTATUS(status);
            if (exit_status == 0) {
                // Command executed successfully
                return true;
            } else {
                // Command returned failure
                return false;
            }
        } else {
            // Child process did not exit normally
            return false;
        }
    }

    va_end(args);

    return true;
}
