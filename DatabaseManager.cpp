#include "DatabaseManager.h"
#include <iostream>
#include <mongocxx/uri.hpp>
#include <mongocxx/exception/exception.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;

//Constructor , connecting to mongodb
DatabaseManager::DatabaseManager(const std::string& connection_string,
    const std::string& db_name)
    : client(mongocxx::uri{ connection_string }), db(client[db_name]),
    students_collection(db["students"]), assignments_collection(db["assignments"]) {
}

bool DatabaseManager::testConnection() {
    try {
       //Testing the connection
        auto result = db.run_command(document{} << "ping" << 1 << finalize);
        return true;
    }
    catch (const mongocxx::exception& e) {
        std::cerr << "MongoDB connection failed: " << e.what() << std::endl;
        return false;
    }
}

// Student operations 
bool DatabaseManager::addStudent(const Student& student) {
    try {
        // Check if student already exists
        auto filter = document{} << "id" << student.getId() << finalize;
        if (students_collection.find_one(filter.view())) {
            return false; // Student already exists
        }

        auto result = students_collection.insert_one(student.toBSON().view());
        return result.has_value();
    }
    catch (const mongocxx::exception& e) {
        std::cerr << "Error adding student: " << e.what() << std::endl;
        return false;
    }
}

std::unique_ptr<Student> DatabaseManager::getStudent(const std::string& id) {
    try {
        auto filter = document{} << "id" << id << finalize;
        auto result = students_collection.find_one(filter.view());

        if (result) {
            return std::make_unique<Student>(result->view());
        }
        return nullptr;
    }
    catch (const mongocxx::exception& e) {
        std::cerr << "Error getting student: " << e.what() << std::endl;
        return nullptr;
    }
}

std::vector<Student> DatabaseManager::getAllStudents() {
    std::vector<Student> students;
    try {
        auto cursor = students_collection.find({});
        for (auto&& doc : cursor) {
            students.emplace_back(doc);
        }
    }
    catch (const mongocxx::exception& e) {
        std::cerr << "Error getting all students: " << e.what() << std::endl;
    }
    return students;
}

bool DatabaseManager::updateStudent(const Student& student) {
    try {
        auto filter = document{} << "id" << student.getId() << finalize;
        auto update = document{} << "$set" << student.toBSON() << finalize;

        auto result = students_collection.update_one(filter.view(), update.view());
        return result && result->modified_count() > 0;
    }
    catch (const mongocxx::exception& e) {
        std::cerr << "Error updating student: " << e.what() << std::endl;
        return false;
    }
}

bool DatabaseManager::removeStudent(const std::string& id) {
    try {
        auto filter = document{} << "id" << id << finalize;
        auto result = students_collection.delete_one(filter.view());
        return result && result->deleted_count() > 0;
    }
    catch (const mongocxx::exception& e) {
        std::cerr << "Error removing student: " << e.what() << std::endl;
        return false;
    }
}

// Assignment operations
bool DatabaseManager::addAssignment(const Assignment& assignment) {
    try {
        // Check if assignment already exists
        auto filter = document{} << "id" << assignment.getId() << finalize;
        if (assignments_collection.find_one(filter.view())) {
            return false; // Assignment already exists
        }

        auto result = assignments_collection.insert_one(assignment.toBSON().view());
        return result.has_value();
    }
    catch (const mongocxx::exception& e) {
        std::cerr << "Error adding assignment: " << e.what() << std::endl;
        return false;
    }
}

std::unique_ptr<Assignment> DatabaseManager::getAssignment(const std::string& id) {
    try {
        auto filter = document{} << "id" << id << finalize;
        auto result = assignments_collection.find_one(filter.view());

        if (result) {
            return std::make_unique<Assignment>(result->view());
        }
        return nullptr;
    }
    catch (const mongocxx::exception& e) {
        std::cerr << "Error getting assignment: " << e.what() << std::endl;
        return nullptr;
    }
}

std::vector<Assignment> DatabaseManager::getAllAssignments() {
    std::vector<Assignment> assignments;
    try {
        auto cursor = assignments_collection.find({});
        for (auto&& doc : cursor) {
            assignments.emplace_back(doc);
        }
    }
    catch (const mongocxx::exception& e) {
        std::cerr << "Error getting all assignments: " << e.what() << std::endl;
    }
    return assignments;
}

std::vector<Assignment> DatabaseManager::getAssignmentsByStudent(const std::string& studentId) {
    std::vector<Assignment> assignments;
    try {
        auto filter = document{} << "studentId" << studentId << finalize;
        auto cursor = assignments_collection.find(filter.view());

        for (auto&& doc : cursor) {
            assignments.emplace_back(doc);
        }
    }
    catch (const mongocxx::exception& e) {
        std::cerr << "Error getting assignments by student: " << e.what() << std::endl;
    }
    return assignments;
}

bool DatabaseManager::updateAssignment(const Assignment& assignment) {
    try {
        auto filter = document{} << "id" << assignment.getId() << finalize;
        auto update = document{} << "$set" << assignment.toBSON() << finalize;

        auto result = assignments_collection.update_one(filter.view(), update.view());
        return result && result->modified_count() > 0;
    }
    catch (const mongocxx::exception& e) {
        std::cerr << "Error updating assignment: " << e.what() << std::endl;
        return false;
    }
}

bool DatabaseManager::removeAssignment(const std::string& id) {
    try {
        auto filter = document{} << "id" << id << finalize;
        auto result = assignments_collection.delete_one(filter.view());
        return result && result->deleted_count() > 0;
    }
    catch (const mongocxx::exception& e) {
        std::cerr << "Error removing assignment: " << e.what() << std::endl;
        return false;
    }
}