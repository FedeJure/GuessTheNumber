#include <exception>
#include <string>
#include "./serverFileReader.h"

server::FileReader::FileReader(std::string& providedFileName)
    : file(fileName), fileName(providedFileName) {
    validateFile();
}

void server::FileReader::validateFile() {
    std::string line;
    std::istream_iterator<std::string> eos;
    std::istream_iterator<std::string> iterator(file);
    while (iterator != eos) {
        line = *iterator;
        int numericLine = std::stoi(line);
        if (numericLine < 100 || numericLine > 999) throw std::exception();
        iterator++;
    }
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

server::FileReader::~FileReader() {}
