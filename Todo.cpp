#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

struct Task {
    int id;
    std::string description;
    bool completed;

    Task(int id, const std::string& desc) : id(id), description(desc), completed(false) {}
};

std::vector<Task> tasks;
int nextId = 1;

void addTask() {
    std::string description;
    std::cout << "Enter task description: ";
    std::getline(std::cin, description);
    
    if (description.empty()) {
        std::cout << "Description cannot be empty!\n";
        return;
    }
    
    tasks.emplace_back(nextId++, description);
    std::cout << "Task added successfully with ID: " << (nextId - 1) << "\n";
}

void listTasks() {
    if (tasks.empty()) {
        std::cout << "No tasks found.\n";
        return;
    }
    
    std::cout << "\n--- Task List ---\n";
    for (const auto& task : tasks) {
        std::cout << "ID: " << task.id 
                  << " - " << task.description 
                  << " [" << (task.completed ? "Completed" : "Pending") << "]\n";
    }
    std::cout << "-----------------\n";
}

void deleteTask() {
    int id;
    std::cout << "Enter task ID to delete: ";
    
    if (!(std::cin >> id)) {
        std::cout << "Invalid input. Please enter a number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    std::cin.ignore();
    
    auto it = std::find_if(tasks.begin(), tasks.end(), 
        [id](const Task& t) { return t.id == id; });
    
    if (it != tasks.end()) {
        tasks.erase(it);
        std::cout << "Task deleted successfully!\n";
    } else {
        std::cout << "Task not found with ID: " << id << "\n";
    }
}

void markCompleted() {
    int id;
    std::cout << "Enter task ID to mark as completed: ";
    
    if (!(std::cin >> id)) {
        std::cout << "Invalid input. Please enter a number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    std::cin.ignore();
    
    auto it = std::find_if(tasks.begin(), tasks.end(), 
        [id](const Task& t) { return t.id == id; });
    
    if (it != tasks.end()) {
        it->completed = true;
        std::cout << "Task marked as completed!\n";
    } else {
        std::cout << "Task not found with ID: " << id << "\n";
    }
}

int main() {
    int choice;
    
    std::cout << "CLI Todo List App\n";
    
    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add Task\n";
        std::cout << "2. List Tasks\n";
        std::cout << "3. Delete Task\n";
        std::cout << "4. Mark Task as Completed\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number between 1-5.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore();
        
        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                listTasks();
                break;
            case 3:
                deleteTask();
                break;
            case 4:
                markCompleted();
                break;
            case 5:
                std::cout << "Exiting the application. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please enter a number between 1-5.\n";
                break;
        }
    } while (choice != 5);

    return 0;
}