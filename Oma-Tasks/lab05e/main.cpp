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
    }

    int operator()() {
        int number;
        do {
            number = distribution(generator);
        } while (std::find(numbers.begin(), numbers.end(), number) != numbers.end());
        numbers.push_back(number);
        return number;
    }

private:
    std::vector<int> numbers;                  // Vector to store generated numbers, to verify no duplicates
    std::uniform_int_distribution<> distribution; // Distribution
    std::default_random_engine generator;      // Random number generator
};

class IndexPrinter {
public:
    IndexPrinter() : index(1) {}

    void operator()(int number) {
        std::cout << "#" << index++ << ": " << number << std::endl; // Print nums
    }

private:
    int index;
};

void antiLoopFunction() {
    std::string userinput;

    LottoNumGen lottoGenerator(1, 40); // 1-40
    LottoNumGen vikingLottoGenerator(1, 48); // 1-48
    LottoNumGen eurojackpotGenerator(1, 50); // 1-50

    // Vectors
    std::vector<int> lottoNumbers(7);
    std::vector<int> vikingLottoNumbers(6);
    std::vector<int> eurojackpotNumbers(5);

    // Generate random numbers
    std::generate(lottoNumbers.begin(), lottoNumbers.end(), lottoGenerator);
    std::generate(vikingLottoNumbers.begin(), vikingLottoNumbers.end(), vikingLottoGenerator);
    std::generate(eurojackpotNumbers.begin(), eurojackpotNumbers.end(), eurojackpotGenerator);

    // Print
    std::cout << "Lotto: ";
    std::copy(lottoNumbers.begin(), lottoNumbers.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    std::cout << "Viking lotto: ";
    std::copy(vikingLottoNumbers.begin(), vikingLottoNumbers.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    
    std::vector<int> matchingNumbers;

    std::sort(lottoNumbers.begin(), lottoNumbers.end());
    std::sort(vikingLottoNumbers.begin(), vikingLottoNumbers.end());

    // Find matching numbers
    std::set_intersection(lottoNumbers.begin(), lottoNumbers.end(),
                            vikingLottoNumbers.begin(), vikingLottoNumbers.end(),
                            std::back_inserter(matchingNumbers));

    std::cout << "Matching numbers" << std::endl;
    IndexPrinter match2;
    std::for_each(matchingNumbers.begin(), matchingNumbers.end(), match2);

    std::cout << "Eurojackpot: ";
    std::copy(eurojackpotNumbers.begin(), eurojackpotNumbers.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    std::vector<int> matchingNumbers2;

    std::sort(matchingNumbers.begin(), matchingNumbers.end());
    std::sort(eurojackpotNumbers.begin(), eurojackpotNumbers.end());

    std::set_intersection(matchingNumbers.begin(), matchingNumbers.end(),
                        eurojackpotNumbers.begin(), eurojackpotNumbers.end(),
                        std::back_inserter(matchingNumbers2));

    std::cout << "Matching numbers in three sets" << std::endl;
    IndexPrinter match3;
    std::for_each(matchingNumbers2.begin(), matchingNumbers2.end(), match3);

    std::cout << "Do you want to continue? (yes/no): ";
    std::cin >> userinput; // Read user input

    if (userinput == "yes") {
        std::cout << std::endl;
        antiLoopFunction();
    }
    
    return;
}


int main() {
    antiLoopFunction();
    return 0;
}
