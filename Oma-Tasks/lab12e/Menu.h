//
// Created by Keijo Länsikunnas on 5.3.2024.
//

#ifndef LAB12_MENU_H
#define LAB12_MENU_H
#include <vector>
#include <string>
#include <memory>
#include "MenuItem.h"

class Menu : public MenuItem {
public:
    explicit Menu(std::string menu_title);
    bool event(menuEvent e) override;
    void show() override;
    void add_item(std::shared_ptr<MenuItem> item);
private:
    std::vector<std::shared_ptr<MenuItem>> items;
    int position;
    int selection;
};


#endif //LAB12_MENU_H
