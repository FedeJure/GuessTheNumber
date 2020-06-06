#include "./clientArgumentHandler.h"
#include "./client.h"

#define CLIENT_SUCESS 0

int main(int argc, char* argv[]) {
    client::ArgumentHandler argHandler(argc, argv);
    client::Client(argHandler.getHost(), argHandler.getService());

    //conexion con servidor

    //empieza a escuchar input del usuario y handlea cada uno 

    return CLIENT_SUCESS;
}
