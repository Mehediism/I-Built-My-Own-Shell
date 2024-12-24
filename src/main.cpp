#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem>
#include <vector>
#include <sstream>

using namespace std;
namespace fs = filesystem;

// Check if a command is a shell builtin
bool is_builtin(const string& cmd) {
    return cmd == "echo" || cmd == "exit" || cmd == "type";
}

// Split PATH into directories
vector<string> get_path_dirs() {
    vector<string> dirs;
    string path = getenv("PATH");
    size_t pos = 0;
    while ((pos = path.find(':')) != string::npos) {
        dirs.push_back(path.substr(0, pos));
        path.erase(0, pos + 1);
    }
    dirs.push_back(path);
    return dirs;
}

// Find executable in PATH
string find_executable(const string& cmd) {
    for (const auto& dir : get_path_dirs()) {
        string full_path = dir + "/" + cmd;
        if (fs::exists(full_path) && fs::is_regular_file(full_path)) {
            return full_path;
        }
    }
    return "";
}

int main() {
    cout << unitbuf;
    cerr << unitbuf;
    
    while(true) {
        cout << "$ ";
        string input;
        getline(cin, input);

        if (input == "exit 0") 
            return 0;
            
        // Check if input starts with "type "
        if (input.substr(0, 5) == "type ") {
            string cmd = input.substr(5);
            if (is_builtin(cmd)) {
                cout << cmd << " is a shell builtin" << endl;
            } else {
                string exe_path = find_executable(cmd);
                if (!exe_path.empty()) {
                    cout << cmd << " is " << exe_path << endl;
                } else {
                    cout << cmd << ": not found" << endl;
                }
            }
            continue;
        }
            
        // Check if input starts with "echo "
        if (input.substr(0, 5) == "echo ") {
            cout << input.substr(5) << endl;
            continue;
        }
        
        // Execute external programs
        stringstream ss(input);
        string program;
        ss >> program;
        string exe_path = find_executable(program);
        if (!exe_path.empty()) {
            system(input.c_str());
        } else {
            cout << input << ": command not found" << endl;
        }
    }
    
    return 0;
}