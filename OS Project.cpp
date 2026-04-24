#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

// ----------------------------
// Process Structure
// ----------------------------
struct Process {
    int pid;
    int execTime;
    int remainingTime;
    string state;   // Running, Waiting, Blocked

    Process(int id, int time) {
        pid = id;
        execTime = time;
        remainingTime = time;
        state = "Waiting";
    }
};

// ----------------------------
// Synchronization System Class
// ----------------------------
class ProcessSynchronizationSystem {
private:
    vector<Process> processes;
    queue<int> waitingQueue;
    string syncMethod;
    int semaphoreValue;
    bool mutexLocked;
    int currentHolder;

public:
    ProcessSynchronizationSystem(vector<Process> p, string method, int semVal = 1) {
        processes = p;
        syncMethod = method;
        semaphoreValue = semVal;
        mutexLocked = false;
        currentHolder = -1;
    }

    // ----------------------------
    // Entry Section
    // ----------------------------
    bool entrySection(int index) {
        if (syncMethod == "mutex") {
            if (!mutexLocked) {
                mutexLocked = true;
                currentHolder = processes[index].pid;
                processes[index].state = "Running";
                return true;
            }
        } else { // Semaphore
            if (semaphoreValue > 0) {
                semaphoreValue--;
                currentHolder = processes[index].pid;
                processes[index].state = "Running";
                return true;
            }
        }

        processes[index].state = "Blocked";
        waitingQueue.push(index);
        return false;
    }

    // ----------------------------
    // Critical Section
    // ----------------------------
    void criticalSection(int index) {
        cout << "?? Process " << processes[index].pid
             << " is in CRITICAL SECTION\n";
        processes[index].remainingTime--;
    }

    // ----------------------------
    // Exit Section
    // ----------------------------
    void exitSection(int index) {
        if (syncMethod == "mutex") {
            mutexLocked = false;
        } else {
            semaphoreValue++;
        }

        processes[index].state = "Waiting";
        currentHolder = -1;

        if (!waitingQueue.empty()) {
            waitingQueue.pop();
        }
    }

    // ----------------------------
    // One Step Execution
    // ----------------------------
    void step() {
        cout << "\n--- SYSTEM STEP ---\n";

        for (int i = 0; i < processes.size(); i++) {
            if (processes[i].remainingTime <= 0)
                continue;

            if (processes[i].state == "Waiting") {
                if (!entrySection(i))
                    continue;
            }

            if (processes[i].state == "Running") {
                criticalSection(i);

                if (processes[i].remainingTime == 0) {
                    cout << "? Process " << processes[i].pid << " FINISHED\n";
                    exitSection(i);
                }
                break; // Only one process in critical section
            }
        }
        displayStatus();
    }

    // ----------------------------
    // Display System State
    // ----------------------------
    void displayStatus() {
        cout << "\n?? Process States:\n";
        for (auto &p : processes) {
            cout << "Process " << p.pid
                 << " | State: " << p.state
                 << " | Remaining Time: " << p.remainingTime << endl;
        }

        cout << "\n? Waiting Queue: ";
        if (waitingQueue.empty())
            cout << "Empty";
        else {
            queue<int> temp = waitingQueue;
            while (!temp.empty()) {
                cout << "P" << processes[temp.front()].pid << " ";
                temp.pop();
            }
        }

        cout << "\n?? Lock Holder: ";
        if (currentHolder == -1)
            cout << "None\n";
        else
            cout << "Process " << currentHolder << "\n";
    }

    // ----------------------------
    // Check Completion
    // ----------------------------
    bool isFinished() {
        for (auto &p : processes) {
            if (p.remainingTime > 0)
                return false;
        }
        return true;
    }
};

// ----------------------------
// MAIN FUNCTION
// ----------------------------
int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes;
    for (int i = 1; i <= n; i++) {
        int time;
        cout << "Execution time for Process " << i << ": ";
        cin >> time;
        processes.push_back(Process(i, time));
    }

    cout << "\nSelect Synchronization Method:\n";
    cout << "1. Mutex\n";
    cout << "2. Semaphore\n";
    int choice;
    cin >> choice;

    ProcessSynchronizationSystem system(
        processes,
        choice == 1 ? "mutex" : "semaphore",
        choice == 2 ? (cout << "Enter semaphore value: ", cin, 1) : 1
    );

    cout << "\nPress ENTER to execute STEP (Ctrl+C to stop)\n";
    cin.ignore();

    while (!system.isFinished()) {
        cin.get();
        system.step();
    }

    cout << "\n?? All processes completed successfully!\n";
    return 0;
}