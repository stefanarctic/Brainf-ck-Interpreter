
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

typedef std::ifstream readstream;
typedef std::ofstream writestream;

int main() {
    std::string outputPath = "bin/output.cpp";
    std::string inputPath = "input.bf";
    char escape = '\n';
    
    
    
    // std::cout << program[0] << std::endl;

    // Read input content
    readstream rstream(inputPath.c_str());
    std::string line;
    std::string content = "";
    if(rstream.is_open()) {
        while(getline(rstream, line)) {
            content += line;
        }
        rstream.close();
    } else {
        std::cout << "Could not open file " << inputPath << escape;
        exit(1);
    }

    writestream wstream(outputPath.c_str(), std::ios::out | std::ios::binary);
    if(!wstream.is_open()) {
        std::cout << "Could not open file " << outputPath << escape;
        exit(1);
    }

    wstream << "#include <iostream>" << escape;
    wstream << "#include <vector>" << escape;
    wstream << "int main()" << escape;
    wstream << "{" << escape;
    wstream << "std::vector<int> program;" << escape;
    wstream << "program.reserve(100);" << escape;
    // wstream << "program.fill(0);" << escape;
    wstream << "int program_pointer = 0;" << escape;
    // wstream << "for(int i = 0; i < program.size(); i++) program[i] = 0;" << escape;

    const char* c_content = content.c_str();
    std::vector<char> content_arr(c_content, c_content + sizeof c_content / sizeof c_content[0]);
    for(int i = 0; i < content_arr.size(); i++) {
        char& currentChar = content_arr[i];
        switch(currentChar) {
            case '>': {
                wstream << "program_pointer++;" << escape;
                break;
            }
            case '<': {
                wstream << "program_pointer--;" << escape;
                break;
            }
            case '+': {
                wstream << "program[program_pointer]++;" << escape;
                break;
            }
            case '-': {
                wstream << "program[program_pointer]--;" << escape;
                break;
            }
            case '.': {
                wstream << "std::cout << program[program_pointer] << std::endl;" << escape;
                break;
            }
            case ',': {
                wstream << "std::cin >> program[program_pointer];" << escape;
                break;
            }
        }
    }

    wstream << "}" << escape;

    wstream.close();
}