#include "ToDoModel.h"



// ������� ��� ������� �������� � ������ � � ����� ������
string ToDoModel::trim(const std::string& str) {
    if (str.empty()) {
        return str;
    }

    // ������� ������ ������������ ������ � ������ ������
    size_t start = str.find_first_not_of(" \t\n\r");
    // ������� ������ ������������ ������ � ����� ������
    size_t end = str.find_last_not_of(" \t\n\r");

    // ���� ������ ������� ������ �� ��������, ���������� ������ ������
    if (start == std::string::npos) {
        return "";
    }

    // ���������� ��������� ��� �������� � ������ � � �����
    return str.substr(start, end - start + 1);
}

string ToDoModel::reverse(string str) {
    // �������������� ������ �������
    int length = str.length();
    for (int i = 0; i < length / 2; ++i) {
        // ���������� �������
        std::swap(str[i], str[length - i - 1]);
    }
    return str;
}


void ToDoModel::addTask(const Task& task) {
    tasks.push_back(task);
}

string ToDoModel::removeTask(const std::string& title) {
    string category = "";
    for (size_t i = 0; i < tasks.size();i++) {
        if (tasks[i].getTitle() == title) {
            category = tasks[i].getCategory();
            tasks.erase(tasks.begin() + i);
            break;
        }
    }
    return category;
    //tasks.erase(std::remove_if(tasks.begin(), tasks.end(), [&](const Task& task) {
    //    return task.getTitle() == title;
    //    }), tasks.end());
}

void ToDoModel::markTaskCompleted(const std::string& title) {
    for (Task& task : tasks) {
        if (task.getTitle() == title) {
            task.markCompleted();
            break;
        }
    }
}


std::vector<Task> ToDoModel::getAllTasks(){
    vector<string> AllparaFilter = getSettingsFilter();
    vector<Task> AllTask = tasks;
    char sort_priority_ascending, sort_by_date, mainFilter;
    for (size_t i = 0; i < AllparaFilter.size(); i++) {
        string nameParametr;
        string line = AllparaFilter[i];
        for (size_t k = 0; k < line.size(); k++)
        {
            if (line[k] == '=') { break; }
            nameParametr += line[k];
        }
        if (nameParametr == "increasePriority") {
            sort_priority_ascending = line[line.size() - 1];
            continue;
        }
        if (nameParametr == "upcomingTasks") {
            sort_by_date = line[line.size() - 1];
            continue;
        }
        if (nameParametr == "filter_by_date_or_priority") {
            mainFilter = line[line.size() - 1];
            continue;
        }
        if (nameParametr == "definedPriorities") {
            char valueFilter = line[line.size() - 1];
            if (valueFilter=='#') {
                continue;
            }
            else {
                vector<int> priorityAll;
                string priorityTemp;
                vector<Task> AllTaskTemp;
                for (size_t k = line.size() - 1; k != -1; k--)
                {
                    if (line[k] == '=') { priorityAll.push_back(stoi(reverse(priorityTemp))); break; }
                    if (line[k] == ',') {
                        priorityAll.push_back(stoi(reverse(priorityTemp)));
                        priorityTemp = "";
                        continue;
                    }
                    priorityTemp += line[k];
                }

                for (size_t k = 0; k < AllTask.size(); k++) {
                    for (size_t j = 0; j < priorityAll.size(); j++)
                    {

                        if (AllTask[k].getPriority() == priorityAll[j]) {
                            AllTaskTemp.push_back(AllTask[k]);
                            break;
                        }
                    }
                }

                AllTask = AllTaskTemp;
            }
            
            continue;
        }
        if (nameParametr == "completedTasks"){
            char valueFilter = line[line.size() - 1];
            vector<Task> AllTaskTemp;
            if (valueFilter == '#') { continue; }
            else if (valueFilter == '1') {
                //����������
                for (size_t k = 0; k < AllTask.size(); k++)
                {
                    if (AllTask[k].isCompleted()) { AllTaskTemp.push_back(AllTask[k]); }
                }
            }
            else if (valueFilter == '0') {
                //�� ����������
                for (size_t k = 0; k < AllTask.size(); k++)
                {
                    if (!AllTask[k].isCompleted()) { AllTaskTemp.push_back(AllTask[k]); }
                }
            }
            AllTask = AllTaskTemp;
            continue;
        }
        if (nameParametr == "category") {
            char valueFilter = line[line.size() - 1];
            if (valueFilter == '#') {
                continue;
            }
            else {
                vector<string> categoryAll;
                string categoryTemp;
                vector<Task> AllTaskTemp;
                for (size_t k = line.size() - 1; k != -1; k--)
                {
                    if (line[k] == '=') { categoryAll.push_back(reverse(categoryTemp)); break; }
                    if (line[k] == ',') {
                        categoryAll.push_back(reverse(categoryTemp));
                        categoryTemp = "";
                        continue;
                    }
                    categoryTemp += line[k];
                }

                for (size_t k = 0; k < AllTask.size(); k++) {
                    for (size_t j = 0; j < categoryAll.size(); j++)
                    {
                        if (AllTask[k].getCategory() == categoryAll[j]) {

                            AllTaskTemp.push_back(AllTask[k]);
                            break;
                        }
                    }
                }
                AllTask = AllTaskTemp;
            }

            continue;
        }
    }
    if (sort_priority_ascending == '#' && sort_by_date == '#') {
        return AllTask;
    }
    
    if (mainFilter=='1') {
        //�������� ������ "���������"
        sort(AllTask.begin(), AllTask.end(), [sort_priority_ascending, sort_by_date](const Task& a, const Task& b) {
            if (sort_priority_ascending == '#') {
                if (sort_by_date == '1') {
                    return a.getDueDateSec() < b.getDueDateSec();
                }
                else {
                    return a.getDueDateSec() > b.getDueDateSec();
                }
            }

            if (sort_by_date == '#') {
                if (sort_priority_ascending == '1') {
                    return a.getPriority() < b.getPriority();
                }
                else {
                    return a.getPriority() > b.getPriority();
                }
            }

            if (a.getPriority() == b.getPriority()) {
                if (sort_by_date == '1') {
                    return a.getDueDateSec() < b.getDueDateSec();
                }
                else {
                    return a.getDueDateSec() > b.getDueDateSec();
                }
            }

            if (sort_priority_ascending == '1') {
                return a.getPriority() < b.getPriority();
            }
            else {
                return a.getPriority() > b.getPriority();
            }
            });
    }

    if (mainFilter == '0') {
        //�������� ������ "����"
        sort(AllTask.begin(), AllTask.end(), [sort_priority_ascending, sort_by_date](const Task& a, const Task& b) {
            if (sort_priority_ascending == '#') {
                if (sort_by_date == '1') {
                    return a.getDueDateSec() < b.getDueDateSec();
                }
                else {
                    return a.getDueDateSec() > b.getDueDateSec();
                }
            }

            if (sort_by_date == '#') {
                if (sort_priority_ascending == '1') {
                    return a.getPriority() < b.getPriority();
                }
                else {
                    return a.getPriority() > b.getPriority();
                }
            }

            if (a.getDueDateSec() == b.getDueDateSec()) {
                if (sort_priority_ascending == '1') {
                    return a.getPriority() < b.getPriority();
                }
                else {
                    return a.getPriority() > b.getPriority();
                }
            }

            if (sort_by_date == '1') {
                return a.getDueDateSec() < b.getDueDateSec();
            }
            else {
                return a.getDueDateSec() > b.getDueDateSec();
            }
            });
    }

    
    return AllTask;
}


vector<string> ToDoModel::getSettingsFilter() {
    // �������� ����� ��� ������
    std::ifstream infile("settingsFiltr.txt");
    if (!infile.is_open()) {
        std::cerr << "������ ��� �������� ����� �������� �������!" << std::endl;
        throw "������ ������ �����";
    }

    // ������ ����� ���������
    vector<string> AllParametrs;
    std::string line;
    while (std::getline(infile, line)) {
        line = trim(line);
        AllParametrs.push_back(line);
    }

    // �������� �����
    infile.close();

    return AllParametrs;
};

void ToDoModel::saveSettings(vector<string>& AllParametrs) {
    // �������� ����� ��� ������
    std::ofstream outfile("settingsFiltr.txt");
    if (!outfile.is_open()) {
        std::cerr << "������ ��� �������� �����!" << std::endl;
        throw "������ �������� ����� �������� �������";
    }

    for (size_t i = 0; i < AllParametrs.size(); i++)
    {
        outfile << AllParametrs[i] << '\n';
    }
    // �������� �����
    outfile.close();
};

void ToDoModel::exportTask(string path) {

    // �������� ����� ��� ������
    std::ofstream outfile(path+"\\Tasks.csv");
    if (!outfile.is_open()) {
        std::cerr << "������ ��� �������� �����!" << std::endl;
        throw "������ �������� �����";
    }

    for (size_t i = 0; i < tasks.size(); i++)
    {
        outfile << tasks[i].getTitle() << '|'
            << tasks[i].getDescription() << '|'
            << tasks[i].getCategory() << '|'
            << tasks[i].getPriority() << '|'
            << tasks[i].getDueDateSec()<< '|'
            << tasks[i].isCompleted()<<"\n";
    }
    // �������� �����
    outfile.close();
}

void ToDoModel::importTask(string path) {
    // �������� ����� ��� ������
    std::ifstream infile(path);
    if (!infile.is_open()) {
        std::cerr << "������ ��� �������� �����" << std::endl;
        throw "������ ������ �����";
    }

    // ������ ����� ���������
    vector<pair<string, int>> Allcategory = Task::getAllcategori();
    std::string line;
    while (std::getline(infile, line)) {
        string title, desc, category,priort,dateSec,iscomplete;

        std::istringstream iss(line);
        std::string param;

        getline(iss, param, '|');
        title = param;

        getline(iss, param, '|');
        desc = param;

        getline(iss, param, '|');
        category = param;

        getline(iss, param, '|');
        priort = param;

        getline(iss, param, '|');
        dateSec = param;

        getline(iss, param, '\n');
        iscomplete = param;

        bool iscompleteb;
        if (iscomplete == "1") { iscompleteb = true; }
        else { iscompleteb = false; }
        

        tasks.push_back(Task(title, desc, category, stoi(priort), (time_t)stoi(dateSec), iscompleteb));
        bool flag = true;
        for (size_t i = 0; i < Allcategory.size(); i++)
        {
            if (Allcategory[i].first == category) {
                Allcategory[i].second += 1;
                flag = false;
            }
        }
        if (flag) { Allcategory.push_back({category,1}); }

    }
    Task::setAllcategori(Allcategory);

    // �������� �����
    infile.close();
};

