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
	// why????
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
    explicit Website(std::string n = "carweb.com") : name(std::move(n)) {}
    ~Website() { std::cout << name << " deleted" << std::endl; };
    void add(std::shared_ptr<Car> car, std::string &dealer) {
        listing[car] = dealer;
    }
    void print(std::ostream &out = std::cout) {
        out << name << std::endl;
        for (auto &[car, dealer] : listing) {
            if (auto carSharedPtr = car.lock()) {
                out << dealer << ":" << std::endl << *carSharedPtr;
            } else {
                // if ptr is deleted.
                out << dealer << ": D-E-L-E-T-E-D" << std::endl;
            }
        }
        out << name << " end of list" << std::endl;
    }
    void remove(std::shared_ptr<Car> car) { listing.erase(car); }

private:
    std::map<std::weak_ptr<Car>, std::string, std::owner_less<std::weak_ptr<Car>>> listing; // This is cancer...
    std::string name;
};

class Dealer {
	friend std::ostream &operator<<(std::ostream &out, const Dealer &dealer);
public:
	explicit Dealer(std::string name_ = "John Doe") : name(std::move(name_)) {};
	~Dealer() { std::cout << name << " deleted" << std::endl; };
	void buy();
	void sell();
	void add(std::shared_ptr<Car> car) {
        cars.push_back(car);
        for (auto site : sites) site->add(car, name);
    }
	void add_site(std::shared_ptr<Website> w) {
        sites.push_back(w);
    }
private:
	std::string name;
	std::vector<std::shared_ptr<Car>> cars;
	std::vector<std::shared_ptr<Website>> sites;
};

void Dealer::buy()
{
    std::shared_ptr<Car> car = std::make_shared<Car>();
    car->Read();
    add(car);
}

void Dealer::sell()
{
    std::cout << *this; // print my list of cars
    std::cout << "Enter license of car you want to buy: " << std::flush;

    std::string license;
    std::cin >> license;
    
    auto ci = std::find_if(cars.begin(), cars.end(), [license](const auto& c) {return license == c->GetLicense();}); // Why is cpp like this?


    if (ci != cars.end()) {
        // modify code so that you don't need to remove a sold car from the website
        //for (auto site : sites) site->remove(*ci);
		ci->reset();
        cars.erase(ci); // Do I still call this?
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
	// who names their variables like this??
	std::cout << "Car sales started" << std::endl;
	auto wa = std::make_shared<Website>("www.autos.com");
	auto wb = std::make_shared<Website>("www.bilar.com");
	auto a = std::make_shared<Dealer>("Alan Aldis");
	auto b = std::make_shared<Dealer>("Bill Munny");
	{ // inner scope to make some if the pointers go out of scope before the function ends.
        auto wc = std::make_shared<Website>("www.cars.com");
		auto c = std::make_shared<Dealer>("Casey Ball");
		auto ca = std::make_shared<Car>();
		auto cb = std::make_shared<Car>();

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

int main(int argc, char **argv) {  // <<<--- The hell are these??!?
  
	srand(time(nullptr));

	car_sales();

	return 0;
}


