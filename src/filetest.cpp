
#include <iostream>
#include <fstream>
#include <vector>

char escape = '\n';

template<typename T>
T* vectorToArray(std::vector<T>& vec) {
    // T arr[vec.size()];
    T* arr = &vec[0];
    return arr;
}

std::string readFile(const std::string& path) {
    std::ifstream file(path);
    std::string line;
    std::string content = "";
    if(file.is_open()) {
        while(getline(file, line)) {
            content += line;
        }
        file.close();
    } else {
        std::cout << "Unable to open file " << path << escape;
    }
    return content;
}

void writeToFile(const std::string& path, const std::string& content) {
    std::ofstream file(path);
    if(file.is_open()) {
        file << content;
    } else {
        std::cout << "Unable to open file " << path << escape;
    }
}

class FileScanner {
private:
    // Write
    std::ofstream m_Ofstream;
    // Read
    std::ifstream m_Ifstream;
    // Path
    std::string path;
public:
    FileScanner(const std::string& path) : m_Ofstream(path, std::ios::out | std::ios::app | std::ios::binary), m_Ifstream(path), path(path) {}
    virtual ~FileScanner() {
        this->close();
    }
    void close() {
        m_Ofstream.close();
        m_Ifstream.close();
    }
    std::string read() {
        return readFile(this->path);
    }
    void write(const std::string& content) {
        writeToFile(this->path, content);
    }
    std::string getPath() {
        return this->path;
    }
};

int main() {
    
    // // int program[100];
    // // int i = 0;
    // // for(;;i++) {
    // //     int n = program[i];
    // //     if(!n)
    // //         break;
        
    // // }
    // // std::vector<int> program;
    // // program.reserve(100);
    // // program[0]++;
    // // std::cout << program[0] << std::endl;
    // // Yes yes;
    // // std::cout << yes.y << std::endl;
    // Yes yes;
    // // yes.y = 1;
    // std::cout << yes.y << std::endl;

    // std::ofstream file;
    // file.open("test.txt", ios::out | ios::app | ios::binary);
    // file << "yes" << escape;
    // file << "yo" << escape;
    // file.close();
    FileScanner scanner("test.txt");
    scanner.write("dasdsad\n");
    scanner.write("asdsadsa\n");
    std::string content = scanner.read();
    scanner.close();
    std::cout << "Wrote to file test.txt" << escape;

}