#include <iostream>
#include <exception>
#include <mongocxx/instance.hpp>
#include "LearningCenterManager.h"

int main() {
    try {
        // Initialize the MongoDB driver (required once per application)
        mongocxx::instance instance{};

        std::cout << "===============================================" << std::endl;
        std::cout << "  Welcome to Learning Center Management!" << std::endl;
        std::cout << "===============================================" << std::endl;
        std::cout << "Initializing connection to MongoDB..." << std::endl;

        // Create and run the learning center manager
        LearningCenterManager manager;
        manager.run();

    }
    catch (const std::exception& e) {
        std::cerr << "Application error: " << e.what() << std::endl;
        std::cerr << "Please ensure MongoDB is running on localhost:27017" << std::endl;
        return 1;
    }

    return 0;
}
