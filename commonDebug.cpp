// #include <string>
// #include <iostream>
// #include "./commonDebug.h"

// #define VARIABLE_KEY "GUESS_NUMBER_DEBUG"

// template<typename T, typename... Args>
// void _log(T message, Args... args);

// template<typename T>
// void common::log(T t) {
//     common::log(t, "");
// }

// template<typename T, typename... Args>
// void common::log(T t, Args... args) {

//     char* environment = getenv(VARIABLE_KEY);
//     if (environment != NULL || std::string(environment) == "true") {
//         _log(t, args...);
//         std::cout << std::endl; fflush(stdout);
//     }
// }

// template<typename T, typename... Args>
// void _log(T t, Args... args) {
//     std::cout << t;
//     func(args...);
// }
