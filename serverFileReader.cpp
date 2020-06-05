#include <exception>
#include <string>
#include "./serverFileReader.h"

server::FileReader::FileReader(std::string& fileName)
    : file(fileName), actualIterator(file) {
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
    std::istream_iterator<std::string> eos;
    if (actualIterator == eos)
        actualIterator = std::istream_iterator<std::string>(file);
    std::string number = *actualIterator;
    //actualIterator++; TODO: arreglar.
    return number;
}

server::FileReader::~FileReader() {}
