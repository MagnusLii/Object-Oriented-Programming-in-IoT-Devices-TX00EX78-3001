#include <iostream>
#include <deque>
#include <vector>
#include <limits>

class RunningAverage {
private:
    std::deque<int> values;
    int maxSize;

public:
    RunningAverage(int size) : maxSize(size) {}

    void add_value(int value) {
        if (values.size() == maxSize) {
            values.pop_front();
        }
        values.push_back(value);
    }

    double get_average() {
        double sum = 0;
        for (int value : values) {
            sum += value;
        }
        return sum / values.size();
    }
};

int main() {
    RunningAverage avg(5);
    int value;

    do {
        std::cout << "Enter a number (enter 0 to stop): ";

        while (!(std::cin >> value)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number: ";
        }

        if (value != 0) {
            avg.add_value(value);
            std::cout << "Current running average: " << avg.get_average() << std::endl;
        }

    } while (value != 0);

    std::cout << "Final running average: " << avg.get_average() << std::endl;

    return 0;
}
