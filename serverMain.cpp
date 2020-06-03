#include "./serverArgumentHandler.h"
#include "./serverFileReader.h"
#include "./commonSocket.h"
#define SERVER_SUCESS 0
#define SERVER_ERROR 1


int main(int argc, char* argv[]) {
    try {
        server::ArgumentHandler argumentHandler(argc, argv);
        server::FileReader fileReader(argumentHandler.getNumbersFileName());
        common::Socket localSocket(argumentHandler.getService());
        //handlear argumentos de ejecucion
        //iniciar clase de lectura de archivo de numeros
        //iniciar socket y escucha de servidor
    }
    catch(const std::exception& e) {
        return SERVER_ERROR;
    }
    return SERVER_SUCESS;
}
