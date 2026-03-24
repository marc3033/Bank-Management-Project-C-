# Bank-Management-Project-C-
A persistent, session-based C++ banking application featuring automated file serialization, nested transaction history tracking, and a robust object-oriented architecture.

This project is meant to be a showcase of my proficiency in professional grade c++.  This project features a multi-user environment with data persistence across application restarts using a custom I/O engine.

Features: 
Session Management:  Utilizes a built in secure login/logout logic flow using pointers to manage active, previous, and future users.  
Data Serialization: Implemented logic to save/load nested std::vector structures to local disk storage.  This allows for saved account data and saved account transaction history between all accounts.
STL Optimization: Implemented saved Accounts using std::vector for continuous memory allocation while using size_t to prevent overflow.

Future Updates:
Transition from local file I/O to a database such as SQL.
Implement Administrative rights for certain users based on a password check.
Implement Atomic Funds Transfer logic.  Specifically focusing on data consistency between accounts in case of an error.

Information: 
Made in C++17 in order to show my understanding of basics and platforms used in companies globally.
Uses Pointers, File I/O, Struct Nesting, OOP, and more.

Tools: Visual Studio / CMake / Git
