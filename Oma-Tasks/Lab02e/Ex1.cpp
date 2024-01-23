#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cctype>

int main() {
    std::string line;
    while (true) {
        std::cout << "Enter a line with numbers or \"stop\": ";
        std::getline(std::cin, line);

        // Convert to lowercase.
        std::transform(line.begin(), line.end(), line.begin(), [](unsigned char c) { // This shit is unreadable...
            return std::tolower(c);
        });

        if (line.substr(0, 4) == "stop") {
            break;
        }

        std::istringstream iss(line);
        int num;
        int sum = 0;
        int count = 0;

        while (iss >> num) {
            sum += num;
            count++;
        }

        std::cout << "Total of " << count << " numbers is " << sum << std::endl;
    }

    return 0;
}
