# Operator overloading
Implement class House for storing housing informa3on.<br><br>
The class must use std::string for storing the address of the house, a double for the size (area in m2)
of the house and an int for the price of the house in euros. All data member must be private.<br><br>
Class must define a constructor that takes the house informa3on as parameters and there must be
default constructor.<br><br>
The class must have the following operators:
- Output operator for prin3ng the housing informa3on with minimal formaDng. No newlines
may be printed by the operator.
- Input operator for reading the housing informa3on from a stream. The operator must accept
the format produced by the output operator. The address of the house may contain spaces
so the operator must be able to read an address with spaces in it.
- Less than operator that compares two houses by price/m2

Class must define the following member func3ons:
- setAddress for seDng the address of the house
- setArea for seDng the area of the house
- setPrice for seDng the price of the house

Write a program that defines a vector of House.<br><br>
The program asks user to enter informa3on of five houses and stores them in the vector. The houses
must be asked in the following ways:
- Ask user to enter the house informa3on (address, area, price) and use constructor to create
a house by passing the informa3on as parameters
- Create a house using default constructor, ask user to enter the house informa3on and use
seJer func3ons before adding the house to the vector
- Create house using default constructor and read values using the input operator

You can decide the mix between the five houses but at least one house must be asked using each of
the above ways.<br><br>
Then sort the vector using std::sort and print the house informa3on one house per line.<br><br>
Notes:<br>
To read a string from a stream using other that default delimiter (white space) you can use
std::getline. It has overload that takes three parameters: stream to read from, reference to a string,
and delimi3ng character. For example:
std::getline(std::cin, my_str, ':');