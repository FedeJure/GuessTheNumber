#ifndef FILE_READER_H_
#define FILE_READER_H_
#include <string>
#include <fstream>
#include <iterator>
#include <iostream>

namespace server
{
    class FileReader {
        std::ifstream file;
        public:
        explicit FileReader(std::string& fileName) : file(fileName) {
            validateFile();
        }

        private:
        void validateFile();
    };
} // namespace server


#endif
