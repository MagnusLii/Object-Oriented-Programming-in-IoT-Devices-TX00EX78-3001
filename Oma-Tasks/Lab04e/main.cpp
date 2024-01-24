#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
        std::getline(is >> std::ws, house.address, ' ');
        is >> house.area >> house.price;
        return is;
    }

    bool operator<(const House& other) const {
        return price / area < other.price / other.area;
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

int main() {
    std::vector<House> houses;


    std::string address;
    double area;
    int price;

    // Ask user to enter the house informa3on (address, area, price) and use constructor to create
    // a house by passing the informa3on as parameters
    std::cout << "Enter house 1 information (address, area, price): ";
    std::cin >> address >> area >> price;
    houses.emplace_back(address, area, price);

    // Create a house using default constructor, ask user to enter the house informa3on and use
    // seJer func3ons before adding the house to the vector
    House house2;
    std::cout << "Enter house 2 information (address, area, price): ";
    std::cin >> address >> area >> price;
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
    std::cin >> address >> area >> price;
    houses.emplace_back(address, area, price);

    // 5
    std::cout << "Enter house 5 information (address, area, price): ";
    std::cin >> address >> area >> price;
    houses.emplace_back(address, area, price);

    // Then sort the vector using std::sort
    std::sort(houses.begin(), houses.end());

    // and print the house information one house per line.
    for (const auto& house : houses) {
        std::cout << house << std::endl;
    }

    return 0;
}
