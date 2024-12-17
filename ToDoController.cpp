#include "ToDoController.h"

using namespace std;




ToDoController::ToDoController(ToDoModel& model, ToDoView& view) : model(model), view(view) {}

void ToDoController::run() {
    while (true) {
        view.displayMenu();
        int choice = getUserChoice();

        switch (choice) {
        case 1:
            addTask();
            break;
        case 2:
            removeTask();
            break;
        case 3:
            markTaskCompleted();
            break;
        case 4:
            showAllTasks();
            break;
        case 5:
            filterMenu();
            break;
        case 6: {
            exportTask();
            break;
        }
        case 7:{
            importTask();
            break;
        }
        case 8:
            return;
        default:
            view.displayMessage("Неверный выбор. Попробуйте снова.");
        }
    }
}



void ToDoController::filterMenu() {
    while (true) {
        view.displayMessage("Настройки фильтра:");
        viewFilterPriority();
        viewFilterStatus();
        viewFilterCategory();
        viewFilterDate();
        view.displayMenuFilter();
        int choice = getUserChoice();

        switch (choice) {
        case 1:
            filterPriority();
            break;
        case 2:
            filterStatus();
            break;
        case 3:
            filterСategory();
            break;
        case 4:
            filterDate();
            break;
        case 5: {
            std::ofstream outFile("settingsFiltr.txt");

            // Проверяем, успешно ли открыт файл
            if (!outFile.is_open()) {
                std::cerr << "Ошибка открытия файла для записи!" << std::endl;
                throw "Ошибка открытия файла";
            }

            // Записываем данные в файл
            outFile << "increasePriority=#" << endl;
            outFile << "definedPriorities=#" << endl;
            outFile << "completedTasks=#" << endl;
            outFile << "category=#" << endl;
            outFile << "upcomingTasks=#" << endl;
            outFile << "filter_by_date_or_priority=1" << endl;
            // Закрываем файл
            outFile.close();

            break;
        }
        case 6:
            return;
        default:
            view.displayMessage("Неверный выбор. Попробуйте снова.");
        }
    }
};

void ToDoController::filterPriority() {

    while (true) {
        view.displayMessage("Настройки фильтра:");
        viewFilterPriority();
        view.displayMenuFilterPriority();
        int choice = getUserChoice();

        switch (choice) {
        case 1: {
            vector<string> AllParametrs = model.getSettingsFilter();
            for (size_t i = 0; i < AllParametrs.size(); i++)
            {
                string nameParametr;
                string line = AllParametrs[i];
                for (size_t k = 0; k < line.size(); k++)
                {
                    if (line[k] == '=') { break; }
                    nameParametr += line[k];
                }
                if (nameParametr == "increasePriority") {
                    for (size_t k = line.size() - 1; k != -1; k--)
                    {
                        if (line[k] == '=') { break; }
                        line.pop_back();
                    }
                    AllParametrs[i] = line + '1';
                    break;
                }
            }
            saveSettings(AllParametrs);
            break;
        }
        case 2: {
            vector<string> AllParametrs = model.getSettingsFilter();
            for (size_t i = 0; i < AllParametrs.size(); i++)
            {
                string nameParametr;
                string line = AllParametrs[i];
                for (size_t k = 0; k < line.size(); k++)
                {
                    if (line[k] == '=') { break; }
                    nameParametr += line[k];
                }
                if (nameParametr == "increasePriority") {
                    for (size_t k = line.size() - 1; k != -1; k--)
                    {
                        if (line[k] == '=') { break; }
                        line.pop_back();
                    }
                    AllParametrs[i] = line + "0";
                    break;
                }
            }
            saveSettings(AllParametrs);
            break;
        }
        case 3: {
            int priority;
            std::cout << "Какой приоритет добавить?: ";
            std::cin >> priority;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            vector<string> AllParametrs = model.getSettingsFilter();
            for (size_t i = 0; i < AllParametrs.size(); i++)
            {
                string nameParametr;
                string line = AllParametrs[i];
                for (size_t k = 0; k < line.size(); k++)
                {
                    if (line[k] == '=') { break; }
                    nameParametr += line[k];
                }
                if (nameParametr == "definedPriorities") {
                    if (line[line.size() - 1] == '#') {
                        line.pop_back();
                        AllParametrs[i] = line + to_string(priority);
                        saveSettings(AllParametrs);
                    }
                    else
                    {
                        vector<int> priorityAll;
                        string priorityTemp;
                        for (size_t k = line.size() - 1; k != -1; k--)
                        {
                            if (line[k] == '=') { priorityAll.push_back(stoi(model.reverse(priorityTemp))); break; }
                            if (line[k] == ',') { 
                                priorityAll.push_back(stoi(model.reverse(priorityTemp)));
                                priorityTemp = "";
                                continue; 
                            }
                            priorityTemp += line[k];
                        }
                        bool flag = true;
                        for (size_t k = 0; k < priorityAll.size(); k++)
                        {
                            if (priorityAll[k] == priority) { flag = false; break; }
                        }
                        if (flag) {
                            AllParametrs[i] = line + ',' + to_string(priority);
                            saveSettings(AllParametrs);
                        }
                        else { cout << "\nТакой приоритет уже есть в фильтре.\n"; }
                        break;
                    }
                    
                    break;
                }
            }
            break;
        }
        case 4: {
            vector<string> AllParametrs = model.getSettingsFilter();
            for (size_t i = 0; i < AllParametrs.size(); i++)
            {
                string nameParametr;
                string line = AllParametrs[i];
                for (size_t k = 0; k < line.size(); k++)
                {
                    if (line[k] == '=') { break; }
                    nameParametr += line[k];
                }
                if (nameParametr == "filter_by_date_or_priority") {
                    for (size_t k = line.size() - 1; k != -1; k--)
                    {
                        if (line[k] == '=') { break; }
                        line.pop_back();
                    }
                    AllParametrs[i] = line + '1';
                    break;
                }
            }
            saveSettings(AllParametrs);
            break;
        }
        case 5: {
            vector<string> AllParametrs = model.getSettingsFilter();
            for (size_t i = 0; i < AllParametrs.size(); i++)
            {
                string nameParametr;
                string line = AllParametrs[i];
                for (size_t k = 0; k < line.size(); k++)
                {
                    if (line[k] == '=') { break; }
                    nameParametr += line[k];
                }
                if (nameParametr == "increasePriority") {
                    for (size_t k = line.size() - 1; k != -1; k--)
                    {
                        if (line[k] == '=') { break; }
                        line.pop_back();
                    }
                    AllParametrs[i] = line + "#";
                }
                if (nameParametr == "definedPriorities") {
                    for (size_t k = line.size() - 1; k != -1; k--)
                    {
                        if (line[k] == '=') { break; }
                        line.pop_back();
                    }
                    AllParametrs[i] = line + "#";
                    
                }
            }
            saveSettings(AllParametrs);
            break;
        }
        case 6:
            return;
        default:
            view.displayMessage("Неверный выбор. Попробуйте снова.");
        }
    }
};

void ToDoController::filterStatus() {
    while (true) {
        view.displayMessage("Настройки фильтра:");
        viewFilterStatus();
        view.displayMenuFilterStatus();
        int choice = getUserChoice();

        switch (choice) {
        case 1: {
            vector<string> AllParametrs = model.getSettingsFilter();
            for (size_t i = 0; i < AllParametrs.size(); i++)
            {
                string nameParametr;
                string line = AllParametrs[i];
                for (size_t k = 0; k < line.size(); k++)
                {
                    if (line[k] == '=') { break; }
                    nameParametr += line[k];
                }
                if (nameParametr == "completedTasks") {
                    for (size_t k = line.size() - 1; k != -1; k--)
                    {
                        if (line[k] == '=') { break; }
                        line.pop_back();
                    }
                    AllParametrs[i] = line + '1';
                    
                    break;
                }
            }
            saveSettings(AllParametrs);
            break;
        }
        case 2: {
            vector<string> AllParametrs = model.getSettingsFilter();
            for (size_t i = 0; i < AllParametrs.size(); i++)
            {
                string nameParametr;
                string line = AllParametrs[i];
                for (size_t k = 0; k < line.size(); k++)
                {
                    if (line[k] == '=') { break; }
                    nameParametr += line[k];
                }
                if (nameParametr == "completedTasks") {
                    for (size_t k = line.size() - 1; k != -1; k--)
                    {
                        if (line[k] == '=') { break; }
                        line.pop_back();
                    }
                    AllParametrs[i] = line + '0';
                    
                    break;
                }
            }
            saveSettings(AllParametrs);
            break;
        }
        case 3: {
            vector<string> AllParametrs = model.getSettingsFilter();
            for (size_t i = 0; i < AllParametrs.size(); i++)
            {
                string nameParametr;
                string line = AllParametrs[i];
                for (size_t k = 0; k < line.size(); k++)
                {
                    if (line[k] == '=') { break; }
                    nameParametr += line[k];
                }
                if (nameParametr == "completedTasks") {
                    for (size_t k = line.size() - 1; k != -1; k--)
                    {
                        if (line[k] == '=') { break; }
                        line.pop_back();
                    }
                    AllParametrs[i] = line + '#';
                    
                    break;
                }
            }
            saveSettings(AllParametrs);
            break;
        }
        case 4:
            return;
        default:
            view.displayMessage("Неверный выбор. Попробуйте снова.");
        }
    }
};

void ToDoController::filterСategory() {
    while (true) {
        view.displayMessage("Настройки фильтра:");
        viewFilterCategory();
        view.displayMenuFilterCategory();
        int choice = getUserChoice();

        switch (choice) {
        case 1: {
            string category;
            bool flag = true;
            std::cout << "Какую категорию добавить?: ";
            std::getline(std::cin, category);
            vector<pair<string, int>> Allcategory = Task::getAllcategori();
            for (int i = 0; i < Allcategory.size(); i++) {
                if (Allcategory[i].first == category) {
                    flag = false;
                    break; 
                }
            }
            if (Allcategory.size() == 0 || flag) { cout << "\nТакой категории нету(\n"; break; }

            vector<string> AllParametrs = model.getSettingsFilter();
            for (size_t i = 0; i < AllParametrs.size(); i++)
            {
                string nameParametr;
                string line = AllParametrs[i];
                for (size_t k = 0; k < line.size(); k++)
                {
                    if (line[k] == '=') { break; }
                    nameParametr += line[k];
                }
                if (nameParametr == "category") {
                    if (line[line.size() - 1] == '#') {
                        line.pop_back();
                        AllParametrs[i] = line + category;
                        saveSettings(AllParametrs);
                    }
                    else
                    {
                        vector<string> categoryAll;
                        string categoryTemp;
                        for (size_t k = line.size() - 1; k != -1; k--)
                        {
                            if (line[k] == '=') { categoryAll.push_back(model.reverse(categoryTemp)); break; }
                            if (line[k] == ',') {
                                categoryAll.push_back(model.reverse(categoryTemp));
                                categoryTemp = "";
                                continue;
                            }
                            categoryTemp += line[k];
                        }
                        bool flag = true;
                        for (size_t k = 0; k < categoryAll.size(); k++)
                        {
                            cout << "\ncategorAll=" << categoryAll[k] << "\n";
                            if (categoryAll[k] == category) { flag = false; break; }
                        }
                        if (flag) {
                            AllParametrs[i] = line + ',' + category;
                            saveSettings(AllParametrs);
                        }
                        else { cout << "\nТакая категория уже есть в фильтре.\n"; }
                        break;
                    }
                    
                    break;
                }
            }
            break;
        }
        case 2:{
            vector<string> AllParametrs = model.getSettingsFilter();
            for (size_t i = 0; i < AllParametrs.size(); i++)
            {
                string nameParametr;
                string line = AllParametrs[i];
                for (size_t k = 0; k < line.size(); k++)
                {
                    if (line[k] == '=') { break; }
                    nameParametr += line[k];
                }
                if (nameParametr == "category") {
                    for (size_t k = line.size() - 1; k != -1; k--)
                    {
                        if (line[k] == '=') { break; }
                        line.pop_back();
                    }
                    AllParametrs[i] = line + '#';
                    
                    break;
                }
            }
            saveSettings(AllParametrs);
            break;
        }
        case 3:
            return;
        default:
            view.displayMessage("Неверный выбор. Попробуйте снова.");
        }
    }
};

void ToDoController::filterDate() {
    while (true) {
        view.displayMessage("Настройки фильтра:");
        viewFilterDate();
        view.displayMenuFilterDate();
        int choice = getUserChoice();

        switch (choice) {
        case 1: {
            vector<string> AllParametrs = model.getSettingsFilter();
            for (size_t i = 0; i < AllParametrs.size(); i++)
            {
                string nameParametr;
                string line = AllParametrs[i];
                for (size_t k = 0; k < line.size(); k++)
                {
                    if (line[k] == '=') { break; }
                    nameParametr += line[k];
                }
                if (nameParametr == "upcomingTasks") {
                    for (size_t k = line.size() - 1; k != -1; k--)
                    {
                        if (line[k] == '=') { break; }
                        line.pop_back();
                    }
                    AllParametrs[i] = line + '1';
                    
                    break;
                }
            }
            saveSettings(AllParametrs);
            break;
        }
        case 2: {
            vector<string> AllParametrs = model.getSettingsFilter();
            for (size_t i = 0; i < AllParametrs.size(); i++)
            {
                string nameParametr;
                string line = AllParametrs[i];
                for (size_t k = 0; k < line.size(); k++)
                {
                    if (line[k] == '=') { break; }
                    nameParametr += line[k];
                }
                if (nameParametr == "upcomingTasks") {
                    for (size_t k = line.size() - 1; k != -1; k--)
                    {
                        if (line[k] == '=') { break; }
                        line.pop_back();
                    }
                    AllParametrs[i] = line + '0';
                    
                    break;
                }
            }
            saveSettings(AllParametrs);
            break;
        }
        case 3: {
            vector<string> AllParametrs = model.getSettingsFilter();
            for (size_t i = 0; i < AllParametrs.size(); i++)
            {
                string nameParametr;
                string line = AllParametrs[i];
                for (size_t k = 0; k < line.size(); k++)
                {
                    if (line[k] == '=') { break; }
                    nameParametr += line[k];
                }
                if (nameParametr == "filter_by_date_or_priority") {
                    for (size_t k = line.size() - 1; k != -1; k--)
                    {
                        if (line[k] == '=') { break; }
                        line.pop_back();
                    }
                    AllParametrs[i] = line + '0';
                    
                    break;
                }
            }
            saveSettings(AllParametrs);
            break;
        }
        case 4:{
            vector<string> AllParametrs = model.getSettingsFilter();
            for (size_t i = 0; i < AllParametrs.size(); i++)
            {
                string nameParametr;
                string line = AllParametrs[i];
                for (size_t k = 0; k < line.size(); k++)
                {
                    if (line[k] == '=') { break; }
                    nameParametr += line[k];
                }
                if (nameParametr == "upcomingTasks") {
                    for (size_t k = line.size() - 1; k != -1; k--)
                    {
                        if (line[k] == '=') { break; }
                        line.pop_back();
                    }
                    AllParametrs[i] = line + '#';
                    
                    break;
                }
            }
            saveSettings(AllParametrs);
            break;
        }
        case 5:
            return;
        default:
            view.displayMessage("Неверный выбор. Попробуйте снова.");
        }
    }
}



void ToDoController::viewFilterPriority() {
    vector<string> Allfilters = model.getSettingsFilter();
    bool param1 = false, param2 = false,param3 = false;
    for (size_t i = 0; i < Allfilters.size(); i++)
    {
        string line= Allfilters[i], nameFilter;
        for (size_t k = 0; k < line.size(); k++)
        {
            if (line[k] == '=') { break; }
            nameFilter += line[k];
        }
        if (nameFilter == "increasePriority") {
            param1 = true;
            if (line[line.size() - 1] == '#') {
                continue;
            }
            if (line[line.size() - 1] == '1') {
                cout << "Фильтр на возрастание приоритетов" << endl;
                continue;
            }
            if (line[line.size() - 1] == '0') {
                cout << "Фильтр на убывание приоритетов" << endl;
                continue;
            }
        }
        if (nameFilter == "definedPriorities") {
            param2 = true;
            if (line[line.size() - 1] == '#') {
                continue;
            }
            else
            {
                vector<string> priorityAll;
                string priorityTemp;
                for (size_t k = line.size() - 1; k != -1; k--)
                {
                    if (line[k] == '=') { priorityAll.push_back(model.reverse(priorityTemp)); break; }
                    if (line[k] == ',') {
                        priorityAll.push_back(model.reverse(priorityTemp));
                        priorityTemp = "";
                        continue;
                    }
                    priorityTemp += line[k];
                }
                cout << "Фильтр на определенные приоритеты: ";
                for (size_t k = 0; k < priorityAll.size(); k++)
                {
                    cout << priorityAll[k];
                    if (k != priorityAll.size() - 1) { cout << ", "; }
                }
                cout << endl;
            }
        }
        if (nameFilter == "filter_by_date_or_priority") {
            param3 = true;
            if (line[line.size() - 1] == '1') {
                cout << "Основной фильтр: Приоритет" << endl;
            }
        }
        if (param1 && param2 && param3) { break; }
    }
};

void ToDoController::viewFilterStatus() {
    vector<string> Allfilters = model.getSettingsFilter();
    bool param1 = false;
    for (size_t i = 0; i < Allfilters.size(); i++)
    {
        string line = Allfilters[i], nameFilter;
        for (size_t k = 0; k < line.size(); k++)
        {
            if (line[k] == '=') { break; }
            nameFilter += line[k];
        }
        if (nameFilter == "completedTasks") {
            param1 = true;
            if (line[line.size() - 1] == '#') {
                continue;
            }
            if (line[line.size() - 1] == '1') {
                cout << "Фильтр на выполненные задания" << endl;
                continue;
            }
            if (line[line.size() - 1] == '0') {
                cout << "Фильтр на не выполненные задания" << endl;
                continue;
            }
        }
        if (param1) { break; }
    }
};

void ToDoController::viewFilterCategory() {
    vector<string> Allfilters = model.getSettingsFilter();
    bool param1 = false;
    for (size_t i = 0; i < Allfilters.size(); i++)
    {
        string line = Allfilters[i], nameFilter;
        for (size_t k = 0; k < line.size(); k++)
        {
            if (line[k] == '=') { break; }
            nameFilter += line[k];
        }
        if (nameFilter == "category") {
            param1 = true;
            if (line[line.size() - 1] == '#') {
                continue;
            }
            else
            {
                vector<string> categoryAll;
                string categoryTemp;
                for (size_t k = line.size() - 1; k != -1; k--)
                {
                    if (line[k] == '=') { categoryAll.push_back(model.reverse(categoryTemp)); break; }
                    if (line[k] == ',') {
                        categoryAll.push_back(model.reverse(categoryTemp));
                        categoryTemp = "";
                        continue;
                    }
                    categoryTemp += line[k];
                }
                cout << "Фильтр на определенные категории: ";
                for (size_t k = 0; k < categoryAll.size(); k++)
                {
                    cout << categoryAll[k];
                    if (k != categoryAll.size() - 1) { cout << ", "; }
                }
                cout << endl;
            }
        }
        if (param1) { break; }
    }
};

void ToDoController::viewFilterDate() {
    vector<string> Allfilters = model.getSettingsFilter();
    bool param1 = false, param2 = false;
    for (size_t i = 0; i < Allfilters.size(); i++)
    {
        string line = Allfilters[i], nameFilter;
        for (size_t k = 0; k < line.size(); k++)
        {
            if (line[k] == '=') { break; }
            nameFilter += line[k];
        }
        if (nameFilter == "upcomingTasks") {
            param1 = true;
            if (line[line.size() - 1] == '#') {
                continue;
            }
            if (line[line.size() - 1] == '1') {
                cout << "Фильтр на ближайшие задачи" << endl;
                continue;
            }
            if (line[line.size() - 1] == '0') {
                cout << "Фильтр на далекие задачи" << endl;
                continue;
            }
        }
        if (nameFilter == "filter_by_date_or_priority") {
            param2 = true;
            if (line[line.size() - 1] == '0') {
                cout << "Основной фильтр: Дата" << endl;
            }
        }
        if (param1 && param2) { break; }
    }
};



void ToDoController::exportTask() {
    string path;
    view.displayMessage("Введите абсолютный путь,куда хотите экспортировать файл:");
    std::getline(std::cin, path);
    try
    {
        model.exportTask(path);
        view.displayMessage("Экспорт произошел успешно!");
    }
    catch (...)
    {
        view.displayMessage("Не удалось экспортировать файл! Возможно вы ввели неправильный путь");
    }
};

void ToDoController::importTask() {
    string path;
    view.displayMessage("Введите абсолютный путь, где находятся задачи:");
    std::getline(std::cin, path);
    try
    {
        model.importTask(path);
        view.displayMessage("Импорт произошел успешно!");
    }
    catch (...)
    {
        view.displayMessage("Импорт не удался( Возможно вы ввели неправильный путь к файлу");
    }
};

int ToDoController::getUserChoice() const {
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return choice;
}

void ToDoController::addTask() {
    std::string title, description, category, dueDate;
    int priority;

    std::cout << "Введите название задачи: ";
    std::getline(std::cin, title);
    std::cout << "Введите описание задачи: ";
    std::getline(std::cin, description);

    std::cout << "Введите категорию задачи: ";
    std::getline(std::cin, category);
    vector<pair<string,int>> Allcategory = Task::getAllcategori();
    bool flagCatecory = true;
    for (int i = 0; i < Allcategory.size(); i++) {
        if (Allcategory[i].first == category) {
            Allcategory[i].second += 1;
            flagCatecory = false;
            break;
        }
    }
        
    
    std::cout << "Введите приоритет задачи (1-5): ";
    std::cin >> priority;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::time_t seconds;
    while (true)
    {
        std::cout << "Введите срок выполнения задачи: ";
        std::getline(std::cin, dueDate);
        try
        {
            std::tm date = checkDate(dueDate);
            //cout << date.tm_mday<<"|" << date.tm_mon <<"|" << date.tm_year << date.tm_hour << date.tm_min << "\n";
            isValid(date.tm_mday, date.tm_mon, date.tm_year, date.tm_hour, date.tm_min);
            // Преобразуем структуру tm в количество секунд с начала эпохи
            seconds = std::mktime(&date);
            break;
        }
        catch (...)
        {
            dueDate = "";
            std::cout << "Вы неправильно ввели дату! Пример: dd.mm.yyyy hh:mm" << '\n';
        }
    }



    Task task(title, description, category, priority, seconds);
    model.addTask(task);
    if (flagCatecory) {
        Allcategory.push_back({ category ,1 });
        Task::setAllcategori(Allcategory);
    }
    if (!flagCatecory){ Task::setAllcategori(Allcategory); }
    view.displayMessage("Задача добавлена.");
}

void ToDoController::removeTask() {
    std::string title;
    std::cout << "Введите название задачи для удаления: ";
    std::getline(std::cin, title);
    string category = model.removeTask(title);
    if (category!="") {
        vector<pair<string, int>> Allcategory = Task::getAllcategori();
        for (int i = 0; i < Allcategory.size(); i++) {
            if (Allcategory[i].first == category) {
                if (Allcategory[i].second == 1){}
                else { Allcategory[i].second -= 1; }
                break;
            }
        }
        Task::setAllcategori(Allcategory);
        view.displayMessage("Задача удалена.");
    }
    else
    {
        view.displayMessage("Такой задачи нету.");
    }
}

void ToDoController::markTaskCompleted() {
    std::string title;
    std::cout << "Введите название задачи для отметки как выполненной: ";
    std::getline(std::cin, title);
    model.markTaskCompleted(title);
    view.displayMessage("Задача отмечена как выполненная.");
}

void ToDoController::showAllTasks() {
    std::vector<Task> tasks = model.getAllTasks();
    view.displayTasks(tasks);
}


void ToDoController::saveSettings(vector<string>& AllParametrs) {
    // Открытие файла для записи
    std::ofstream outfile("settingsFiltr.txt");
    if (!outfile.is_open()) {
        std::cerr << "Ошибка при открытии файла!" << std::endl;
        throw "Ошибка открытия файла настроек фильтра";
    }

    for (size_t i = 0; i < AllParametrs.size(); i++)
    {
        outfile << AllParametrs[i] << '\n';
    }
    // Закрытие файла
    outfile.close();
};

std::tm ToDoController::checkDate(std::string date_str) {
    date_str = model.trim(date_str);
    size_t lenght = date_str.size();
    bool checkTime = false;
    for (size_t k = 0; k < lenght; k++) {
        if (date_str[k] == ':') { checkTime = true; break; }
    }

    size_t i = 0;
    std::string day, month, year, hour = "0", min = "0";
    for (; i < lenght; i++)
    {
        if (date_str[i] == '.') { i++; break; }
        day += date_str[i];
    }
    for (; i < lenght; i++)
    {
        if (date_str[i] == '.') { i++; break; }
        month += date_str[i];
    }
    for (; i < lenght; i++)
    {
        if (date_str[i] == ' ') { i++; break; }
        year += date_str[i];
    }
    day = model.trim(day); month = model.trim(month); year = model.trim(year);

    if (checkTime) {
        for (; i < lenght; i++)
        {
            if (date_str[i] == ':') { i++; break; }
            hour += date_str[i];
        }
        for (; i < lenght; i++)
        {
            min += date_str[i];
        }
    }
    int day_i = stoi(day), month_i = stoi(month), year_i = stoi(year), hour_i = stoi(hour), min_i = stoi(min);


    std::tm date = {};

    // Устанавливаем значения даты и времени
    date.tm_year = year_i-1900;  // Год с 1900 года (например, 2023 - 1900 = 123)
    date.tm_mon = month_i;     // Месяц (0 - январь, 1 - февраль, ..., 9 - октябрь)
    date.tm_mday = day_i;    // День месяца (1-31)
    date.tm_hour = hour_i;   // Часы (0-23)
    date.tm_min = min_i;    // Минуты (0-59)
    date.tm_sec = 0;    // Секунды (0-59)

    return date;
}

void ToDoController::isValid(int day, int month, int year, int hour, int min) const {
    if (year < 1 || month < 0 || month > 11 || day < 1 || day>31 || hour < 0 || hour>23 || min < 0 || min>59) {
        throw "Неправильный ввод даты!";
    }

    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Проверка на високосный год
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
        daysInMonth[1] = 29;
    }

    if (!(day <= daysInMonth[month - 1])) {
        throw "Неправильный ввод даты(Проверка на високосный год)!";
    };
}
