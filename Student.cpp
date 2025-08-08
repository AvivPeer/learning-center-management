#include "Student.h"
#include <iostream>
#include <iomanip>
#include <bsoncxx/builder/stream/document.hpp>

using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;

Student::Student(const std::string& firstName, const std::string& lastName,
    const std::string& homeTeacher, const std::string& instructor)
    : firstName(firstName), lastName(lastName), email(email),
    homeTeacher(homeTeacher), personalInstructor(instructor) {

    id = firstName+ "_" + lastName;
    enrollmentDate = std::time(nullptr);
}

Student::Student(const bsoncxx::document::view& doc) {
    if (doc["id"]) id = std::string(doc["id"].get_string().value);
    if (doc["firstName"]) firstName = std::string(doc["firstName"].get_string().value);
    if (doc["lastName"]) lastName = std::string(doc["lastName"].get_string().value);
    if (doc["homeTeacher"]) homeTeacher = std::string(doc["homeTeacher"].get_string().value);
    if (doc["personalInstructor"]) personalInstructor = std::string(doc["personalInstructor"].get_string().value);
    if (doc["enrollmentDate"]) enrollmentDate = doc["enrollmentDate"].get_int64().value;
}

bsoncxx::document::value Student::toBSON() const {
    return document{}
        << "id" << id
        << "firstName" << firstName
        << "lastName" << lastName
        << "homeTeacher" << homeTeacher
        << "personalInstructor" << personalInstructor
        << "enrollmentDate" << static_cast<int64_t>(enrollmentDate)
        << finalize;
}

// Getters
std::string Student::getId() const { return id; }
std::string Student::getFirstName() const { return firstName; }
std::string Student::getLastName() const { return lastName; }
std::string Student::getFullName() const { return firstName + " " + lastName; }
std::string Student::getHomeTeacher() const { return homeTeacher; }
std::string Student::getPersonalInstructor() const { return personalInstructor; }
std::time_t Student::getEnrollmentDate() const { return enrollmentDate; }

// Setters
void Student::setFirstName(const std::string& name) { firstName = name; }
void Student::setLastName(const std::string& name) { lastName = name; }
void Student::setHomeTeacher(const std::string& teacher) { homeTeacher = teacher; }
void Student::setPersonalInstructor(const std::string& instructor) { personalInstructor = instructor; }

void Student::displayInfo() const {
    std::cout << "Student ID: " << id << std::endl;
    std::cout << "Name: " << getFullName() << std::endl;
    std::cout << "Home Teacher: " << homeTeacher << std::endl;
    std::cout << "Personal Instructor: " << personalInstructor << std::endl;

    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", std::localtime(&enrollmentDate));
    std::cout << "Enrollment Date: " << buffer << std::endl;
}