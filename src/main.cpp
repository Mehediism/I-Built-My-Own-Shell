#include <iostream>
#include <string>

bool is_builtin(const std::string& cmd) {
    return cmd == "echo" || cmd == "exit" || cmd == "type";
}

int main() {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;
    
    while(true) {
        std::cout << "$ ";
        std::string input;
        std::getline(std::cin, input);

        if (input == "exit 0") 
            return 0;
            
        // Check if input starts with "type "
        if (input.substr(0, 5) == "type ") {
            std::string cmd = input.substr(5);  // Get the command after "type "
            if (is_builtin(cmd)) {
                std::cout << cmd << " is a shell builtin" << std::endl;
                continue;
            }
        }
            
        // Check if input starts with "echo "
        if (input.substr(0, 5) == "echo ") {
            std::cout << input.substr(5) << std::endl;
            continue;
        }
            
        std::cout << input << ": command not found" << std::endl;
    }
    
    return 0;
}