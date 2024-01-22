#include <iostream>
#include <vector>
#include <limits>

int main() {
    std::vector<int> numbers;
    int count;

    std::cout << "How many numbers do you want to enter? ";
    std::cin >> count;

    for (int i = 0; i < count; i++) {
        int number;
        std::cout << "Enter nr[" << i + 1 << "]: ";
        while (!(std::cin >> number)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number: ";
        }
        numbers.push_back(number);
    }

    std::cout << "You entered: ";
    for (int i = 0; i < numbers.size(); i++) {
        std::cout << numbers[i];
        if (i != numbers.size() - 1) {
            std::cout << ", ";
        }
    }

    return 0;
}
