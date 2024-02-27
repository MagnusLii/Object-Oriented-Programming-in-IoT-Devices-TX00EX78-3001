#include <iostream>
#include <string>
#include <vector>

class Person {
public:
	Person(const char* name = "nobody") : name(name) {}
	virtual ~Person() = default;
	virtual void identity() const {
		std::cout << "My name is " << name << std::endl;
	}
	virtual void interrogate() {}
private:
	std::string name;
};

class Observer;
class Subject {
public:
	virtual void Attach(Observer *o) = 0; // Set
	virtual void Notify() = 0;
};
// Abstract interface of Observer
class Observer {
public:
	virtual void Update() = 0;
};

class Spy : public Person, public Subject {
public:
	Spy(const char* name, const char* alias, int resistance)
		: Person(name), alias(alias), resistance(resistance) {}

	void set_identity(const char* Alias) {alias = Alias;}

	void identity() const override {
		if (resistance > 0) {
			std::cout << "My name is " << alias << std::endl;
		} else {
			Person::identity();
			std::cout << "My alias is " << alias << std::endl;
		}
	}

	void Attach(Observer *observer) override {
		observers.push_back(observer);
	}
	void Notify() override {
		for (auto observer : observers) {
			observer->Update();
		}
	}
		

	void interrogate() override {
		resistance--;
		if (resistance <= 0) {
			Notify();
		}
	}


private:
	std::vector<Observer*> observers;
	std::string alias;
	int resistance;
};

class Judge : public Person, public Observer {
	public:
	Judge(const char* name) : Person(name) {}
	void Update() override {
		std::cout << "[";
		Person::identity();
		std::cout << "I'm sending a spy to prison!]" << std::endl;
	}
};

int main(int argc, char** argv) {
	Person agent("James Bond");
	Spy spy("Emilio Largo", "William Johnson", 3);
	Spy spy2("Ernst Blofield", "John Keats", 5);
	Judge judge("Judge Barnhill");
	spy.Attach(&judge);
	spy2.Attach(&judge);

	std::cout << std::endl << "Nice to meet you. ";
	agent.identity();

	for (int i = 0; i < 6; ++i) {
		std::cout << "Who are you?" << std::endl;
		spy.interrogate();
		spy.identity();
	}
	spy.set_identity("Bill Munny");
	spy.identity();

	std::cout << std::endl << "Nice to meet you. ";
	agent.identity();

	for (int i = 0; i < 6; ++i) {
		std::cout << "Who are you?" << std::endl;
		spy2.interrogate();
		spy2.identity();
	}

	return 0;
}