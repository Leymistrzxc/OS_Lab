#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int choice;
    
    printf("Welcome to Process Info Program!\n");
    printf("Made by: [Your Name]\n");
    printf("NCP 422 - Operating Systems\n\n");
    
    printf("Menu:\n");
    printf("1. Show Process ID\n");
    printf("2. Show User Info\n");
    printf("3. Show All Information\n");
    printf("4. Exit\n");
    printf("Enter your choice (1-4): ");
    scanf("%d", &choice);
    
    switch(choice) {
        case 1:
            printf("\n=== PROCESS ID ===\n");
            printf("Your Process ID is: %d\n", getpid());
            break;
            
        case 2:
            printf("\n=== USER INFORMATION ===\n");
            printf("User ID: %d\n", getuid());
            printf("Group ID: %d\n", getgid());
            printf("Parent Process ID: %d\n", getppid());
            break;
            
        case 3:
            printf("\n=== ALL SYSTEM INFORMATION ===\n");
            printf("1. Process ID: %d\n", getpid());
            printf("2. Parent PID: %d\n", getppid());
            printf("3. User ID: %d\n", getuid());
            printf("4. Group ID: %d\n", getgid());
            
            // Try to get username
            printf("\n5. Trying to get username...\n");
            system("echo 'Username:' && whoami");
            
            // Get hostname
            printf("\n6. Getting hostname...\n");
            system("hostname");
            
            printf("\n=== INFORMATION COMPLETE ===\n");
            break;
            
        case 4:
            printf("\nThank you for using the program!\n");
            printf("Goodbye!\n");
            break;
            
        default:
            printf("\nInvalid choice! Please enter 1-4 only.\n");
    }
    
    printf("\nProgram created for NCP 422 Lab Activity.\n");
    return 0;
}