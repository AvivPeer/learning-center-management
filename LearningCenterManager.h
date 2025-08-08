#ifndef LEARNING_CENTER_MANAGER_H
#define LEARNING_CENTER_MANAGER_H

#include "DatabaseManager.h"

class LearningCenterManager {
private:
    DatabaseManager db;

    // Menu display methods
    void displayMenu();
    void displayStudentMenu();
    void displayAssignmentMenu();

    // Student management methods
    void addStudent();
    void viewStudent();
    void listAllStudents();
    void updateStudent();
    void removeStudent();

    // Assignment management methods
    void createAssignment();
    void viewAssignment();
    void listAllAssignments();
    void updateAssignmentStatus();
    void viewStudentAssignments();

    // Report methods
    void generateReports();

public:
    // Constructor
    LearningCenterManager();

    // Main application loop
    void run();
};

#endif // LEARNING_CENTER_MANAGER_H