#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Task {
public:
    static vector<pair<string,int>> m_all_category;

    Task(const std::string& title, const std::string& description, const std::string& category, int priority, const std::time_t dueDate_sec);
    Task(const std::string& title, const std::string& description, const std::string& category, int priority, const std::time_t dueDate_sec, bool iscomplete);
    std::string getTitle() const;
    std::string getDescription() const;
    std::string getCategory() const;
    int getPriority() const;
    std::string getDueDate() const;
    bool isCompleted() const;
    time_t getDueDateSec() const;

    static vector<pair<string,int>> getAllcategori() { return m_all_category;  };
    static void setAllcategori(vector<pair<string, int>> allcategory) { m_all_category = allcategory; };

    void markCompleted();
    void markUncompleted();


private:
    std::string m_title;
    std::string m_description;
    std::string m_category;
    int m_priority;
    std::time_t m_dueDate_sec;
    bool m_completed;
};
