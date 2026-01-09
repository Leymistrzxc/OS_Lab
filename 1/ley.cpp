#include <iostream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <unistd.h>  // for getpid()
#include <string>
#include <cstring>

// Function to execute a system command and capture its output
std::string execCommand(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;

    // Open a pipe to run the command
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);

    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    // Read the output of the command line by line and store in result
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result;
}

int main() {
    try {
        // Student information header
        std::cout << "NCP 422 - Operating Systems Laboratory" << std::endl;
        std::cout << "Lab Activity #1 - C++ Implementation" << std::endl;
        std::cout << "======================================" << std::endl << std::endl;

        // Run the "whoami" command to get the current user
        std::string user = execCommand("whoami");

        // Trim any trailing whitespace or newlines from the output
        size_t endpos = user.find_last_not_of(" \n\r\t");
        if (std::string::npos != endpos) {
            user = user.substr(0, endpos + 1);
        }

        // Print process ID and the current user
        std::cout << "Process ID is: " << getpid() << std::endl;
        std::cout << "User: " << user << std::endl;

        // Additional system information
        std::cout << std::endl;
        std::cout << "=== Additional System Information ===" << std::endl;
        std::cout << "Parent Process ID: " << getppid() << std::endl;
        std::cout << "User ID: " << getuid() << std::endl;
        std::cout << "Group ID: " << getgid() << std::endl;

        // Get system name
        try {
            std::string hostname = execCommand("hostname");
            size_t endpos2 = hostname.find_last_not_of(" \n\r\t");
            if (std::string::npos != endpos2) {
                hostname = hostname.substr(0, endpos2 + 1);
            }
            std::cout << "Hostname: " << hostname << std::endl;
        } catch (...) {
            std::cout << "Hostname: Not available" << std::endl;
        }

        std::cout << std::endl << "Program execution completed successfully!" << std::endl;

    } catch (const std::exception& ex) {
        // Handle any errors that occur during the execution
        std::cerr << "Error running process: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}