#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2, pid3;

    std::cout << "Parent process (PID: " << getpid() << ")\n";

    
    pid1 = fork();
    if (pid1 == 0) {
        
        std::cout << "Child 1 (PID: " << getpid() << ", Parent PID: " << getppid() << ")\n";
        return 0; 
    }

    
    pid2 = fork();
    if (pid2 == 0) {
        
        std::cout << "Child 2 (PID: " << getpid() << ", Parent PID: " << getppid() << ")\n";
        return 0; 
    }

    
    pid3 = fork();
    if (pid3 == 0) {
        
        std::cout << "Child 3 (PID: " << getpid() << ", Parent PID: " << getppid() << ")\n";
        return 0; 
    }

    
    waitpid(pid3, nullptr, 0);
    std::cout << "Parent process waited for Child 3 (PID: " << pid3 << ")\n";

    return 0;
}