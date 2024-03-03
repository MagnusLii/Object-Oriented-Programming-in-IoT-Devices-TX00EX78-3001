#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <ctime>
#include <map>

// Class representing a Car
class Car {
	friend std::ostream &operator<<(std::ostream &out, const Car &car);
public:
	// Constructor with default values for model, license, and mileage
	explicit Car(std::string m="Ford", std::string l="", int ml=0) :
        model(std::move(m)),
        // Generate a random license if none is provided
        license(!l.empty()?std::move(l):(rand()%2?"FOO-":"BAR-") + std::to_string(rand()%999+1)),
        // Use provided mileage if positive; otherwise, generate a random mileage
        mileage(ml>0?ml:rand()%10000) {}

	// Destructor that prints a message when a car is deleted
	~Car() { std::cout << model << " " << license << " deleted" << std::endl; };

	// Method to read car information from user (not currently used)
	void Read();

	// Getter for the license plate
	const std::string &GetLicense() const { return license; }
private:
	std::string model;
	std::string license;
	int mileage;
};

// Method to read car information (not currently used)
void Car::Read()
{
	// std::cout << "Enter car information" << std::endl;
	// replace the following with your own code
	model = "Seat";
	license = (rand() % 2 ? "ZAP-" : "ZIP-") + std::to_string(rand() % 999 + 1);
	mileage = 10000 + rand() % 10000;
}

// Overloaded output stream operator for printing Car objects
std::ostream & operator<<(std::ostream & out, const Car & car)
{
	std::cout << "Model: " << car.model << std::endl << "License: " << car.license << std::endl << "Mileage: " << car.mileage << std::endl;

	return out;
}

/* ---------------------- */

// Class representing a Website that lists cars for sale
class Website {
public:
	// Constructor with a default name for the website
	explicit Website(std::string n="carweb.com") : name(std::move(n)) {}

	// Destructor that prints a message when a website is deleted
	~Website() { std::cout << name << " deleted" << std::endl; };

	// Add a car to the website's listing along with the dealer's name
	void add(Car *car, std::string &dealer) { listing[car] = dealer; }

	// Print the website's listing, including dealer names and car details
	void print(std::ostream &out = std::cout) {
        out << name << std::endl;
        for(auto [car, dealer] : listing) out << dealer << ":" << std::endl << *car;
        out << name << " end of list" << std::endl;
	}

	// Remove a car from the website's listing
	void remove(Car *car) { listing.erase(car); }
private:
	std::map<Car *, std::string> listing;
	std::string name;
};

// Class representing a Car Dealer
class Dealer {
	friend std::ostream &operator<<(std::ostream &out, const Dealer &dealer);
public:
	// Constructor with a default name for the dealer
	explicit Dealer(std::string name_ = "John Doe") : name(std::move(name_)) {};

	// Destructor that prints a message when a dealer is deleted
	~Dealer() { std::cout << name << " deleted" << std::endl; };

	// Buy a new car, read its information, add it to the dealer's list, and list it on associated websites
	void buy();

	// Sell a car by prompting the user for the license plate, removing it from the dealer's list,
	// and removing it from associated websites
	void sell();

	// Add a car to the dealer's list and list it on associated websites
	void add(Car *car) {
        cars.push_back(car);
        for (auto site : sites) site->add(car, name);
    }

	// Add a website to the dealer's list of associated websites
	void add_site(Website *w) {
        sites.push_back(w);
    }
private:
	std::string name;
	std::vector<Car *> cars;
	std::vector<Website *> sites;
};

// Method to buy a new car, read its information, add it to the dealer's list, and list it on associated websites
void Dealer::buy()
{
	Car *car = new Car;
	car->Read();
	add(car);
}

// Method to sell a car
void Dealer::sell()
{
	// Print the list of cars for sale by the dealer
	std::cout << *this; // print my list of cars
	std::cout << "Enter license of car you want to buy: " << std::flush;

	// Prompt the user for the license plate of the car they want to buy
	std::string license;
	std::cin >> license;

	// Find the car in the dealer's list based on the entered license plate
	auto ci = std::find_if(cars.begin(), cars.end(), [&license](Car *c) {return license == c->GetLicense(); });

	// If the car is found, remove it from associated websites and the dealer's list
	if (ci != cars.end()) {
        // Modify code so that you don't need to remove a sold car from the website
		for (auto site : sites) site->remove(*ci);
		cars.erase(ci);
	}
}

// Overloaded output stream operator for printing Dealer objects
std::ostream & operator<<(std::ostream & out, const Dealer & dealer)
{
	std::cout << dealer.name << "'s cars for sale" << std::endl;
	for (auto car : dealer.cars) std::cout << *car;
	std::cout << "End of " << dealer.name << "'s cars listing" << std::endl;

	return out;
}

/* ---------------------- */

// Function to simulate a car sales scenario
void car_sales()
{
	std::cout << "Car sales started" << std::endl;

	// Create websites and dealers
	auto *wa = new Website("www.autos.com");
	auto *wb = new Website("www.bilar.com");
	auto *a = new Dealer("Alan Aldis");
	auto *b = new Dealer("Bill Munny");

	{ // Inner scope to make some of the pointers go out of scope before the function ends.
        auto *wc = new Website("www.cars.com");
		auto *c = new Dealer("Casey Ball");
		Car *ca = new Car;
		Car *cb = new Car;

		// Add websites to dealers
		a->add_site(wa);
		a->add_site(wb);
		b->add_site(wb);
		b->add_site(wc);
		c->add_site(wa);
		c->add_site(wb);
		c->add_site(wc);

		// Buy cars for dealers
		a->buy();
		a->buy();
		a->buy();
		a->buy();

		b->buy();
		b->buy();
		b->buy();

		c->buy();
		c->buy();
		c->add(ca);
		c->add(cb);

		wa->print();
		wb->print();
		wc->print();

		std::cout << *a << *b << *c << std::endl;

		a->sell();

		std::cout << *a << *b << *c << std::endl;

		wa->print();
		wb->print();
		wc->print();
	}

	wa->print();
	wb->print();


	std::cout << "Car sales ended" << std::endl;

}

int main(int argc, char **argv) {

	srand(time(nullptr));

	car_sales();

	return 0;
}


