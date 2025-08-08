#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <ctime>
#include <bsoncxx/document/view.hpp>
#include <bsoncxx/document/value.hpp>

class Student {
private:
    std::string id;
    std::string firstName;
    std::string lastName;
    std::string email;
    std::string homeTeacher;
    std::string personalInstructor;
    std::time_t enrollmentDate;

public:
    // Constructors
    Student(const std::string& firstName, const std::string& lastName,
        const std::string& homeTeacher, const std::string& instructor);

    Student(const bsoncxx::document::view& doc);

    // BSON conversion
    bsoncxx::document::value toBSON() const;

    // Getters
    std::string getId() const;
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getFullName() const;
    std::string getHomeTeacher() const;
    std::string getPersonalInstructor() const;
    std::time_t getEnrollmentDate() const;

    // Setters
    void setFirstName(const std::string& name);
    void setLastName(const std::string& name);
    void setHomeTeacher(const std::string& teacher);
    void setPersonalInstructor(const std::string& instructor);

    // Display
    void displayInfo() const;
};

#endif // STUDENT_H