#include <exception>
#include <string>
#include "./serverFileReader.h"

server::FileReader::FileReader(std::string& providedFileName)
    : fileName(providedFileName) {
    file = std::ifstream(fileName); 
    validateFile();
}

void server::FileReader::validateFile() {
    std::string line;
    while (file.peek() != EOF) {
        std::string line;
        std::getline(file, line);
        int numericLine = std::stoi(line);
        if (numericLine < 100 || numericLine > 999) throw std::exception();
    }
    file.close();
    file = std::ifstream(fileName);
}

std::string server::FileReader::getNext() {
    std::unique_lock<std::mutex> lock(m);
    if (file.peek() == EOF) {
        file.close();
        file = std::ifstream(fileName);
    }
    std::string number;
    std::getline(file, number);
    return number;
}

server::FileReader::~FileReader() {
    file.close();
}
