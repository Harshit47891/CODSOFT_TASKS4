#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

struct Task {
    string description;
    bool completed;
};

class ToDoList {
private:
    vector<Task> tasks;

public:
    void addTask(const string& description) {
        tasks.push_back({description, false});
        cout << "Task added.\n";
    }

    void viewTasks() const {
        if (tasks.empty()) {
            cout << "\nYour to-do list is empty.\n";
            return;
        }
        cout << "\n--- To-Do List ---\n";
        for (size_t i = 0; i < tasks.size(); i++) {
            cout << i + 1 << ". [" << (tasks[i].completed ? "Completed" : "Pending")
                 << "] " << tasks[i].description << "\n";
        }
    }

    void markCompleted(int index) {
        if (index < 1 || index > (int)tasks.size()) {
            cout << "Invalid task number.\n";
            return;
        }
        if (tasks[index - 1].completed) {
            cout << "Task is already completed.\n";
            return;
        }
        tasks[index - 1].completed = true;
        cout << "Task marked as completed.\n";
    }

    void removeTask(int index) {
        if (index < 1 || index > (int)tasks.size()) {
            cout << "Invalid task number.\n";
            return;
        }
        cout << "Removed: " << tasks[index - 1].description << "\n";
        tasks.erase(tasks.begin() + (index - 1));
    }

    bool isEmpty() const { return tasks.empty(); }
};

int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number.\n";
    }
}

int main() {
    ToDoList list;
    int choice;

    do {
        cout << "\n===== TO-DO LIST MANAGER =====\n"
             << "1. Add task\n"
             << "2. View tasks\n"
             << "3. Mark task as completed\n"
             << "4. Remove task\n"
             << "5. Exit\n";
        choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1: {
                string description;
                cout << "Enter task: ";
                getline(cin, description);
                if (description.empty())
                    cout << "Task cannot be empty.\n";
                else
                    list.addTask(description);
                break;
            }
            case 2:
                list.viewTasks();
                break;
            case 3:
                if (list.isEmpty()) { cout << "No tasks to mark.\n"; break; }
                list.viewTasks();
                list.markCompleted(readInt("Enter task number to mark completed: "));
                break;
            case 4:
                if (list.isEmpty()) { cout << "No tasks to remove.\n"; break; }
                list.viewTasks();
                list.removeTask(readInt("Enter task number to remove: "));
                break;
            case 5:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please select 1-5.\n";
        }
    } while (choice != 5);

    return 0;
}
