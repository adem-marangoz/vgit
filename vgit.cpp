/**
 * @file vgit.cpp
 * @author adem marangoz (adem.marangoz95@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-12-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */


// Include Libraries ============================================
#include "vgit.hpp"
#include <functional>
#include <sstream>
#include <ostream>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <regex>
#include "Colors.hpp"

/**
 * Constructor for vgit class.
 * 
 * Initializes the command_map with the different commands and their associated
 * functions.
 */
vgit::vgit(): main_directoryPath(std::filesystem::current_path()), ignored_files(Ignore_list())
{
    command_map["vgit init"] = [this](const std::string& arg) { return vgit_init(arg); };
    command_map["vgit add"] = [this](const std::string& arg) { return vgit_add(arg); };
    patternFunctions[R"(.*\..*)"] = [this](const std::string& ignored_item) {
        add_files(ignored_item);
    };
    patternFunctions[R"(.*\/\*)"] = [this](const  std::string& ignored_item) {
        add_paths(ignored_item);
    };
    patternFunctions[R"(^.*\*\.\w+$)"] = [this](const std::string& ignored_item) {
        add_extensions(ignored_item);
    };
    
}


/**
 * This function takes a command string as input and executes the corresponding
 * command in the vgit command map. If the command is not found, it returns an
 * error code.
 * 
 * @param input The command string to be executed. The command string should
 *               start with the command name, followed by optional arguments.
 *               The command name should match exactly with the command names
 *               in the command map.
 * @return The result of the command execution. If the command is not found,
 *         it returns CMD_States::Error.
 */
vgit::CMD_States vgit::vgit_control(const std::string &input)
{
    for (const auto& pair : command_map) {
        const std::string& key = pair.first;

        if (input.find(key) == 0) 
        {
            std::string arg = input.substr(key.size());
            arg.erase(0, arg.find_first_not_of(" "));
            return command_map[key](arg);
        }
    }
    std::cout << "Command not found" << std::endl;
    return CMD_States::Error;
}



/**
 * Initializes a new vgit repository in the current working directory.
 * If the `.vgit` directory already exists, it does nothing.
 * 
 * @param message The command-line argument. This must be empty.
 * @return Success if the initialization was successful, Error otherwise.
 */
vgit::CMD_States vgit::vgit_init(const std::string &message) noexcept
{
    if(message.empty())
    {
        if(std::filesystem::create_directory(".vgit"))
        {
            std::cout << "Created .vgit directory" << std::endl;
        }else
        {
            std::cout << ".vgit directory already exists" << std::endl;
        }
        return CMD_States::Success;
    }else
    {
        std::cout << "Error: This must don't have any arguments" << std::endl;
    }
    return CMD_States::Error;
}


/**
 * Checks whether a given string matches a valid pattern for a .gitignore item.
 * 
 * A valid pattern is any string that matches the following regex pattern:
 * 
 *     (([a-zA-Z0-9]+/)*[a-zA-Z0-9]+\.[a-zA-Z0-9]+)$
 * 
 * Examples of valid patterns include "path/to/file.txt", "*.txt", and "file.txt".
 * Examples of invalid patterns include "path/to/file" (no extension) and "path/./file.txt" (dot in the middle).
 * 
 * @param input The string to check.
 * @return Whether the string is a valid pattern.
 */
bool vgit::isValidPattern(const std::string& input) 
{
    std::regex pattern(R"((([a-zA-Z0-9]+/)*[a-zA-Z0-9]+\.[a-zA-Z0-9]+)$)");
    return std::regex_match(input, pattern);
}



/**
 * Reads the .gitignore file and returns a multimap of ignored items.
 * 
 * The multimap is keyed by the type of ignored item (paths, extensions, files).
 * The value is the full path of the item.
 * 
 * If the .gitignore file does not exist, it returns an empty multimap.
 * 
 * @return A multimap of ignored items.
 */
const std::multimap<std::string, std::string> vgit::Ignore_list(void)
{
    std::multimap<std::string, std::string> Ignore_list_multimap; // create multimap

    std::ifstream gitignoreFile(".gitignore"); // open .gitignore file
    if (gitignoreFile.is_open())
    {
        std::string line;
        while (getline(gitignoreFile, line)) // read each line
        {
            if (line.back() == '/') // add ignored path
            {
                Ignore_list_multimap.insert({"paths", main_directoryPath.string() + "/" + line});
            }
            else if (line.find("*.") != std::string::npos) // add ignored extension
            {
                Ignore_list_multimap.insert({"extensions", main_directoryPath.string() + "/" + line});
            }
            else if (line.empty() || line[0] == '#') // skip empty lines and comments
            {
                continue;
            }
            else if (isValidPattern(line)) // add ignored file
            {
                Ignore_list_multimap.insert({"files", main_directoryPath.string() + "/" + line});
            }
        }
        gitignoreFile.close(); // close .gitignore file
    }
    else
    {
        std::cout << ".gitignore file not found" << std::endl;
    }

    // print ignore_list_multimap
    // for(const auto &[key, value] : Ignore_list_multimap)
    // {
    //     std::cout << key << ": " << value << std::endl;
    // }

    return Ignore_list_multimap;
}


vgit::CMD_States vgit::vgit_add(const std::string &message)
{
    if(!message.empty())
    {
        if(message == ".")
        {
            add_all_files(main_directoryPath.string());
        }else
        {
            std::stringstream ss(message);
            std::string arg;
            while (std::getline(ss, arg, ' ')) 
            {
                bool patternMatched = false;
                for (const auto& [pattern, func] : patternFunctions)
                {
                    std::regex regexPattern(pattern);
                    if (std::regex_match(arg, regexPattern))
                    {
                        std::cout << "Matched pattern \"" << pattern << "\" for \"" << arg << "\"" << std::endl;
                        func(arg);
                        patternMatched = true;
                        break;
                    }
                }

                if (!patternMatched)
                {
                    std::cout << "Warning: No matching pattern for \"" << arg << "\"" << std::endl;
                }
            }
        }
    }else
    {
        std::cout << "Error: This must don't have any arguments" << std::endl;
    }
    return CMD_States::Success;
}

void vgit::scan_file(const std::string& message, const std::string& extenstion)
{
    
}


void vgit::scan_path(const std::string& path)
{
    if (std::filesystem::is_directory(path)) 
    {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(path)) 
        {
            const auto target = entry.path().string();    
            bool isIgnored = false;

            for (const auto& [key, value] : ignored_files) 
            {
                if (key == "extensions") // check if file extension is ignored
                {
                    std::string regexPattern = std::regex_replace(value, std::regex(R"(\*)"), R"(.*)");
                    std::regex pattern(regexPattern, std::regex::icase); // ignore case
                    if (std::regex_match(target, pattern)) {
                        std::cout << Colors::RED << "[Ignored] pattern: " << entry.path() << Colors::RESET << "\n";
                        isIgnored = true;
                        break;
                    }
                } 
                else if (key == "paths" && target.find(value) != std::string::npos) // check if path is ignored
                {
                    std::cout << Colors::RED << "[Ignored] path: " << value << Colors::RESET << "\n";
                    isIgnored = true;
                    break;
                } 
                else if (key == "files" && target == value) // check if file is ignored
                {
                    std::cout << Colors::RED << "[Ignored] file: " << value << Colors::RESET << "\n";
                    isIgnored = true;
                    break;
                }
            }

            if (isIgnored) {
                continue; 
            }

            if (std::filesystem::is_regular_file(entry.path())) 
            {
                // @TODO : add to index file
                std::cout << Colors::GREEN << "[File] " << entry.path() << " (Size: " << std::filesystem::file_size(entry.path()) << " bytes)" << Colors::RESET << std::endl;
            }
        }
    } else {
        std::cerr << "The specified path is not a valid directory!" << std::endl;
    }
}

void vgit::add_all_files(const std::string& message)
{
    scan_path(message);
}


void vgit::add_paths(const std::string& message)
{
    std::cout << "===============add paths===============" << std::endl;
    size_t pos = message.rfind('/');
    std::string path = (pos != std::string::npos) ? message.substr(0, pos + 1) : message;
    path  = main_directoryPath.string() + "/" + path;
    scan_path(path);
}

void vgit::add_extensions(const std::string& message)
{
    std::cout << "===============add extensions===============" << std::endl;
    size_t pos = message.rfind('/');
    std::string path = (pos != std::string::npos) ? message.substr(0, pos + 1) : message;
    path  = main_directoryPath.string() + "/" + path;
    pos = message.rfind('.');
    std::string extension = (pos != std::string::npos) ? message.substr(pos) : message;
    std::cout << "extension" << extension << std::endl;
    scan_file(path, extension);

}

void vgit::add_files(const std::string& message)
{
    std::cout << "===============add files===============" << std::endl;
    size_t pos = message.rfind('/');
    std::string path = (pos != std::string::npos) ? message.substr(0, pos + 1) : message;
    std::string filename = (pos != std::string::npos) ? message.substr(pos + 1) : message;
    path  = main_directoryPath.string() + "/" + path;
    auto rang = ignored_files.equal_range("files");
    for(auto it = rang.first; it != rang.second; ++it)
    {
        if(it->second == path) {
            std::cout << Colors::RED << "[Ignored] path: " << path << Colors::RESET << "\n";
            continue;
        }else
        {
            if(std::filesystem::is_regular_file(message))
            {
                std::cout << Colors::GREEN << "[File] " << message << " (Size: " << std::filesystem::file_size(message) << " bytes)" << Colors::RESET << "\n";
                break;
            }
        }
    }
    // std::cout << "add files" << std::endl;
}



// if(arg.find("/*") != std::string::npos)
// {
//     std::filesystem::path directoryPath = std::filesystem::current_path();
//     std::size_t pos = arg.find_last_not_of("/*");
//     arg.erase(pos + 2);
//     directoryPath += + "/" + arg;
//     for (const auto& entry : std::filesystem::recursive_directory_iterator(directoryPath)) 
//     {
//         if (std::filesystem::is_regular_file(entry.path())) 
//         {
//             std::cout << "[File] " << entry.path() << " (Size: " << std::filesystem::file_size(entry.path()) << " bytes)" << std::endl;
//         }
//     }

// }
// else if(arg.find(".") != std::string::npos)
// {
//     if (std::filesystem::is_regular_file(arg)) 
//     {
//         std::cout << "[File] " << arg << " (Size: " << std::filesystem::file_size(arg) << " bytes)" << std::endl;
//     }
// }

