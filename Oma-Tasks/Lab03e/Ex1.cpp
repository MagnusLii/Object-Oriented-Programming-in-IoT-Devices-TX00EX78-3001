#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <limits>

int main()
{
    std::map<std::string, int> myMap;
    std::string name;
    int num;

    while (true)
    {
        std::cout << "Enter name or \"stop\" or \"print\": ";
        std::cin >> name;

        if (name == "stop")
        {
            break;
        }
        else if (name == "print")
        {
            for (const auto &pair : myMap)
            {
                std::cout << pair.first << " : " << pair.second << std::endl;
            }
        }
        else
        {
            std::cout << "Enter integer: ";
            while (!(std::cin >> num))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a number: ";
            }
            myMap[name] = num;
        }
    }

    return 0;
}
