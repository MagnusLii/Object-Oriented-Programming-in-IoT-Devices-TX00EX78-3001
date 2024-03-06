//
// Created by Keijo Länsikunnas on 5.3.2024.
//

#include "IntEdit.h"
#include <iostream>

IntEdit::IntEdit(std::string menu_title) :
        MenuItem(menu_title), value(0), backup(0), changed(false) {
}

bool IntEdit::event(MenuItem::menuEvent e) {
    bool handled = true;
    switch (e) {
        case MenuItem::up:
            if (!changed) {
                changed = true;
                backup = value;
            }
            ++value;
            show();
            break;
        case MenuItem::down:
            if (!changed) {
                changed = true;
                backup = value;
            }
            --value;
            show();
            break;
        case MenuItem::ok:
            if (changed) {
                changed = false;
                backup = value;
                // notify?
            }
            break;
        case MenuItem::back:
            if (changed) {
                changed = false;
                value = backup;
                show();
            } else {
                handled = false;
            }
            break;
    }

    return handled;

}

void IntEdit::show() {
    std::cout << "[" << menu_title << "]" << std::endl;
    std::cout << "Value: " << value << std::endl;
}

ObservableIntEditObserver::ObservableIntEditObserver(ObservableIntEdit* observableIntEdit)
    : observableIntEdit(observableIntEdit) {}

void ObservableIntEditObserver::notify(int value) {
    std::cout << "Observer notified of change in " << observableIntEdit->title() << ": " << value << std::endl;
}

ObservableIntEdit::ObservableIntEdit(std::string menu_title) : IntEdit(menu_title) {}

bool ObservableIntEdit::event(MenuItem::menuEvent e) {
    bool handled = IntEdit::event(e);
    if (handled) {
        notifyObservers();
    }
    return handled;
}

void ObservableIntEdit::addObserver(Observer* observer) {
    observers.insert(observer);
}

void ObservableIntEdit::removeObserver(Observer* observer) {
    observers.erase(observer);
}

void ObservableIntEdit::notifyObservers() {
    for (auto observer : observers) {
        observer->notify(value);
    }
}