#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

class House {
public:
    House() {}

    House(const std::string& address, double area, int price)
        : address(address), area(area), price(price) {}

    friend std::ostream& operator<<(std::ostream& os, const House& house) {
        os << house.address << " " << house.area << " " << house.price;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, House& house) {
        while (!(is >> house.address >> house.area >> house.price) || house.area <= 0 || house.price < 0) {
            std::cout << "Invalid input. Please enter valid values for area and price: ";
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        return is;
    }

    bool operator<(const House& other) const {
        if (area == 0.0 && other.area == 0.0) {
            return price < other.price; // both prices are zero
        } else if (area == 0.0) {
            return false; // base obj area = 0, so not less.
        } else if (other.area == 0.0) {
            return true; // other obj area = 0, so less.
        } else {
            return price / area < other.price / other.area;
        }
    }

    void setAddress(const std::string& address) {
        this->address = address;
    }

    void setArea(double area) {
        this->area = area;
    }

    void setPrice(int price) {
        this->price = price;
    }

private:
    std::string address;
    double area;
    int price;
};

// turn into class method???
void getInput(std::string& address, double& area, int& price) {
    while (!(std::cin >> address >> area >> price) || area <= 0 || price < 0) {
        std::cout << "Invalid input. Please enter valid values for area and price: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main() {
    std::vector<House> houses;


    std::string address;
    double area;
    int price;

    // Ask user to enter the house informa3on (address, area, price) and use constructor to create
    // a house by passing the information as parameters
    std::cout << "Enter house 1 information (address, area, price): ";
    getInput(address, area, price);
    houses.emplace_back(address, area, price);

    // Create a house using default constructor, ask user to enter the house information and use
    // seJer functions before adding the house to the vector
    std::cout << "Enter house 2 information (address, area, price): ";
    getInput(address, area, price);
    House house2;
    house2.setAddress(address);
    house2.setArea(area);
    house2.setPrice(price);
    houses.push_back(house2);

    // Create house using default constructor and read values using the input operator
    House house3;
    std::cout << "Enter house 3 information (address, area, price): ";
    std::cin >> house3;
    houses.push_back(house3);

    // 4
    std::cout << "Enter house 4 information (address, area, price): ";
    getInput(address, area, price);
    houses.emplace_back(address, area, price);

    // 5
    std::cout << "Enter house 5 information (address, area, price): ";
    getInput(address, area, price);
    houses.emplace_back(address, area, price);

    // Then sort the vector using std::sort
    std::sort(houses.begin(), houses.end());

    // and print the house information one house per line.
    for (const auto& house : houses) {
        std::cout << house << std::endl;
    }

    return 0;
}
