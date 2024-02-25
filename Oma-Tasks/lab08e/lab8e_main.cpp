#include <iostream>

class Counter {
public:
	virtual void inc() = 0;
	virtual void dec() = 0;
	virtual operator int() = 0;
	virtual ~Counter() {};
};

class LimitedCounter : public Counter {
private:
	int value;
	int upperLimit;

public:
	// The constructor takes two parameters: initial value and upper limit.
	LimitedCounter(int initialValue, int upperLimit) : value(initialValue), upperLimit(upperLimit) {}

	// Counter can’t be incremented over the upper limit. If inc() is called when counter has
 	// reached the upper limit nothing happens
	void inc() override {
		if (value < upperLimit) {
			value++;
		}
	}

	// Counter can’t be decremented below zero. If counter is zero then calling dec() will
	// have no eFect
	void dec() override {
		if (value > 0) {
			value--;
		}
	}

	operator int() override {
		return value;
	}
};

class OverflowCounter : public Counter {
private:
	int value;
	int upperLimit;

public:
	// The constructor takes two parameters: initial value and upper limit
	OverflowCounter(int initialValue, int limit) : value(initialValue), upperLimit(limit) {}

	// When counter has reached the upper limit incrementing the value will set the counter
	// to zero.
	void inc() override {
		if (value == upperLimit) {
			value = 0;
		}
		else {
			value++;
		}
	}

	// When counter is zero decrementing the counter sets counter to upper limit.
	void dec() override {
		if (value == 0) {
			value = upperLimit;
		}
		else {
			value--;
		}
	}

	operator int() override {
		return value;
	}
};

/*Function takes two parameters: a reference to Counter and number that tells how
many times the counter should be incremented or decremented. A negative value
decrements counter and positive value increments counter.*/
void UseCounter(Counter& ctr, int num) {
	if (num > 0) {
		for (int i = 0; i < num; i++) {
			ctr.inc();
		}
	}
	else {
		for (int i = 0; i < -num; i++) {
			ctr.dec();
		}
	}
}

int main(int argc, char** argv) {
	LimitedCounter lc(0, 5);
	OverflowCounter oc(5, 9);

	std::cout << oc << std::endl;
	UseCounter(oc, 5);
	std::cout << oc << std::endl; // should display zero
	UseCounter(oc, -1);
	std::cout << oc << std::endl; // should display 9
	oc.dec();
	std::cout << oc << std::endl; // should display 8

	std::cout << lc << std::endl;
	lc.inc();
	std::cout << lc << std::endl;
	lc.dec();
	std::cout << lc << std::endl;
	for(int i = 0; i < 10; ++i) lc.inc();
	std::cout << lc << std::endl;
	UseCounter(lc, -9);
	std::cout << lc << std::endl;

	return 0;
}
