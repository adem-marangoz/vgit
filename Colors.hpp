/**
 * @file Colors.hpp
 * @author adem marangoz (adem.marangoz95@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-12-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */



#pragma once

#include <string>

namespace Colors {
    const std::string RESET = "\033[0m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN = "\033[36m";


    const std::string BOLD = "\033[1m";
    const std::string UNDERLINE = "\033[4m";
    const std::string REVERSE = "\033[7m";

    std::string coloize(const std::string& text, const std::string& color) {
        return color + text + RESET;
    }
}