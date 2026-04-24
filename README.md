Process Synchronization Simulator
A educational tool designed to simulate how an Operating System manages shared resources among concurrent processes. This project demonstrates the fundamental concepts of process management and synchronization mechanisms to prevent race conditions and data inconsistency.

🚀 Project Overview

In a real-world OS, multiple processes often access shared data like memory or hardware devices. Without proper control, this can lead to system errors. This simulator provides a visual and functional representation of how synchronization solves these issues.

✨ Key Features

 * **Process Management:** Create multiple processes with unique IDs and specific execution times.
 * **Synchronization Mechanisms:** Implementation of **Mutex Locks** and **Semaphores** (Binary and Counting).
 * **Critical Section Simulation:** Clear visualization of Entry, Critical, and Exit sections.
 * **Real-time Monitoring:** Track process states such as **Running**, **Waiting**, and **Blocked**.
 * **Concurrency Support:** Capable of handling 10-15 concurrent processes simultaneously.

🛠️ Technical Specifications

 * **Platform:** Windows.
 * **Environment:** Java (Simulation behavior focused).
 * **Architecture:** Modular and well-documented code structure.
## 🖥️ How to Use
 1. **Input:** Enter the number of processes and their execution time.
 2. **Configuration:** Select the synchronization method (Mutex or Semaphore).
 3. **Control:** Use the **Start**, **Stop**, **Reset**, or **Step** buttons to control the simulation flow.
 4. **Observe:** Watch the "Waiting Queue" and "Critical Section" to see how processes are blocked or granted access.
## 📊 System Requirements
 * **Input Types:** All numeric inputs must be positive integers.
 * **Stability:** Built-in error handling to prevent crashes from invalid inputs.
## 👥 Contributors
 * **Muhammad Uzair** (2023-UoK-03680)
 * **Syed Saqlain Haider** (2023-UoK-03688)
 * **Ausaf Ahmed** (2023-UoK-03691)
**Instructor:** Mr. Mehtab Mushtaq
**Department:** CS & IT, University of Kotli Azad Jammu & Kashmir
> **Note:** This project is for educational purposes and focuses on behavior simulation rather than actual hardware kernel control.
>
