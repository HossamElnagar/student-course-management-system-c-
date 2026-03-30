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
- Remove students by ID
- Search for a student using `find_if()` (STL algorithm)
- Display all registered students
- Enroll a student in a course — duplicates blocked automatically via `set`
- View all courses of a specific student
- Sort students by GPA using `sort()` (STL algorithm)
- **Bonus:** Count students with GPA ≥ 3.0 using `count_if()` (STL algorithm)

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
 Student System
1.Add  2.Remove  3.Search  4.Display
5.Enroll  6.Courses  7.Sort  8.Count(GPA>=3)  0.Exit
Choice:
```

### Example Usage

```
Choice: 1
ID   : 1001
Name : Ali
GPA  : 3.5
Added.

Choice: 5
ID   : 1001
Course: Data Structures
Enrolled.

Choice: 8
  Students with GPA >= 3.0 : 1
```

---

## 🗂️ Project Structure

```
main.cpp
│
├── class Person              ← Base class
│     └── string name
│
├── class Student             ← Derived from Person
│     ├── int id
│     ├── double gpa
│     └── set<string> courses
│
└── class StudentSystem       ← System controller
      ├── vector<Student> students
      ├── map<int,int> index
      └── menu loop in main()
```

---

## 🏛️ OOP Design

| Concept | Implementation |
|---|---|
| **Inheritance** | `Student` inherits from `Person` via `public` inheritance |
| **Encapsulation** | All attributes are `private` with getters |
| **Polymorphism** | `virtual ~Person()` — correct destructor called at runtime |
| **Virtual Destructor** | Prevents memory leak when deleting via `Person*` |
| **Constructor** | `Student(int, string, double)` passes `name` to `Person` |

---

## 📦 STL Usage

| Container / Algorithm | Where Used | Purpose |
|---|---|---|
| `vector<Student>` | `StudentSystem` | Stores all students in order |
| `map<int, int>` | `StudentSystem::index` | Maps ID to vector index for O(log n) lookup |
| `set<string>` | `Student::courses` | No duplicates, auto-sorted |
| `sort()` | `sortByGpa()` | Sorts students ascending by GPA |
| `find_if()` | `searchStudent()` | Searches students by ID |
| `count_if()` | `countHighGpa()` | Counts students with GPA >= 3.0 |

---

## 🛡️ Constraints & Validation

- **Unique ID** — `map::count()` rejects duplicate IDs immediately
- **GPA range** — `do { } while (v < 0 || v > 4)` re-prompts until valid
- **No duplicate courses** — `set<string>` blocks duplicates automatically
- **Not found handling** — clear message shown when ID does not exist

---

## 📚 Libraries Used

```cpp
#include <iostream>    // Input / Output
#include <vector>      // STL container
#include <map>         // STL container
#include <set>         // STL container
#include <algorithm>   // sort(), find_if(), count_if()
#include <string>      // String handling
#include <utility>     // pair / move helpers
```

---

## 📝 Assignment Requirements Coverage

| Requirement | Status |
|---|---|
| Classes + Encapsulation | ✅ |
| Inheritance (Person → Student) | ✅ |
| Virtual Destructor | ✅ |
| At least 2 STL containers | ✅ `vector` + `map` + `set` (3 containers) |
| STL Algorithms | ✅ `sort()` + `find_if()` + `count_if()` |
| Unique ID validation | ✅ |
| GPA range validation | ✅ |
| No duplicate courses | ✅ via `set<string>` |
| Invalid input handling | ✅ |
