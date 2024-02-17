# Inheritance
Implement Person class as defined below. The class simply holds a person’s name and
prints it when needed.<br><br>
```cpp
class Person {
public:
Person(const char *name = "nobody");
virtual ~Person() = default;
virtual void identity() const;
virtual void interrogate();
private:
std::string name;
};
```

Identity() prints the name of the person.<br>
Interrogate() does nothing (empty body) in class Person.<br><br>

Derive a Spy class from Person and add member function that can be used to set an alias
for the spy.<br>
```cpp
void set_identity(const char *alias);
```
**Spy constructor must take three parameters:** name of the spy, alias of the spy, and
resistance. Resistance is an integer that represents spy’s resistance to interrogation. Every
time interrogate() is called resistance is decremented by one. When resistance is greater
than zero identity() prints alias of the spy instead of the real name. When resistance is zero
identity() prints both the real name and the alias of the spy.<br><br>

Set_identity sets the spy’s alias.<br>

Note that you must override indentity() and interrogate() in class Spy.<br><br>

The real name of the spy is inherited from the Person class. Spy adds a private member to
hold the alias that spy uses until resistance runs out.<br><br>

Use the following program to test your classes.
```cpp
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
```
```
Example output:
Nice to meet you. My name is: James Bond
Who are you?
My name is: William Johnson
Who are you?
My name is: William Johnson
Who are you?
My name is: Emilio Largo
My alias is: William Johnson
Who are you?
My name is: Emilio Largo
My alias is: William Johnson
Who are you?
My name is: Emilio Largo
My alias is: William Johnson
Who are you?
My name is: Emilio Largo
My alias is: William Johnson
My name is: Emilio Largo
My alias is: Bill Munny
Nice to meet you. My name is: James Bond
Who are you?
My name is: John Keats
Who are you?
My name is: John Keats
Who are you?
My name is: John Keats
Who are you?
My name is: John Keats
Who are you?
My name is: Ernst Blofield
My alias is: John Keats
Who are you?
My name is: Ernst Blofield
My alias is: John Keats
```