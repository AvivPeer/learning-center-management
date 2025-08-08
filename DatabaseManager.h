#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <string>
#include <vector>
#include <memory>
#include <mongocxx/client.hpp>
#include <mongocxx/database.hpp>
#include <mongocxx/collection.hpp>
#include "Student.h"
#include "Assignment.h"

class DatabaseManager {
private:
    mongocxx::client client;
    mongocxx::database db;
    mongocxx::collection students_collection;
    mongocxx::collection assignments_collection;

public:
    // Constructor
    DatabaseManager(const std::string& connection_string = "<YourConnectionString>",
        const std::string& db_name = "learning_center");

    // Connection testing
    bool testConnection();

    // Student operations
    bool addStudent(const Student& student);
    std::unique_ptr<Student> getStudent(const std::string& id);
    std::vector<Student> getAllStudents();
    bool updateStudent(const Student& student);
    bool removeStudent(const std::string& id);

    // Assignment operations
    bool addAssignment(const Assignment& assignment);
    std::unique_ptr<Assignment> getAssignment(const std::string& id);
    std::vector<Assignment> getAllAssignments();
    std::vector<Assignment> getAssignmentsByStudent(const std::string& studentId);
    bool updateAssignment(const Assignment& assignment);
    bool removeAssignment(const std::string& id);
};

#endif // DATABASE_MANAGER_H