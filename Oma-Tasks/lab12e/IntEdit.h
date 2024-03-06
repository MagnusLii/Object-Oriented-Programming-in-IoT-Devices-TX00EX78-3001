//
// Created by Keijo Länsikunnas on 5.3.2024.
//

#ifndef LAB12_INTEDIT_H
#define LAB12_INTEDIT_H
#include <string>
#include "MenuItem.h"
#include <set>

class IntEdit : public MenuItem {
public:
    explicit IntEdit(std::string menu_title);
    bool event(menuEvent e) override;
    void show() override;
protected:
    int value;
    int backup;
    bool changed;
};

class Observer {
public:
    virtual void notify(int value) = 0;
    virtual ~Observer() = default;
};

class ObservableIntEdit;

class ObservableIntEditObserver : public Observer {
public:
    ObservableIntEditObserver(ObservableIntEdit* observableIntEdit);
    void notify(int value) override;

private:
    ObservableIntEdit* observableIntEdit;
};

class ObservableIntEdit : public IntEdit {
public:
    explicit ObservableIntEdit(std::string menu_title);
    bool event(menuEvent e) override;
    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
    void notifyObservers();

private:
    std::set<Observer*> observers;
};


#endif //LAB12_INTEDIT_H
