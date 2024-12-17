#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "Task.h"

class ToDoModel {
public:

    string trim(const std::string& str);

    string reverse(string str);

    void addTask(const Task& task);

    string removeTask(const std::string& title);
    void markTaskCompleted(const std::string& title);

    std::vector<Task> getAllTasks();

    vector<string> getSettingsFilter();
    void saveSettings(std::vector<std::string>& AllParametrs);

    void exportTask(string path);
    void importTask(string path);



private:
    std::vector<Task> tasks;
};
