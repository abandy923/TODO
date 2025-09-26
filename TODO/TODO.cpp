#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct Task {
    string description;
    bool done;
};

// Load tasks from file
void loadTasks(vector<Task>& tasks, const string& filename) {
    ifstream file(filename);
    if (!file) return;

    string line;
    while (getline(file, line)) {
        Task t;
        if (line.substr(0, 3) == "[x]") {
            t.done = true;
            t.description = line.substr(4);
        }
        else {
            t.done = false;
            t.description = line.substr(4);
        }
        tasks.push_back(t);
    }
    file.close();
}

// Save tasks to file
void saveTasks(const vector<Task>& tasks, const string& filename) {
    ofstream file(filename);
    for (const auto& t : tasks) {
        file << (t.done ? "[x] " : "[ ] ") << t.description << endl;
    }
    file.close();
}

// Display tasks
void listTasks(const vector<Task>& tasks) {
    cout << "\n--- To-Do List ---\n";
    if (tasks.empty()) {
        cout << "No tasks yet. Use option 2 to add one.\n";
    }
    else {
        for (size_t i = 0; i < tasks.size(); i++) {
            cout << i + 1 << ". [" << (tasks[i].done ? "x" : " ") << "] "
                << tasks[i].description << endl;
        }
    }
}


// Add new task
void addTask(vector<Task>& tasks) {
    string desc;
    cout << "Enter task description: ";
    cin.ignore();
    getline(cin, desc);
    tasks.push_back({ desc, false });
}

// Mark task as done
void completeTask(vector<Task>& tasks) {
    int index;
    cout << "Enter task number to mark as done: ";
    cin >> index;
    if (index > 0 && index <= tasks.size()) {
        tasks[index - 1].done = true;
        cout << "Task marked as done.\n";
    }
    else {
        cout << "Invalid task number.\n";
    }
}

// Delete task
void deleteTask(vector<Task>& tasks) {
    int index;
    cout << "Enter task number to delete: ";
    cin >> index;
    if (index > 0 && index <= tasks.size()) {
        tasks.erase(tasks.begin() + index - 1);
        cout << "Task deleted.\n";
    }
    else {
        cout << "Invalid task number.\n";
    }
}

int main() {
    vector<Task> tasks;
    string filename = "tasks.txt";
    loadTasks(tasks, filename);

    int choice;
    do {
        cout << "\n1. List tasks\n2. Add task\n3. Complete task\n4. Delete task\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: listTasks(tasks); break;
        case 2: addTask(tasks); break;
        case 3: completeTask(tasks); break;
        case 4: deleteTask(tasks); break;
        case 5: saveTasks(tasks, filename); cout << "Goodbye!\n"; break;
        default: cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}



//Lists tasks with status [ ] or [x].

//Add, complete, and delete tasks.

//Saves tasks to tasks.txt so data persists between runs.