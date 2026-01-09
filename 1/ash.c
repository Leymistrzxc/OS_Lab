#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/types.h>
#include <sys/wait.h>
#endif


FILE* executeCommand(const char* cmd) {
#ifdef _WIN32
   
    return _popen(cmd, "r");
#else
   
    return popen(cmd, "r");
#endif
}

int main() {
    char output[256]; 
    FILE *fp = executeCommand("whoami");
    
    if (fp == NULL) {
        
        fprintf(stderr, "Error running the process\n");
        return 1;
    }
    

    if (fgets(output, sizeof(output), fp) != NULL) {
        
        printf("Process ID is: %d\n", getpid());
        
      
        output[strcspn(output, "\n")] = 0;
        printf("User: %s\n", output);
    } else {
        printf("Error reading command output\n");
    }
    
    fclose(fp);
    
    printf("\n=== Additional Information ===\n");
    printf("Parent Process ID: %d\n", getppid());
    printf("User ID: %d\n", getuid());
    printf("Group ID: %d\n", getgid());
    
    return 0;
}