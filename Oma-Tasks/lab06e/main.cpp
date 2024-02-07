#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <string>
#include <cctype>
#include <limits>

void getInput(std::istream &inputStream, std::string &address, double &area, int &price);
void removeSpecials(std::string &str);

class House{
public:
    House() {}

    House(const std::string &address, double area, int price)
        : address(address), area(area), price(price) {}

    std::string getAddress() const{
        return address;
    }

    friend std::ostream &operator<<(std::ostream &os, const House &house){
        os << house.address << " " << house.area << " " << house.price << std::endl;
        return os;
    }

    friend std::istream &operator>>(std::istream &is, House &house){
        getInput(is, house.address, house.area, house.price);
        removeSpecials(house.address);
        return is;
    }

    bool operator<(const House &other) const{
        if (area == 0.0 && other.area == 0.0){
            return price < other.price; // both prices are zero
        }
        else if (area == 0.0){
            return false; // base obj area = 0, so not less.
        }
        else if (other.area == 0.0){
            return true; // other obj area = 0, so less.
        }
        else{
            return price / area < other.price / other.area;
        }
    }

private:
    std::string address;
    double area;
    int price;
};

class Apartment{
public:
    Apartment(std::shared_ptr<House> house, int apartmentNumber, double size, int monthlyRent)
        : house(house), apartmentNumber(apartmentNumber), size(size), monthlyRent(monthlyRent) {}

    bool operator<(const Apartment &other) const{
        return monthlyRent < other.monthlyRent;
    }

    void printApartmentInfo() const{
        std::cout << "Address: " << house->getAddress() << ", Apartment Number: " << apartmentNumber << std::endl;
        std::cout << "Size: " << size << " m2" << std::endl;
        std::cout << "Monthly Rent: " << monthlyRent << std::endl;
    }

private:
    std::shared_ptr<House> house;
    int apartmentNumber;
    double size;
    int monthlyRent;
};

int main(){
    std::vector<Apartment> apartments;

    // Write a program that creates two houses and defines a vector of Apartments. 
    std::shared_ptr<House> house1 = std::make_shared<House>("132 tie 5B", 100.0, 1000);
    std::shared_ptr<House> house2 = std::make_shared<House>("road road 7", 150.0, 1500);

    // Program adds three apartments of the first house
    apartments.push_back(Apartment(house1, 18, 111, 132));
    apartments.push_back(Apartment(house1, 7, 12.3, 413279));
    apartments.push_back(Apartment(house1, 3, 44.4, 123));

    // and four apartments of the second house to the vector.
    apartments.push_back(Apartment(house2, 10, 666, 100));
    apartments.push_back(Apartment(house2, 20, 69, 1000));
    apartments.push_back(Apartment(house2, 30, 420, 10000));
    apartments.push_back(Apartment(house2, 40, 1337, 100000));

    // Then program sorts the apartments and prints the apartment informa2on on separate lines. 
    std::sort(apartments.begin(), apartments.end());
    int counter = 0;
    for (const auto &apartment : apartments){
        std::cout << "Apartment " << ++counter << std::endl;
        apartment.printApartmentInfo();
        std::cout << std::endl;
    }

    return 0;
}

void removeSpecials(std::string &str){
    str.erase(std::remove_if(str.begin(), str.end(), [](char c)
                             { return !std::isalnum(c) && c != ' '; }),
              str.end());
}

void getInput(std::istream &inputStream, std::string &address, double &area, int &price){
    bool done = false;

    while (!done){
        try{
            std::string userinput;
            std::getline(inputStream, userinput);
            size_t lastDelimiterPos = userinput.rfind(' ');

            if (lastDelimiterPos != std::string::npos){
                size_t secondLastDelimiterPos = userinput.rfind(' ', lastDelimiterPos - 1);

                address = userinput.substr(0, secondLastDelimiterPos);
                area = std::stod(userinput.substr(secondLastDelimiterPos + 1, lastDelimiterPos - secondLastDelimiterPos - 1));
                price = std::stoi(userinput.substr(lastDelimiterPos + 1));
                done = true;
            }
            else{
                throw std::invalid_argument("Invalid input");
            }
        }
        catch (const std::exception &e){
            // Instead of prints, flags should be raised on the input stream.
            std::cerr << "Invalid input, press enter to try again." << std::endl;
            inputStream.clear();
            inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter house information (address, area, price): ";
        }
    }
}