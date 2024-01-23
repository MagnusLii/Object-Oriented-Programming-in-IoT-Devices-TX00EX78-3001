#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

int main() {
    std::vector<std::string> directoryNames;
    std::string input;

    // Get dir names.
    std::cout << "Enter directory names (enter a blank line to stop): ";
    while (std::getline(std::cin, input) && !input.empty()) {
        directoryNames.push_back(input);
    }

    // Form path
    fs::path relativePath;
    for (const auto& name : directoryNames) {
        relativePath /= name;
    }

    // Create dirs
    fs::create_directories(relativePath);

    // Open result.txt
    fs::path filePath = relativePath / "result.txt";
    std::ofstream outputFile(filePath);

    // Print path to result.txt
    std::cout << "Absolute path to the file: " << fs::absolute(filePath) << std::endl;
    outputFile << "Absolute path to the file: " << fs::absolute(filePath) << std::endl;

    std::cout << "\n" << std::endl;

    // Print vector
    std::cout << "Content of the string vector:\n";
    for (const auto& name : directoryNames) {
        std::cout << name << std::endl;
        outputFile << name << std::endl;
    }

    std::cout << "\n" << std::endl;

    // Print relative path
    std::cout << "Relative path to the file: " << relativePath << std::endl;
    outputFile << "Relative path to the file: " << relativePath << std::endl;

    return 0;
}
