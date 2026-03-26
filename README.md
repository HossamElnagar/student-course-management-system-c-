# 🎓 Student Course Management System

A C++ console application to manage students and their enrolled courses.  
Built as an individual assignment applying **OOP**, **STL**, and core C++ concepts.

---

## 📋 Table of Contents

- [Features](#features)
- [How to Compile & Run](#how-to-compile--run)
- [Menu Options](#menu-options)
- [Project Structure](#project-structure)
- [OOP Design](#oop-design)
- [STL Usage](#stl-usage)
- [Constraints & Validation](#constraints--validation)
- [Libraries Used](#libraries-used)

---

## ✨ Features

- Add students with unique ID, name, and GPA
- Remove students efficiently using swap-with-last `O(1)`
- Search for a student by ID
- Display all registered students
- Enroll a student in a course (no duplicates allowed)
- View all courses of a specific student
- Sort students by GPA (descending) without modifying original order
- Full input validation — program never crashes on bad input

---

## ⚙️ How to Compile & Run

**Requirements:** Any C++17 compiler (g++, clang++, MSVC)

```bash
# Compile
g++ -std=c++17 -o student_system main.cpp

# Run
./student_system
```

> On Windows:
> ```bash
> g++ -std=c++17 -o student_system.exe main.cpp
> student_system.exe
> ```

---

## 📌 Menu Options

```
=========================================
   Student Course Management System
=========================================

--- Menu ---
1. Add Student
2. Remove Student
3. Search Student
4. Display All Students
5. Enroll Student in Course
6. Show Student Courses
7. Sort Students by GPA
8. Exit
```

### Example Usage

```
Choice: 1
Enter Student ID: 1001
Enter Name: Ali
Enter GPA (0.0 - 4.0): 3.5
  [+] Student added successfully.

Choice: 5
Enter Student ID: 1001
Enter Course Name: Data Structures
  [+] Enrolled in "Data Structures" successfully.
```

---

## 🗂️ Project Structure

```
main.cpp
│
├── class Person            ← Base class
│     └── string name
│
├── class Student           ← Derived from Person
│     ├── int id
│     ├── double gpa
│     └── vector<string> courses
│
└── class StudentManager    ← System controller
      ├── vector<Student> students
      └── run() / menu loop
```

---

## 🏛️ OOP Design

| Concept | Implementation |
|---|---|
| **Inheritance** | `Student` inherits from `Person` via `public` inheritance |
| **Encapsulation** | All attributes are `private` with getters/setters |
| **Polymorphism** | `display()` is `virtual` — calls correct version at runtime |
| **Virtual Destructor** | `~Person()` is `virtual` to prevent memory leaks |
| **Constructors** | Default + parameterised constructors in both classes |

---

## 📦 STL Usage

| Container / Algorithm | Where Used | Purpose |
|---|---|---|
| `vector<Student>` | `StudentManager` | Stores all students dynamically |
| `vector<string>` | `Student::courses` | Stores enrolled courses per student |
| Bubble Sort (manual) | `sortByGpa()` | Sorts a **copy** — original order preserved |

---

## 🛡️ Constraints & Validation

- **Unique ID** — duplicate IDs are rejected immediately
- **GPA range** — must be between `0.0` and `4.0`; re-prompted on invalid input
- **No duplicate courses** — linear scan blocks re-enrollment in same course
- **Empty course name** — rejected with an error message
- **Invalid `cin` input** — buffer flushed with `while(cin.get(c) && c != '\n')` — no crash

---

## 📚 Libraries Used

```cpp
#include <iostream>   // Input / Output
#include <vector>     // STL container
#include <string>     // String handling
```

> No `<map>`, `<set>`, `<algorithm>`, or `<limits>` used.

---

## 📝 Assignment Requirements Coverage

| Requirement | Status |
|---|---|
| Classes + Encapsulation | ✅ |
| Inheritance (Person → Student) | ✅ |
| Virtual functions | ✅ |
| At least 2 STL containers | ✅ `vector<Student>` + `vector<string>` |
| Sorting algorithm | ✅ Bubble Sort |
| Unique ID validation | ✅ |
| GPA range validation | ✅ |
| No duplicate courses | ✅ |
| Invalid input handling | ✅ |
