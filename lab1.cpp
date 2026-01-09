#include <iostream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <unistd.h>


std::string execCommand(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, int(*)(FILE*)> pipe(popen(cmd, "r"), static_cast<int(*)(FILE*)>(pclose));

    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }


    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result;
}

int main() {
    try {
        
        std::string user = execCommand("whoami");
        user = user.substr(0, user.find_last_not_of(" \n\r\t") + 1);
        std::cout << "Process ID is: " << getpid() << std::endl;
        std::cout << "User: " << user << std::endl;

    } catch (const std::exception& ex) {
        std::cerr << "Error running process: " << ex.what() << std::endl;
    }

    return 0;
}