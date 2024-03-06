#include <cstdlib>

#include <iostream>
#include "Menu.h"
#include "IntEdit.h"

int main(int argc, char** argv) {

    auto sub_menu = std::make_shared<Menu>("Colors");

    auto redEdit = std::make_shared<IntEditObserver>("Red");
    auto blueEdit = std::make_shared<IntEditObserver>("Blue");
    auto greenEdit = std::make_shared<IntEditObserver>("Green");

    auto observer = std::make_shared<ObserverNotifier>(redEdit.get());
    redEdit->addObserver(observer.get());
    blueEdit->addObserver(observer.get());
    greenEdit->addObserver(observer.get());

    sub_menu->add_item(redEdit);
    sub_menu->add_item(blueEdit);
    sub_menu->add_item(greenEdit);

    auto main_menu = std::make_shared<Menu>("Main menu");
    main_menu->add_item(std::make_shared<IntEdit>("Speed"));
    main_menu->add_item(std::make_shared<IntEdit>("Target"));
    main_menu->add_item(std::make_shared<IntEdit>("Sound"));
    main_menu->add_item(sub_menu);

    main_menu->show();

    std::string s;
    do {
        std::cin >> s;
        if (s[0] == '+') main_menu->event(MenuItem::up);
        if (s[0] == '-') main_menu->event(MenuItem::down);
        if (s[0] == '<') main_menu->event(MenuItem::back);
        if (s[0] == 'o') main_menu->event(MenuItem::ok);
    } while (s[0] != 'q');

    return 0;
}
