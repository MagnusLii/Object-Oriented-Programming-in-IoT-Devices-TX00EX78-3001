#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <random>
#include <ctime>

class LottoNumGen {
public:
    LottoNumGen(int min, int max) : distribution(min, max) {
        std::random_device rd;
        generator = std::default_random_engine(rd());
        generatedCount = 0;
        totalCount = max - min;
    }

    int operator()() {
        if (generatedCount > totalCount) {
            throw std::runtime_error("Unable to produce unique random number.");
        }

        int number;
        do {
            number = distribution(generator);
        } while (std::find(numbers.begin(), numbers.end(), number) != numbers.end());
        numbers.push_back(number);
        generatedCount++;
        return number;
    }

private:
    std::vector<int> numbers;                  // Vector to store generated numbers, to verify no duplicates
    std::uniform_int_distribution<> distribution; // Distribution
    std::default_random_engine generator;      // Random number generator
    int generatedCount;             
    int totalCount;                      
};

void test_generator(LottoNumGen ur, int count) {
    std::cout << "Generating numbers: " << std::endl;
    int i = 0;
    
    try {
        for (i; i < count; i++) {
            std::cout << ur() << std::endl;
        }
        std::cout << std::endl;
    } catch (std::exception& error) {
        std::cout << "Exception: " << error.what() << std::endl;
        std::cout << "Tried to generate " << count << " random numbers. Got only " << i << std::endl;
    }

    return;
}

int main(void) {
    LottoNumGen randGen(5, 13);
    test_generator(randGen, 6);
    test_generator(randGen, 9);
    test_generator(randGen, 13); // this will cause exception
    LottoNumGen randGen2(1, 35);
    test_generator(randGen2, 7);
    test_generator(randGen2, 7);
    test_generator(randGen2, 7);
    test_generator(randGen2, 70); // this will cause exception

    return 0;
}

