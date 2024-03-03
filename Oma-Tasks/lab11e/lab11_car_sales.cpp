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

class Car {
	friend std::ostream &operator<<(std::ostream &out, const Car &car);
public:
	explicit Car(std::string m="Ford", std::string l="", int ml=0) :
        model(std::move(m)),
        license(!l.empty()?std::move(l):(rand()%2?"FOO-":"BAR-") + std::to_string(rand()%999+1)),
        mileage(ml>0?ml:rand()%10000) {}
	~Car() { std::cout << model << " " << license << " deleted" << std::endl; };
	void Read();
	const std::string &GetLicense() const { return license; }
private:
	std::string model;
	std::string license;
	int mileage;
};

void Car::Read()
{
	// std::cout << "Enter car information" << std::endl;
	// replace the following with your own code
	model = "Seat";
	license = (rand() % 2 ? "ZAP-" : "ZIP-") + std::to_string(rand() % 999 + 1);
	mileage = 10000 + rand() % 10000;
}

std::ostream & operator<<(std::ostream & out, const Car & car)
{
	std::cout << "Model: " << car.model << std::endl << "License: " << car.license << std::endl << "Mileage: " << car.mileage << std::endl;

	return out;
}

/* ---------------------- */

class Website {
public:
	explicit Website(std::string n="carweb.com") : name(std::move(n)) {}
	~Website() { std::cout << name << " deleted" << std::endl; };
	void add(Car *car, std::string &dealer) { listing[car] = dealer; }
	void print(std::ostream &out = std::cout) {
        out << name << std::endl;
        for(auto [car, dealer] : listing) out << dealer << ":" << std::endl << *car;
        out << name << " end of list" << std::endl;
	}
	void remove(Car *car) { listing.erase(car); }
private:
	std::map<Car *, std::string> listing;
	std::string name;
};

class Dealer {
	friend std::ostream &operator<<(std::ostream &out, const Dealer &dealer);
public:
	explicit Dealer(std::string name_ = "John Doe") : name(std::move(name_)) {};
	~Dealer() { std::cout << name << " deleted" << std::endl; };
	void buy();
	void sell();
	void add(Car *car) {
        cars.push_back(car);
        for (auto site : sites) site->add(car, name);
    }
	void add_site(Website *w) {
        sites.push_back(w);
    }
private:
	std::string name;
	std::vector<Car *> cars;
	std::vector<Website *> sites;
};

void Dealer::buy()
{
	Car *car = new Car;
	car->Read();
	add(car);
}

void Dealer::sell()
{
	std::cout << *this; // print my list of cars
	std::cout << "Enter license of car you want to buy: " << std::flush;

	std::string license;
	std::cin >> license;
	auto ci = std::find_if(cars.begin(), cars.end(), [&license](Car *c) {return license == c->GetLicense(); });
	if (ci != cars.end()) {
        // modify code so that you don't need to remove a sold car from the website
		for (auto site : sites) site->remove(*ci);
		cars.erase(ci);
	}
}


std::ostream & operator<<(std::ostream & out, const Dealer & dealer)
{
	std::cout << dealer.name << "'s cars for sale" << std::endl;
	for (auto car : dealer.cars) std::cout << *car;
	std::cout << "End of " << dealer.name << "'s cars listing" << std::endl;

	return out;
}

/* ---------------------- */



void car_sales()
{
	std::cout << "Car sales started" << std::endl;
	auto *wa = new Website("www.autos.com");
	auto *wb = new Website("www.bilar.com");
	auto *a = new Dealer("Alan Aldis");
	auto *b = new Dealer("Bill Munny");
	{ // inner scope to make some if the pointers go out of scope before the function ends.
        auto *wc = new Website("www.cars.com");
		auto *c = new Dealer("Casey Ball");
		Car *ca = new Car;
		Car *cb = new Car;

		a->add_site(wa);
		a->add_site(wb);
		b->add_site(wb);
		b->add_site(wc);
		c->add_site(wa);
		c->add_site(wb);
		c->add_site(wc);

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


