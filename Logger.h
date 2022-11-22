//
// Created by dmitry on 26.04.2022.
//
#pragma once
#ifndef LOGGER_LOGGER_H
#define LOGGER_LOGGER_H

#include <iostream>
#include <map>
#include <fstream>
#include <regex>
#include <chrono>
#include <ctime>

class Logger {
private:
    static Logger *_instance;
    std::fstream _file_logs;

public:
    Logger() = default;
    Logger(const Logger &) = delete;
    Logger(Logger &) = delete;
    Logger &operator=(const Logger &) = delete;
    ~Logger() {
        delete _instance;
        _file_logs.close();
    };

public:
    static Logger *get_instance() {
        if (_instance == nullptr)
            _instance = new Logger();

        return _instance;
    }

    bool get_connection_status() const {
        return _file_logs.is_open();
    }

    bool connect(const std::string &file_path) {
        _file_logs.open(file_path,
                   std::ios::in |
                   std::ios::out |
                   std::ios::app);

        std::regex rgx(R"((\w:)?([\\\w\s0-9_]*)\.\w+)");
        if (!std::regex_match(file_path, rgx)) return false;

        if (!_file_logs.is_open()) return false;

        return true;
    }

    // логи в консоль
    std::string log(const std::string &message) {
        auto temp = std::chrono::system_clock::now();
        std::time_t date_time = std::chrono::system_clock::to_time_t(temp);

        std::string s_date_time(std::ctime(&date_time));
        s_date_time.pop_back();
        std::clog << s_date_time + " : " + message << std::endl;

        return s_date_time + " : " + message;
    }

    // логи в файл
    std::string logf(const std::string &message) {
        auto temp = std::chrono::system_clock::now();
        std::time_t date_time = std::chrono::system_clock::to_time_t(temp);

        std::string s_date_time(std::ctime(&date_time));
        s_date_time.pop_back();

        if (_file_logs.is_open()) _file_logs << s_date_time + " : " + message << std::endl;

        return s_date_time + " : " + message;
    }
};


#endif //LOGGER_LOGGER_H
