/*=============================================================================
 |   Assignment:  PEX1
 |       Author:  C2C Hampton Ford
 |      Section:  M4A
 |        Class:  CS483
 +-----------------------------------------------------------------------------
 |   Description:  Creates a custom shell in implemented in C.
 |
 |   Required Features Not Included:
 |      None --i test it a good bit and everything worked
 |
 |   Known Bugs:
 |      None
 +-----------------------------------------------------------------------------
 |   Documentation Statement:
 |      Got the pwd with "PWD" environment variable https://unix.stackexchange.com/questions/188182/how-can-i-get-the-current-working-directory
 |      Looked up fgets(..) https://www.tutorialspoint.com/c_standard_library/c_function_fgets.htm
 |      Looked up strcmp(..) http://www.cplusplus.com/reference/cstring/strcmp/
 |      Looked up fork() doc and examples https://www.geeksforgeeks.org/fork-system-call/
 |      Looked up strtok() doc and examples https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
 |          --note i didn't copy/pasta or anything but ofc followed this example closely b/c honestly strok() is weird and that man page is difficult to follow in abstract
 |      Looked up chdir() doc and examples https://www.geeksforgeeks.org/chdir-in-c-language-with-examples/
 |      Looked up getenv() doc https://man7.org/linux/man-pages/man3/getenv.3.html
 |      Looked up wait() doc at https://www.geeksforgeeks.org/wait-system-call-c/
 |      Looked up execvp() doc at https://linux.die.net/man/3/execvp
 |      Looked up execvp() example at https://www.geeksforgeeks.org/exec-family-of-functions-in-c/
 |          --to debug execvp() error
 |      I outduped the child's process stdout w/ dup2 which I initially thought of from an asm64 333 project but
 |          --figured out how to do in C from https://stackoverflow.com/questions/52088683/is-it-possible-to-redirect-child-processs-stdout-to-another-file-in-parent-proc
 |          --**no code was copied
 |      Looked up strdup() doc https://man7.org/linux/man-pages/man3/strdup.3.html
 |
 |       Reused my Queue and underlying Doubly Linked List library from CS220
 |      --old docs statement from that https://stackoverflow.com/questions/1813991/c-structure-with-pointer-to-self answer by avakar
 *===========================================================================*/

#include "pex1.h"

int main(int argc, char* argv[]) {
    List list;

    // check no arguments to program
    if (argc != 1) {
        perror("Executable afsh takes no arguments.\n");
        exit(INVALID_ARG_ERROR);
    }

    // initialize list
    init_queue(&list, "");

    // start shell
    startShell(&list);

    return 0;
}

/*
 * Purpose: Start custom shell
 * @Params: List*
 * @Return: void
 */
void startShell(List* list) {
    // print intro
    printf("...Air Force Shell (afsh)...\n");

    // create shell loop
    do {
        // print custom shell prompt
        char env[MAX_COMMAND_LEN];
        if (getcwd(env, sizeof env) == NULL) {
            perror("Error getting shell prompt.\n");
            exit(STD_FUNCTION_ERROR);
        }
        printf("@f$h:%s>", env);

        // receive shell originalCommand
        char originalCommand[MAX_COMMAND_LEN];
        if (fgets(originalCommand, MAX_COMMAND_LEN, stdin) == NULL) {
            perror("fgets error input failed");
            exit(STD_FUNCTION_ERROR);
        }
        //overwrite newline character
        originalCommand[strlen(originalCommand) - 1] = '\0';
        char* enCommand;
        enCommand = strdup(originalCommand);
        if (enCommand == NULL) {
            perror("Insufficient memory for strdup.\n");
            exit(STD_FUNCTION_ERROR);
        }

        // tokenize originalCommand
        //originalCommand storage
        char* commandArr[MAX_COMMAND_LEN];
        int i = 0;
        //required strtok variables
        char delimeter[2] = " ";
        char* token;
        token = strtok(originalCommand, delimeter);
        while (token != NULL) {
            commandArr[i] = strdup(token);
            token = strtok(NULL, delimeter);
            ++i;
        }

        // save shell originalCommand to history
        remDuplicates(list, commandArr[0]); //prevents 'history 1' 'history 2' both being separate commands
        enqueue(list, enCommand);

        // check if "built-in"
        if (strcmp(commandArr[0], "exit") == 0) {
            //free dynamically allocated linked list
            list_delete(list->head);
            for (int n = 0; n <= i; ++n) {
                free(commandArr[n]);
            }
            break;
        }
        else if (strcmp(commandArr[0], "history") == 0) {
            char *leftOverStr;
            int arg = (int)strtod(commandArr[1], &leftOverStr);
            if (arg < list->list_size) {
                nth_history(list, arg);
            }
            else {
                printf("Attempting to access history past bounds.\n");
            }
        }
        else if (strcmp(commandArr[0], "recall") == 0) {
            char *leftOverStr;
            int arg = (int)strtod(commandArr[1], &leftOverStr);
            if (arg < list->list_size) {
                nth_recall(list, arg);
            }
            else {
                printf("Attempting to recall past bounds.\n");
            }
        }
        else if (strcmp(commandArr[0], "cd") == 0) {
            if (strcmp(commandArr[1], "~") == 0) {
                strcpy(commandArr[1], getenv("HOME"));
            }
            if (chdir(commandArr[1]) != 0) {
                printf("Could not enter directory: '%s'\n\n", commandArr[1]);
            }
        }
        // fork/exec
        else {
            pid_t childPID = fork();
            if (childPID < 0) {
                printf("Child process failed.\n"); //loop through for another try
            }
            if (childPID == 0) { //child process started
                dup2(execvp(commandArr[0], commandArr), getpid());
                printf("\n"); //pretty formatting
            }
            else { //parent process should wait for child process to finish (e.g. terminate)
                wait(NULL); //"wait() waits only for terminated children" --documentation
            }
        }
    } while (1);
}