#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class Task{
    private : 
    string description;
    bool completed;

    public :
    Task(string desc =  "") : description(desc), completed(false){}
    string getDescription() const { 
        return description;
    }
    bool isCompleted() const{
        return completed;
    }
    void setComplete(bool status){
        completed = status;
    }
};

class Node{
    public :
    Task task;
    Node* next;
    Node(const Task& t) : task(t), next(nullptr) {}
};
class TaskManager{
    private:
    Node* head;
    int count;

    void clearList(){
        Node* curr = head;
        while(curr){
        Node* next = curr->next;
        delete curr;
        curr = next;
    }
}
public: 
TaskManager() : head(nullptr), count(0) {}
~TaskManager() {
    clearList();
}

void addTask(const Task& task){
    Node* newNode = new Node(task);
    newNode-> next = head;
    head = newNode;
    count++;
}

void removeTask(const string& desc){
    Node*curr = head;
    Node* prev = nullptr;
    while(curr){
        if(curr->task.getDescription() == desc){
            if(prev){
                prev->next = curr->next;
            } else {
                head = curr->next;
            }
            delete curr;
            count--;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    cout<< "Task not found.\n";
}

void markComplete(const string& desc){
    Node* curr = head;
    while(curr){
        if(curr->task.getDescription() == desc){
            curr->task.setComplete(true);
            cout<<"Task marked complete.\n";
            return;
        }
        curr = curr->next;
    }
    cout<<"Task not found.\n";
}

void displayTasks() const{
    cout<<"Tasks (" << count << " total):\n";
    Node* curr = head;
    if(!curr){
        cout<<"No tasks.\n";
        return;
    }

    while(curr){
        cout<<"- "<<curr->task.getDescription();
        if(curr->task.isCompleted()) cout << " YAY DONE! ";
        cout<<"\n";
        curr = curr->next;
    }
}

void loadFromFile(const string& filename = "tasks.txt") {
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            size_t pos = line.find('|');
            if (pos != string::npos) {
                string desc = line.substr(0, pos);
                bool done = (line.substr(pos + 1) == "1");
                Task t(desc);
                if (done) t.setComplete(true);
                addTask(t);
            }
        }
        file.close();
        cout << "Loaded from " << filename << "\n";
    }

void saveToFile(const string& filename = "tasks.txt"){
    ofstream file(filename);
    Node* curr = head;
    while(curr){
        file << curr->task.getDescription()<<"|"<< curr->task.isCompleted()<<"\n";
        curr = curr->next;
    }
    file.close();
    cout<<"Saved to "<< filename << "\n";
}

};

int main() {
    TaskManager tm;
    tm.loadFromFile();  
    
    int choice;
    string desc;
    
    do {
        cout << "\n=== Task Manager ===\n";
        cout << "1. Add Task\n";
        cout << "2. Remove Task\n";
        cout << "3. Mark Complete\n";
        cout << "4. Display Tasks\n";
        cout << "5. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();  
        
        if (choice == 5) break;
        
        cout << "Task: ";
        getline(cin, desc);
        
        switch (choice) {
            case 1: tm.addTask(Task(desc)); cout << "Added.\n"; break;
            case 2: tm.removeTask(desc); break;
            case 3: tm.markComplete(desc); break;
            case 4: tm.displayTasks(); break;
            default: cout << "Invalid choice.\n";
        }
    } while (true);
    
    tm.saveToFile();
    return 0;
}
