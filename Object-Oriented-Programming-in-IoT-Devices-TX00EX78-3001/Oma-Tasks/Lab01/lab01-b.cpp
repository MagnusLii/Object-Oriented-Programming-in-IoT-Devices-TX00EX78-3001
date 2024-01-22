#include <iostream>
#include <string>

void replaceCharacter(std::string& str, char ch) {
    for (char& c : str) {
        if (c == ch) {
            c = '_';
        }
    }
}

int main() {
    std::string str;
    char ch;

    while (true) {
        std::cout << "Enter a string: ";
        std::getline(std::cin, str);

        std::cout << "Enter character to replace or \"stop\": ";
        std::string input;
        std::getline(std::cin, input);

        if (input == "stop") {
            break;
        }

        ch = input[0];
        replaceCharacter(str, ch);

        std::cout << "Result: " << str << std::endl;
    }

    return 0;
}
