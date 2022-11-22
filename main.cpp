#include <iostream>
#include <string>
#include <Windows.h>
#include "Logger.h"

using namespace std;

Logger *Logger::_instance = nullptr;

int main() {
    setlocale(LC_ALL, "ru");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    Logger *first_logger = Logger::get_instance();
    Logger *second_logger = Logger::get_instance();

    first_logger->log("First logger send 1st message without writing to file\"1\"");
    first_logger->log("First logger send 2st message without writing to file\"2\"");

    second_logger->connect("E:\\file.txt");
    second_logger->logf("Second logger send init message with writing to file \"1\"");
    first_logger->logf("First logger send message with writing to file \"2\"");
}
