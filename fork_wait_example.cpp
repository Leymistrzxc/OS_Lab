#include <iostream>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid1, pid2, pid3;

    
    pid1 = fork();
    if (pid1 == 0) {
       
        std::cout << "Process 1 (PID: " << getpid() << ")\n";
        return 0; 
    }

    
    pid2 = fork();
    if (pid2 == 0) {
       
        std::cout << "Process 2 (PID: " << getpid() << ")\n";
        return 0; 
    }

    
    pid3 = fork();
    if (pid3 == 0) {
        
        std::cout << "Process 3 (PID: " << getpid() << ")\n";
        return 0; 

    return 0;
}