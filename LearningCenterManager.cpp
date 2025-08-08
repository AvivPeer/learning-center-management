#include "LearningCenterManager.h"
#include <iostream>
#include <limits>

LearningCenterManager::LearningCenterManager() {
    if (!db.testConnection()) {
        std::cerr << "Failed to connect to MongoDB. Please ensure MongoDB is running." << std::endl;
        std::cerr << "Default connection: mongodb://localhost:27017" << std::endl;
        exit(1);
    }
    std::cout << "Successfully connected to MongoDB!" << std::endl;
}

void LearningCenterManager::displayMenu() {
    std::cout << "\n===============================================" << std::endl;
    std::cout << "    Learning Center Management System" << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "1. Student Management" << std::endl;
    std::cout << "2. Assignment Management" << std::endl;
    std::cout << "3. Reports" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "Enter your choice: ";
}

void LearningCenterManager::displayStudentMenu() {
    std::cout << "\n--- Student Management ---" << std::endl;
    std::cout << "1. Add New Student" << std::endl;
    std::cout << "2. View Student Details" << std::endl;
    std::cout << "3. List All Students" << std::endl;
    std::cout << "4. Update Student Info" << std::endl;
    std::cout << "5. Remove Student" << std::endl;
    std::cout << "6. Back to Main Menu" << std::endl;
    std::cout << "Enter your choice: ";
}

void LearningCenterManager::displayAssignmentMenu() {
    std::cout << "\n--- Assignment Management ---" << std::endl;
    std::cout << "1. Create New Assignment" << std::endl;
    std::cout << "2. View Assignment Details" << std::endl;
    std::cout << "3. List All Assignments" << std::endl;
    std::cout << "4. Update Assignment Status" << std::endl;
    std::cout << "5. View Student Assignments" << std::endl;
    std::cout << "6. Back to Main Menu" << std::endl;
    std::cout << "Enter your choice: ";
}

void LearningCenterManager::addStudent() {
    std::string firstName, lastName, email, homeTeacher, instructor;

    std::cout << "\n--- Add New Student ---" << std::endl;
    std::cout << "First Name: ";
    std::cin >> firstName;
    std::cout << "Last Name: ";
    std::cin >> lastName;
    std::cout << "Home Teacher: ";
    std::cin >> homeTeacher;
    std::cout << "Personal Instructor: ";
    std::cin >> instructor;

    Student student(firstName, lastName, homeTeacher, instructor);

    if (db.addStudent(student)) {
        std::cout << "Student added successfully! ID: " << student.getId() << std::endl;
    }
    else {
        std::cout << "Error: Student already exists or database error!" << std::endl;
    }
}

void LearningCenterManager::viewStudent() {
    std::string id;
    std::cout << "Enter Student ID: ";
    std::cin >> id;

    auto student = db.getStudent(id);
    if (student) {
        std::cout << "\n--- Student Details ---" << std::endl;
        student->displayInfo();
    }
    else {
        std::cout << "Student not found!" << std::endl;
    }
}

void LearningCenterManager::listAllStudents() {
    auto students = db.getAllStudents();
    if (students.empty()) {
        std::cout << "No students found." << std::endl;
        return;
    }

    std::cout << "\n--- All Students ---" << std::endl;
    for (const auto& student : students) {
        std::cout << "ID: " << student.getId() << " | Name: " << student.getFullName()
            << " | Teacher: " << student.getHomeTeacher() << std::endl;
    }
}

void LearningCenterManager::updateStudent() {
    std::string id;
    std::cout << "Enter Student ID to update: ";
    std::cin >> id;

    auto student = db.getStudent(id);
    if (!student) {
        std::cout << "Student not found!" << std::endl;
        return;
    }

    std::cout << "\n--- Current Student Info ---" << std::endl;
    student->displayInfo();

    std::cout << "\n--- Update Student Info ---" << std::endl;
    std::cout << "Leave field empty to keep current value" << std::endl;

    std::string input;
    std::cin.ignore(); // Clear buffer

    std::cout << "First Name [" << student->getFirstName() << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) student->setFirstName(input);

    std::cout << "Last Name [" << student->getLastName() << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) student->setLastName(input);

    std::cout << "Home Teacher [" << student->getHomeTeacher() << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) student->setHomeTeacher(input);
        else student->setHomeTeacher("");

    std::cout << "Personal Instructor [" << student->getPersonalInstructor() << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) student->setPersonalInstructor(input);
        else student->setPersonalInstructor("");

    if (db.updateStudent(*student)) {
        std::cout << "Student updated successfully!" << std::endl;
    }
    else {
        std::cout << "Error updating student!" << std::endl;
    }
}

void LearningCenterManager::removeStudent() {
    std::string id;
    std::cout << "Enter Student ID to remove: ";
    std::cin >> id;

    auto student = db.getStudent(id);
    if (!student) {
        std::cout << "Student not found!" << std::endl;
        return;
    }

    std::cout << "\n--- Student to Remove ---" << std::endl;
    student->displayInfo();

    char confirm;
    std::cout << "\nAre you sure you want to remove this student? (y/N): ";
    std::cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        if (db.removeStudent(id)) {
            std::cout << "Student removed successfully!" << std::endl;
        }
        else {
            std::cout << "Error removing student!" << std::endl;
        }
    }
    else {
        std::cout << "Operation cancelled." << std::endl;
    }
}

void LearningCenterManager::createAssignment() {
    std::string title, description, studentId, subject;
    int dueDays;

    std::cout << "\n--- Create New Assignment ---" << std::endl;
    std::cout << "Student ID: ";
    std::cin >> studentId;

    // Verify student exists
    if (!db.getStudent(studentId)) {
        std::cout << "Error: Student not found!" << std::endl;
        return;
    }

    std::cin.ignore(); // Clear buffer
    std::cout << "Assignment Title: ";
    std::getline(std::cin, title);
    std::cout << "Description: ";
    std::getline(std::cin, description);
    std::cout << "Subject: ";
    std::getline(std::cin, subject);
    std::cout << "Due in how many days? ";
    std::cin >> dueDays;

    Assignment assignment(title, description, studentId, subject, dueDays);

    if (db.addAssignment(assignment)) {
        std::cout << "Assignment created successfully! ID: " << assignment.getId() << std::endl;
    }
    else {
        std::cout << "Error: Assignment already exists or database error!" << std::endl;
    }
}

void LearningCenterManager::viewAssignment() {
    std::string id;
    std::cout << "Enter Assignment ID: ";
    std::cin >> id;

    auto assignment = db.getAssignment(id);
    if (assignment) {
        std::cout << "\n--- Assignment Details ---" << std::endl;
        assignment->displayInfo();
    }
    else {
        std::cout << "Assignment not found!" << std::endl;
    }
}

void LearningCenterManager::listAllAssignments() {
    auto assignments = db.getAllAssignments();
    if (assignments.empty()) {
        std::cout << "No assignments found." << std::endl;
        return;
    }

    std::cout << "\n--- All Assignments ---" << std::endl;
    for (const auto& assignment : assignments) {
        std::cout << "ID: " << assignment.getId() << " | Title: " << assignment.getTitle()
            << " | Student: " << assignment.getStudentId()
            << " | Status: " << assignment.getStatusString() << std::endl;
    }
}

void LearningCenterManager::updateAssignmentStatus() {
    std::string id;
    std::cout << "Enter Assignment ID: ";
    std::cin >> id;

    auto assignment = db.getAssignment(id);
    if (!assignment) {
        std::cout << "Assignment not found!" << std::endl;
        return;
    }

    std::cout << "\n--- Current Assignment ---" << std::endl;
    std::cout << "Title: " << assignment->getTitle() << std::endl;
    std::cout << "Current Status: " << assignment->getStatusString() << std::endl;

    std::cout << "\n--- Select New Status ---" << std::endl;
    std::cout << "1. Pending" << std::endl;
    std::cout << "2. In Progress" << std::endl;
    std::cout << "3. Submitted" << std::endl;
    std::cout << "Enter choice: ";

    int choice;
    std::cin >> choice;

    AssignmentStatus newStatus;
    switch (choice) {
    case 1: newStatus = AssignmentStatus::PENDING; break;
    case 2: newStatus = AssignmentStatus::IN_PROGRESS; break;
    case 3: newStatus = AssignmentStatus::SUBMITTED; break;
    default:
        std::cout << "Invalid choice!" << std::endl;
        return;
    }

    assignment->setStatus(newStatus);

    if (db.updateAssignment(*assignment)) {
        std::cout << "Assignment status updated successfully!" << std::endl;
    }
    else {
        std::cout << "Error updating assignment status!" << std::endl;
    }
}


void LearningCenterManager::viewStudentAssignments() {
    std::string studentId;
    std::cout << "Enter Student ID: ";
    std::cin >> studentId;

    auto assignments = db.getAssignmentsByStudent(studentId);
    if (assignments.empty()) {
        std::cout << "No assignments found for this student." << std::endl;
        return;
    }

    auto student = db.getStudent(studentId);
    std::cout << "\n--- Assignments for " << (student ? student->getFullName() : studentId) << " ---" << std::endl;

    for (const auto& assignment : assignments) {
        std::cout << "\nID: " << assignment.getId() << std::endl;
        std::cout << "Title: " << assignment.getTitle() << std::endl;
        std::cout << "Subject: " << assignment.getSubject() << std::endl;
        std::cout << "Status: " << assignment.getStatusString() << std::endl;
        std::cout << "------------------------" << std::endl;
    }
}

void LearningCenterManager::generateReports() {
    std::cout << "\n--- Reports Menu ---" << std::endl;
    std::cout << "1. Student Summary Report" << std::endl;
    std::cout << "2. Assignment Status Report" << std::endl;
    std::cout << "3. Back to Main Menu" << std::endl;
    std::cout << "Enter your choice: ";

    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1: {
        auto students = db.getAllStudents();
        std::cout << "\n--- Student Summary Report ---" << std::endl;
        std::cout << "Total Students: " << students.size() << std::endl;
        for (const auto& student : students) {
            auto assignments = db.getAssignmentsByStudent(student.getId());
            std::cout << student.getFullName() << " - " << assignments.size() << " assignments" << std::endl;
        }
        break;
    }
    case 2: {
        auto assignments = db.getAllAssignments();
        std::cout << "\n--- Assignment Status Report ---" << std::endl;
        int pending = 0, inProgress = 0, submitted = 0;

        for (const auto& assignment : assignments) {
            switch (assignment.getStatus()) {
            case AssignmentStatus::PENDING: pending++; break;
            case AssignmentStatus::IN_PROGRESS: inProgress++; break;
            case AssignmentStatus::SUBMITTED: submitted++; break;
            }
        }

        std::cout << "Pending: " << pending << std::endl;
        std::cout << "In Progress: " << inProgress << std::endl;
        std::cout << "Submitted: " << submitted << std::endl;
        std::cout << "Total: " << assignments.size() << std::endl;
        break;
    }
    
    case 3:
        return;
    default:
        std::cout << "Invalid choice!" << std::endl;
    }
}

void LearningCenterManager::run() {
    int choice;

    while (true) {
        displayMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please enter a number." << std::endl;
            continue;
        }

        switch (choice) {
        case 1: // Student Management
            while (true) {
                displayStudentMenu();
                int studentChoice;
                std::cin >> studentChoice;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input! Please enter a number." << std::endl;
                    continue;
                }

                switch (studentChoice) {
                case 1: addStudent(); break;
                case 2: viewStudent(); break;
                case 3: listAllStudents(); break;
                case 4: updateStudent(); break;
                case 5: removeStudent(); break;
                case 6: goto mainMenu;
                default: std::cout << "Invalid choice!" << std::endl;
                }
            }
        mainMenu:
            break;

        case 2: // Assignment Management
            while (true) {
                displayAssignmentMenu();
                int assignChoice;
                std::cin >> assignChoice;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input! Please enter a number." << std::endl;
                    continue;
                }

                switch (assignChoice) {
                case 1: createAssignment(); break;
                case 2: viewAssignment(); break;
                case 3: listAllAssignments(); break;
                case 4: updateAssignmentStatus(); break;
                case 5: viewStudentAssignments(); break;
                case 6: goto mainMenu2;
                default: std::cout << "Invalid choice!" << std::endl;
                }
            }
        mainMenu2:
            break;

        case 3: // Reports
            generateReports();
            break;

        case 4: // Exit
            std::cout << "Goodbye!" << std::endl;
            return;

        default:
            std::cout << "Invalid choice! Please try again." << std::endl;
        }
    }
}