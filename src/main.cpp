#include <iostream>
#include <string>

int main() {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;
    
    while(true) {
        std::cout << "$ ";
        std::string input;
        std::getline(std::cin, input);

        if (input == "exit 0") 
            return 0;
            
        // Check if input starts with "echo "
        if (input.substr(0, 5) == "echo ") {
            // Print everything after "echo "
            std::cout << input.substr(5) << std::endl;
            continue;
        }
            
        std::cout << input << ": command not found" << std::endl;
    }
    
    return 0;
}