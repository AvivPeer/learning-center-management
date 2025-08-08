# Learning Center Management System

A comprehensive C++ application for managing students and assignments in a learning center environment, built with MongoDB integration and modern object-oriented design.

## 🎯 Features

### Student Management
- **Add Students**: Register new students with personal details and instructor assignments
- **View & Search**: Look up individual student information by ID
- **Update Records**: Modify student information including name, home teacher, and personal instructor
- **Remove Students**: Delete student records with confirmation prompts
- **List All**: Display comprehensive student roster

### Assignment Management
- **Create Assignments**: Generate new assignments with titles, descriptions, subjects, and due dates
- **Track Progress**: Monitor assignment status (Pending, In Progress, Submitted)
- **Update Status**: Change assignment completion status with feedback options
- **Student View**: Display all assignments for a specific student
- **Assignment Details**: View complete assignment information including deadlines

### Reporting System
- **Student Summary**: Overview of all students and their assignment counts
- **Status Reports**: Breakdown of assignment completion statistics
- **Real-time Analytics**: Live data from MongoDB database

## 🛠 Technical Architecture

### Core Technologies
- **Language**: C++17
- **Database**: MongoDB with mongocxx driver
- **Architecture**: Object-Oriented Design with clear separation of concerns

### Key Components
- **LearningCenterManager**: Main application controller and user interface
- **DatabaseManager**: MongoDB connection and CRUD operations handler
- **Student Class**: Student entity with BSON serialization
- **Assignment Class**: Assignment entity with status management and date tracking

### Database Design
- **MongoDB Collections**: Separate collections for students and assignments
- **BSON Integration**: Native MongoDB document format support
- **Data Validation**: Input validation and error handling throughout

## 🚀 Getting Started

### Prerequisites
```bash
# MongoDB C++ Driver
sudo apt-get install libmongocxx-dev libbsoncxx-dev

# MongoDB Server
sudo apt-get install mongodb-org
```

### Installation
```bash
# Clone the repository
git clone https://github.com/avivpeer/learning-center-management.git
cd learning-center-management

# Compile the project
g++ -std=c++17 *.cpp -o learning_center \
    $(pkg-config --cflags --libs libmongocxx)

# Run the application
./learning_center
```

### Database Configuration
The application connects to MongoDB using:
- **Default**: `mongodb://localhost:27017`
- **Database**: `learning_center`
- **Collections**: `students`, `assignments`

## 📁 Project Structure
```
learning-center-management/
├── main.cpp                     # Application entry point
├── LearningCenterManager.h/.cpp # Main controller and UI
├── DatabaseManager.h/.cpp       # MongoDB operations
├── Student.h/.cpp              # Student entity class
├── Assignment.h/.cpp           # Assignment entity class
└── README.md                   # This file
```

## 🎮 Usage Example

```cpp
// Creating a new student
Student student("John", "Doe", "Mrs. Smith", "Mr. Johnson");

// Creating an assignment
Assignment assignment("Math Homework", "Complete exercises 1-20", 
                     "John_Doe", "Mathematics", 7);

// Database operations
DatabaseManager db;
db.addStudent(student);
db.addAssignment(assignment);
```

## 🔧 Key Features Implemented

### Error Handling
- MongoDB connection validation
- Input sanitization and validation
- Graceful error recovery with user feedback

### Data Persistence
- Automatic BSON serialization/deserialization
- Robust database connection management
- Data integrity validation

### User Experience
- Intuitive menu-driven interface
- Clear feedback messages
- Confirmation prompts for destructive operations

## 📊 Database Schema

### Students Collection
```json
{
  "id": "John_Doe",
  "firstName": "John",
  "lastName": "Doe",
  "homeTeacher": "Mrs. Smith",
  "personalInstructor": "Mr. Johnson",
  "enrollmentDate": 1677123456
}
```

### Assignments Collection
```json
{
  "id": "ASSIGN_12345",
  "title": "Math Homework",
  "description": "Complete exercises 1-20",
  "studentId": "John_Doe",
  "subject": "Mathematics",
  "status": "PENDING",
  "createdDate": 1677123456,
  "dueDate": 1677727456,
  "feedback": ""
}
```

## 🚀 Future Enhancements
- [ ] Web-based user interface
- [ ] Grade tracking and GPA calculation
- [ ] Email notifications for due assignments
- [ ] Advanced reporting with data visualization
- [ ] Multi-user authentication system
- [ ] Export functionality (PDF reports, CSV data)

## 🤝 Contributing
1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit changes (`git commit -m 'Add AmazingFeature'`)
4. Push to branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📝 License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 👨‍💻 Author
**Aviv Peer**
- LinkedIn: [aviv-peer-6225a0188](https://www.linkedin.com/in/aviv-peer-6225a0188)
- Email: aviv.per@gmail.com

## 🙏 Acknowledgments
- MongoDB team for excellent C++ driver documentation
- Braude College Software Engineering program
- Learning center management domain expertise from teaching experience
