#include <exception>
#include <string>
#include "./serverFileReader.h"

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
