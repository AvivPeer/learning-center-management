#include "Assignment.h"
#include <iostream>
#include <iomanip>
#include <bsoncxx/builder/stream/document.hpp>

using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;

std::string Assignment::statusToString(AssignmentStatus status) {
    switch (status) {
    case AssignmentStatus::PENDING: return "PENDING";
    case AssignmentStatus::IN_PROGRESS: return "IN_PROGRESS";
    case AssignmentStatus::SUBMITTED: return "SUBMITTED";
    default: return "PENDING";
    }
}
//Converting string to Enum Status
AssignmentStatus Assignment::stringToStatus(const std::string& str) {
    if (str == "IN_PROGRESS") return AssignmentStatus::IN_PROGRESS;
    if (str == "SUBMITTED") return AssignmentStatus::SUBMITTED;
    return AssignmentStatus::PENDING;
}
//Constructor for assignment 
Assignment::Assignment(const std::string& title, const std::string& description,
    const std::string& studentId, const std::string& subject,
    int dueDaysFromNow)
    : title(title), description(description), studentId(studentId),
    subject(subject), status(AssignmentStatus::PENDING) {

    // Generate random assign id
    id = "ASSIGN_" + std::to_string(std::hash<std::string>{}(title + studentId) % 100000);

    createdDate = std::time(nullptr);
    dueDate = createdDate + (dueDaysFromNow * 24 * 60 * 60);
}

//Constructor , read from mongodb
Assignment::Assignment(const bsoncxx::document::view& doc) {
    if (doc["id"]) id = std::string(doc["id"].get_string().value);
    if (doc["title"]) title = std::string(doc["title"].get_string().value);
    if (doc["description"]) description = std::string(doc["description"].get_string().value);
    if (doc["studentId"]) studentId = std::string(doc["studentId"].get_string().value);
    if (doc["subject"]) subject = std::string(doc["subject"].get_string().value);
    if (doc["createdDate"]) createdDate = doc["createdDate"].get_int64().value;
    if (doc["dueDate"]) dueDate = doc["dueDate"].get_int64().value;
    if (doc["status"]) status = stringToStatus(std::string(doc["status"].get_string().value));
    if (doc["feedback"]) feedback = std::string(doc["feedback"].get_string().value);
}
//Constructing BSON document to store in MongoDB
bsoncxx::document::value Assignment::toBSON() const {
    return document{}
        << "id" << id
        << "title" << title
        << "description" << description
        << "studentId" << studentId
        << "subject" << subject
        << "createdDate" << static_cast<int64_t>(createdDate)
        << "dueDate" << static_cast<int64_t>(dueDate)
        << "status" << statusToString(status)
        << "feedback" << feedback
        << finalize;
}

// Getters
std::string Assignment::getId() const { return id; }
std::string Assignment::getTitle() const { return title; }
std::string Assignment::getDescription() const { return description; }
std::string Assignment::getStudentId() const { return studentId; }
std::string Assignment::getSubject() const { return subject; }
std::time_t Assignment::getCreatedDate() const { return createdDate; }
std::time_t Assignment::getDueDate() const { return dueDate; }
AssignmentStatus Assignment::getStatus() const { return status; }
std::string Assignment::getFeedback() const { return feedback; }

// Setters
void Assignment::setTitle(const std::string& t) { title = t; }
void Assignment::setDescription(const std::string& desc) { description = desc; }
void Assignment::setStatus(AssignmentStatus s) { status = s; }
void Assignment::setFeedback(const std::string& f) { feedback = f; }

//Returns the status of an assignment
std::string Assignment::getStatusString() const {
    switch (status) {
    case AssignmentStatus::PENDING: return "Pending";
    case AssignmentStatus::IN_PROGRESS: return "In Progress";
    case AssignmentStatus::SUBMITTED: return "Submitted";
    default: return "Unknown";
    }
}

//Display the information of a specfific assignment
void Assignment::displayInfo() const {
    std::cout << "Assignment ID: " << id << std::endl;
    std::cout << "Title: " << title << std::endl;
    std::cout << "Subject: " << subject << std::endl;
    std::cout << "Student ID: " << studentId << std::endl;
    std::cout << "Description: " << description << std::endl;
    std::cout << "Status: " << getStatusString() << std::endl;

    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M", std::localtime(&createdDate));
    std::cout << "Created: " << buffer << std::endl;

    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M", std::localtime(&dueDate));
    std::cout << "Due Date: " << buffer << std::endl;


    if (!feedback.empty()) {
        std::cout << "Feedback: " << feedback << std::endl;
    }
}