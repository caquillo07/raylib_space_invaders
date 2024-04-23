//
// Created by Hector Mejia on 3/15/24.
//

#include "common.h"
#include <spdlog/spdlog.h>

void initLogger() {
    // todo make more prod ready whenever you feel like making a commercial
    //  project
    spdlog::set_level(spdlog::level::trace);
    spdlog::set_pattern("[%^%l%$] %s:%# [%H:%M:%S:%e] %v");
}

void panic(const char *message) {
    spdlog::critical("{}\n", message);
    exit(EXIT_FAILURE);
}

void panic(const std::string &message) {
    panic(message.c_str());
}

void panicIf(bool condition, const char *message) {
    if (condition) {
        panic(message);
    }
}
