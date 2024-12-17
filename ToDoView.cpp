#include "ToDoView.h"
#include <iostream>
#include <Windows.h>

void ToDoView::displayMenu() const {
    std::cout << "1. �������� ������" << std::endl;
    std::cout << "2. ������� ������" << std::endl;
    std::cout << "3. �������� ������ ��� �����������" << std::endl;
    std::cout << "4. �������� ��� ������" << std::endl;
    std::cout << "5. ��������� ������" << std::endl;
    std::cout << "6. ������� ����� � ������� CSV" << std::endl;
    std::cout << "7. ������ ����� � ������� CSV" << std::endl;
    std::cout << "8. �����" << std::endl;
}

void ToDoView::displayMenuFilter() const {
    std::cout << "1. ������ �� �����������" << std::endl;
    std::cout << "2. ������ �� ������� ������" << std::endl;
    std::cout << "3. ������ �� ���������" << std::endl;
    std::cout << "4. ������ �� ����" << std::endl;
    std::cout << "5. �������� �������" << std::endl;
    std::cout << "6. �����" << std::endl;
};


void ToDoView::displayMenuFilterPriority() const {
    std::cout << "1. ������������� �� ����������� �����������" << std::endl;
    std::cout << "2. ������������� �� �������� �����������" << std::endl;
    std::cout << "3. �������� ������ �� ������������ ���������" << std::endl;
    std::cout << "4. ������� �������� ��������" << std::endl;
    std::cout << "5. �������� ��������� �������" << std::endl;
    std::cout << "6. �����" << std::endl;
};
void ToDoView::displayMenuFilterStatus() const {
    std::cout << "1. ��������� ������� �� ���������� �������" << std::endl;
    std::cout << "2. ��������� ������� �� �� ���������� �������" << std::endl;
    std::cout << "3. �������� ��������� �������" << std::endl;
    std::cout << "4. �����" << std::endl;
};
void ToDoView::displayMenuFilterCategory() const {
    std::cout << "1. �������� � ������� ���������" << std::endl;
    std::cout << "2. �������� ��������� �������" << std::endl;
    std::cout << "3. �����" << std::endl;
};
void ToDoView::displayMenuFilterDate() const {
    std::cout << "1. ��������� ������ �� ����� ��������� ������ " << std::endl;
    std::cout << "2. ��������� ������ �� ����� ������� ������ " << std::endl;
    std::cout << "3. ������� �������� ��������" << std::endl;
    std::cout << "4. �������� ��������� �������" << std::endl;
    std::cout << "5. �����" << std::endl;
};



void ToDoView::displayTasks(const std::vector<Task>& tasks) const {
    for (const Task& task : tasks) {
        std::cout << "������: " << task.getTitle() << std::endl;
        std::cout << "��������: " << task.getDescription() << std::endl;
        std::cout << "���������: " << task.getCategory() << std::endl;
        std::cout << "���������: " << task.getPriority() << std::endl;
        std::cout << "���� ����������: " << task.getDueDate() << std::endl;
        std::cout << "������: " << (task.isCompleted() ? "���������" : "�� ���������") << std::endl;
        std::cout << "----------------------------------------" << std::endl;
    }
}

void ToDoView::displayMessage(const std::string& message) const {
    std::cout << message << std::endl;
}


