#include "ToDoView.h"
#include <iostream>
#include <Windows.h>

void ToDoView::displayMenu() const {
    std::cout << "1. Добавить задачу" << std::endl;
    std::cout << "2. Удалить задачу" << std::endl;
    std::cout << "3. Отметить задачу как выполненную" << std::endl;
    std::cout << "4. Показать все задачи" << std::endl;
    std::cout << "5. Настроить фильтр" << std::endl;
    std::cout << "6. Экспорт задач в формате CSV" << std::endl;
    std::cout << "7. Импорт задач в формате CSV" << std::endl;
    std::cout << "8. Выход" << std::endl;
}

void ToDoView::displayMenuFilter() const {
    std::cout << "1. Фильтр по приоритетам" << std::endl;
    std::cout << "2. Фильтр по статусу задачи" << std::endl;
    std::cout << "3. Фильтр по категории" << std::endl;
    std::cout << "4. Фильтр по дате" << std::endl;
    std::cout << "5. Очистить фильтры" << std::endl;
    std::cout << "6. назад" << std::endl;
};


void ToDoView::displayMenuFilterPriority() const {
    std::cout << "1. Отфильтровать по возрастанию приоритетов" << std::endl;
    std::cout << "2. Отфильтровать по убыванию приоритетов" << std::endl;
    std::cout << "3. Добавить фильтр на определенный приоритет" << std::endl;
    std::cout << "4. Сделать основным фильтром" << std::endl;
    std::cout << "5. Очистить настройки фильтра" << std::endl;
    std::cout << "6. назад" << std::endl;
};
void ToDoView::displayMenuFilterStatus() const {
    std::cout << "1. Поставить фильтор на выполненые задания" << std::endl;
    std::cout << "2. Поставить фильтор на не выполненые задания" << std::endl;
    std::cout << "3. Очистить настройки фильтра" << std::endl;
    std::cout << "4. назад" << std::endl;
};
void ToDoView::displayMenuFilterCategory() const {
    std::cout << "1. Добавить в фильтер категорию" << std::endl;
    std::cout << "2. Очистить настройки фильтра" << std::endl;
    std::cout << "3. назад" << std::endl;
};
void ToDoView::displayMenuFilterDate() const {
    std::cout << "1. Поставить фильтр на самые ближайжие задачи " << std::endl;
    std::cout << "2. Поставить фильтр на самые далекие задачи " << std::endl;
    std::cout << "3. Сделать основным фильтром" << std::endl;
    std::cout << "4. Очистить настройки фильтра" << std::endl;
    std::cout << "5. назад" << std::endl;
};



void ToDoView::displayTasks(const std::vector<Task>& tasks) const {
    for (const Task& task : tasks) {
        std::cout << "Задача: " << task.getTitle() << std::endl;
        std::cout << "Описание: " << task.getDescription() << std::endl;
        std::cout << "Категория: " << task.getCategory() << std::endl;
        std::cout << "Приоритет: " << task.getPriority() << std::endl;
        std::cout << "Срок выполнения: " << task.getDueDate() << std::endl;
        std::cout << "Статус: " << (task.isCompleted() ? "Выполнено" : "Не выполнено") << std::endl;
        std::cout << "----------------------------------------" << std::endl;
    }
}

void ToDoView::displayMessage(const std::string& message) const {
    std::cout << message << std::endl;
}


