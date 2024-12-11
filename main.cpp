/**
 * @file main.cpp
 * @author adem marangoz (adem.marangoz95@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-12-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */


// Include Libraries ============================================
#include "vgit.hpp"




int main()
{
    vgit vgit;
    std::cout << "Enter your command" << std::endl;
    std::string input;
    getline(std::cin, input);
    vgit.vgit_control(input);
    return 0;
}