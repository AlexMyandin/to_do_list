#pragma once
#include <iostream>
#include <vector>
#include "Task.h"
class ToDoView {
public:
    void displayMenu() const;

    void displayMenuFilter() const;

    void displayMenuFilterPriority() const;
    void displayMenuFilterStatus() const;
    void displayMenuFilterCategory() const;
    void displayMenuFilterDate() const;


    void displayTasks(const std::vector<Task>& tasks) const;

    void displayMessage(const std::string& message) const;


};
