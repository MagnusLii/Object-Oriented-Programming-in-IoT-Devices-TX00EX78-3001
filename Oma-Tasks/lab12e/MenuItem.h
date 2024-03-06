//
// Created by Keijo Länsikunnas on 5.3.2024.
//

#ifndef LAB12_MENUITEM_H
#define LAB12_MENUITEM_H

#include <string>

class MenuItem {
public:
    enum menuEvent {
        up,
        down,
        ok,
        back
    };
    MenuItem(std::string menu_title);
    virtual const std::string &title() const;
    virtual bool event(menuEvent e) = 0;
    virtual void show() = 0;
    virtual ~MenuItem() = default;
protected:
    std::string menu_title;
};

#endif //LAB12_MENUITEM_H
