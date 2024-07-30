# Rocket Chat Project Documentation

Welcome to the ChatApp project! This project is a simple chat application built using C++. The main goals of the project are to provide a secure and efficient chat platform, leveraging modern C++ libraries and technologies.

## Features

### User Registration and Authentication
   - Users can register with inline validation and securely log in and log out.

### Message Handling
   - Currently in development, using cppzmq for message handling.

### Data Storage
   - User data and messages are stored in an SQLite database.

### User Generation for Testing
   - Generates test users using XML with the pugixml library.

### Unit Testing
   - Comprehensive unit tests written using gtest.

### Test User Generation
   - Uses yaml-cpp for generating test users.

### Build System
   - Built with CMake for easy compilation and management.

## Libraries and Technologies

### Core Language
- **C++:** Core language for the project.

### Web Frameworks and Libraries
- **Pistache:** For handling HTTP requests.
- **HTMX:** For frontend communication and dynamic content updates.

### Messaging
- **cppzmq:** For message handling.

### Database
- **SQLite:** Database for storing user data and messages.

### XML Processing
- **pugixml:** For parsing and generating XML data.

### Testing Framework
- **gtest:** For unit testing the application.

### Configuration and User Generation
- **yaml-cpp:** For handling YAML configuration files and generating test users.

### Build System
- **CMake:** Build system for managing the project build process.

# ChatApp Project Directory Structure
```
ChatApp/
├── CMakeLists.txt     
├── db/                   
├── frontend/                 
│   ├── chatsite         
│   ├── loginpage  
├── src/             
│   ├── CmakeLists.txt     
│   ├── main.cpp       
│   ├── servervices.cpp/          
│   ├── user.cpp/          
│   ├── logs.cpp/        
│   ├── generator.cpp/          
│   ├── user_generator.cpp/           
├── tests/               
│   ├── user_tests.cpp         
│   ├── CmakeLists.txt  
├── CMakeLists.txt     
└── README.md
```

 ## Prerequisites

- C++17 or higher
- CMake 3.10 or higher
- SQLite
- Pistache
- HTMX
- cppzmq
- pugixml
- gtest
- yaml-cpp
