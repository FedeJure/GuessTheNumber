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
        std::istream_iterator<std::string> actualIterator;
        public:
        explicit FileReader(std::string& fileName);
        ~FileReader();
        std::string getNext();
        private:
        void validateFile();
    };
} // namespace server


#endif
