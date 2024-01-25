#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>
#include <sstream>
#include <string>

void getInput(std::string &address, double &area, int &price);
void removeSpecials(std::string &str);

class House
{
public:
    House() {}

    House(const std::string &address, double area, int price)
        : address(address), area(area), price(price) {}

    friend std::ostream &operator<<(std::ostream &os, const House &house)
    {
        os << "Address: " << house.address << ",  area: " << house.area << ", price: " << house.price;
        return os;
    }

    friend std::istream &operator>>(std::istream &is, House &house)
    {
        getInput(house.address, house.area, house.price);
        removeSpecials(house.address);
        return is;
    }

    bool operator<(const House &other) const
    {
        if (area == 0.0 && other.area == 0.0)
        {
            return price < other.price; // both prices are zero
        }
        else if (area == 0.0)
        {
            return false; // base obj area = 0, so not less.
        }
        else if (other.area == 0.0)
        {
            return true; // other obj area = 0, so less.
        }
        else
        {
            return price / area < other.price / other.area;
        }
    }

    void setAddress(const std::string &address)
    {
        this->address = address;
    }

    void setArea(double area)
    {
        this->area = area;
    }

    void setPrice(int price)
    {
        this->price = price;
    }

private:
    std::string address;
    double area;
    int price;
};

void removeSpecials(std::string &str)
{
    str.erase(std::remove_if(str.begin(), str.end(), [](char c)
                             { return !std::isalnum(c) && c != ' '; }),
              str.end());
}

void getInput(std::string &address, double &area, int &price)
{
    bool done = false;

    while (!done)
    {
        try
        {
            std::string userinput;
            std::getline(std::cin, userinput);
            size_t lastDelimiterPos = userinput.rfind(' ');
            if (lastDelimiterPos != std::string::npos)
            {
                size_t secondLastDelimiterPos = userinput.rfind(' ', lastDelimiterPos - 1);

                address = userinput.substr(0, secondLastDelimiterPos);
                area = std::stod(userinput.substr(secondLastDelimiterPos + 1, lastDelimiterPos - secondLastDelimiterPos - 1));
                price = std::stoi(userinput.substr(lastDelimiterPos + 1));
                done = true;
            }
            else
            {
                throw std::invalid_argument("Invalid input");
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Invalid input, press enter to try again." << std::endl;
            std::cin.clear();
            std::cout << "Enter house information (address, area, price): ";
        }
    }
}

int main()
{
    std::vector<House> houses;

    std::string address;
    double area;
    int price;

    // Ask user to enter the house information (address, area, price) and use constructor to create
    // a house by passing the information as parameters
    std::cout << "Enter house 1 information (address, area, price): ";
    getInput(address, area, price);
    removeSpecials(address);
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
    removeSpecials(address);
    houses.emplace_back(address, area, price);

    // 5
    std::cout << "Enter house 5 information (address, area, price): ";
    getInput(address, area, price);
    removeSpecials(address);
    houses.emplace_back(address, area, price);

    // Then sort the vector using std::sort
    std::sort(houses.begin(), houses.end());

    // and print the house information one house per line.
    for (const auto &house : houses)
    {
        std::cout << house << std::endl;
    }

    return 0;
}
