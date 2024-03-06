//
// Created by Keijo Länsikunnas on 5.3.2024.
//

#include "Menu.h"

#include <iostream>

Menu::Menu(std::string menu_title) : MenuItem(menu_title) , position(0), selection(-1) {
}

bool Menu::event(MenuItem::menuEvent e) {
    bool handled = true;
    if(items.empty()) return false;

    if(selection < 0) {
        switch(e) {
            case MenuItem::up:
                ++position;
                if(position > items.size() - 1) position = items.size() - 1; ;
                show();
                break;
            case MenuItem::down:
                --position;
                if(position < 0) position = 0;
                show();
                break;
            case MenuItem::ok:
                selection = position;
                items[selection]->show();
                break;
            case MenuItem::back:
                handled = false;
                break;
        }
    }
    else if(!items[selection]->event(e)) {
        selection = -1;
        show();
    }

    return handled;
}


void Menu::show() {
    int index = 0;
    std::cout << "===" << menu_title << "===" << std::endl;
    for(auto &item : items) {
        std::cout << (index == position ? "-->" : "   ");
        std::cout << item->title() << std::endl;
        ++index;
    }
    for(int i = 0; i < menu_title.length() + 6; ++i) std::cout << '=';
    std::cout << std::endl;
}

void Menu::add_item(std::shared_ptr<MenuItem> item) {
    items.push_back(std::move(item));
}

