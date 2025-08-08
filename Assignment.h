#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <string>
#include <ctime>
#include <bsoncxx/document/view.hpp>
#include <bsoncxx/document/value.hpp>

enum class AssignmentStatus {
    PENDING,
    IN_PROGRESS,
    SUBMITTED,
};

class Assignment {
private:
    std::string id;
    std::string title;
    std::string description;
    std::string studentId;
    std::string subject;
    std::time_t createdDate;
    std::time_t dueDate;
    AssignmentStatus status;
    std::string feedback;

    static std::string statusToString(AssignmentStatus status);
    static AssignmentStatus stringToStatus(const std::string& str);

public:
    // Constructors
    Assignment(const std::string& title, const std::string& description,
        const std::string& studentId, const std::string& subject,
        int dueDaysFromNow = 7);

    Assignment(const bsoncxx::document::view& doc);

    // BSON conversion
    bsoncxx::document::value toBSON() const;

    // Getters
    std::string getId() const;
    std::string getTitle() const;
    std::string getDescription() const;
    std::string getStudentId() const;
    std::string getSubject() const;
    std::time_t getCreatedDate() const;
    std::time_t getDueDate() const;
    AssignmentStatus getStatus() const;
    std::string getFeedback() const;

    // Setters
    void setTitle(const std::string& t);
    void setDescription(const std::string& desc);
    void setStatus(AssignmentStatus s);
    void setFeedback(const std::string& f);

    // Utility
    std::string getStatusString() const;
    void displayInfo() const;
};

#endif // ASSIGNMENT_H