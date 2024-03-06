//
// Created by Keijo Länsikunnas on 5.3.2024.
//

#include "MenuItem.h"

MenuItem::MenuItem(std::string menu_title) : menu_title(menu_title) {

}

const std::string &MenuItem::title() const {
    return menu_title;
}
