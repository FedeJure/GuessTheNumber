#ifndef FILE_READER_H_
#define FILE_READER_H_
#include <string>
#include <fstream>
#include <iterator>
#include <iostream>
#include <mutex>

namespace server
{
    class FileReader {
        std::ifstream file;
        std::mutex m;
        std::string fileName;
        public:
        explicit FileReader(std::string& fileName);
        ~FileReader();
        std::string getNext();
        private:
        void validateFile();
    };
} // namespace server


#endif
