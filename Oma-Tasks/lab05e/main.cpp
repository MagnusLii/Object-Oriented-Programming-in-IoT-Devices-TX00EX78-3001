#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <random>
#include <ctime>

class LottoNumGen {
public:
    LottoNumGen(int min, int max) : distribution(min, max) {
        unsigned int seed = std::time(NULL);
        std::srand(seed);
    }

    int operator()() {
        return distribution(generator); // Generate a random number
    }

private:
    std::default_random_engine generator; // Random number generator engine
    std::uniform_int_distribution<int> distribution; // Uniform distribution for generating rand ints
};

int main() {

    std::string userinput;

    do {
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

    std::cout << "Eurojackpot: ";
    std::copy(eurojackpotNumbers.begin(), eurojackpotNumbers.end(), std::ostream_iterator<int>(std::cout, " ")); 
    std::cout << std::endl;

    std::vector<int> matchingNumbers; // Vector to store matching numbers

    // Find matching numbers
    std::set_intersection(lottoNumbers.begin(), lottoNumbers.end(),
                          vikingLottoNumbers.begin(), vikingLottoNumbers.end(),
                          std::back_inserter(matchingNumbers));

    std::set_intersection(matchingNumbers.begin(), matchingNumbers.end(),
                          eurojackpotNumbers.begin(), eurojackpotNumbers.end(),
                          std::back_inserter(matchingNumbers));

    std::cout << "Matching numbers" << std::endl;
    std::for_each(matchingNumbers.begin(), matchingNumbers.end(), [](int number) {
        static int index = 1;
        std::cout << "#" << index++ << ": " << number << std::endl; // Print the matching numbers
    });

    
    std::cout << "Do you want to continue? (yes/no): ";
    std::cin >> userinput; // Read user input

    } while (userinput == "yes");

    return 0;
}
