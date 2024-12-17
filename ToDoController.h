#pragma once
#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include "ToDoModel.h"
#include "ToDoView.h"

//std::vector<std::string> Task::m_all_category = std::vector<std::string>({"#"});
class ToDoController {
public:
    ToDoController(ToDoModel& model, ToDoView& view);

    void run();

    void filterMenu();
    void filterPriority();
    void filterStatus();
    void filterСategory();
    void filterDate();

    void viewFilterPriority();
    void viewFilterStatus();
    void viewFilterCategory();
    void viewFilterDate();

    void exportTask();
    void importTask();
private:
    ToDoModel& model;
    ToDoView& view;

    int getUserChoice() const;

    void addTask();

    void removeTask();

    void markTaskCompleted();

    void showAllTasks();

    void saveSettings(std::vector<std::string>& AllParametrs);

    std::tm checkDate(std::string date_str);

    void isValid(int day, int month, int year, int hour, int min) const;
};
