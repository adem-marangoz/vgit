/**
 * @file vgit.hpp
 * @author adem marangoz (adem.marangoz95@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-12-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */



#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include <map>
#include <filesystem>
#include <functional>


class vgit{
private:
    enum class CMD_States
    {
        Success,
        Error
    };
void add_all_files(const std::multimap<std::string, std::string>& ignored_items);
void add_paths(const std::string&);
void add_extensions(const std::string&);
void add_files(const std::string&);
void scan_path(const std::string&);
const std::multimap<std::string, std::string> Ignore_list(void);
bool isValidPattern(const std::string& input);
CMD_States vgit_init(const std::string &message) noexcept;
CMD_States vgit_add(const std::string &message);

std::filesystem::path main_directoryPath;
const std::multimap<std::string, std::string> ignored_files;
std::unordered_map<std::string, std::function<CMD_States(const std::string& ignored_item)>> command_map;
std::unordered_map<std::string, std::function<void(const std::string& ignored_item)>> patternFunctions;

public:
    vgit();
    CMD_States vgit_control(const std::string &command);
    ~vgit(){};
};


