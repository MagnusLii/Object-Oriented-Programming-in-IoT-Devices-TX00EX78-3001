#include <iostream>
#include <string>

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

class Spy : public Person {
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

	void interrogate() override {resistance--;}

private:
	std::string alias;
	int resistance;
};

int main(int argc, char** argv) {
	Person agent("James Bond");
	Spy spy("Emilio Largo", "William Johnson", 3);
	Spy spy2("Ernst Blofield", "John Keats", 5);

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