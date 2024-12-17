#include "Task.h"

using namespace std;
Task::Task(const std::string& title, const std::string& description, const std::string& category, int priority, const std::time_t dueDate_sec)
    : m_title(title), m_description(description), m_category(category), m_priority(priority), m_dueDate_sec(dueDate_sec), m_completed(false) {}

Task::Task(const std::string& title, const std::string& description, const std::string& category, int priority, const std::time_t dueDate_sec, bool iscomplete)
    : m_title(title), m_description(description), m_category(category), m_priority(priority), m_dueDate_sec(dueDate_sec), m_completed(iscomplete) {};
std::string Task::getTitle() const { return m_title; }
std::string Task::getDescription() const { return m_description; }
std::string Task::getCategory() const { return m_category; }
int Task::getPriority() const { return m_priority; }
std::string Task::getDueDate() const { 
    tm ltm = {};
    localtime_s(&ltm, &m_dueDate_sec);
    string datee = to_string(ltm.tm_mday) + "."
        + to_string(ltm.tm_mon) + "." + 
        to_string(ltm.tm_year+1900) + " " +
        to_string(ltm.tm_hour) + ":" + to_string(ltm.tm_min);
    // print various components of tm structure.
    //std::cout << "Year" << 1900 + ltm.tm_year << std::endl;
    //std::cout << "Month: " << 1 + ltm.tm_mon << std::endl;
    //std::cout << "Day: " << ltm.tm_mday << std::endl;
    //std::cout << "Time: " << ltm.tm_hour << ":";
    //std::cout << ltm.tm_min << ":";
    //std::cout << ltm.tm_sec << std::endl;
    return datee; 
}

time_t Task::getDueDateSec() const {
    return m_dueDate_sec;
};
bool Task::isCompleted() const { return m_completed; }

void Task::markCompleted() { m_completed = true; }
void Task::markUncompleted() { m_completed = false; }

