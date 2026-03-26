#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ============================================================
//  Base class: Person  (Inheritance requirement)
// ============================================================
class Person {
protected:
    string name;

public:
    Person() : name("") {}
    explicit Person(const string& n) : name(n) {}

    string getName() const { return name; }
    void   setName(const string& n) { name = n; }

    virtual void display() const {
        cout << "Name: " << name;
    }

    virtual ~Person() {}
};

// ============================================================
//  Derived class: Student
// ============================================================
class Student : public Person {
private:
    int    id;
    double gpa;
    vector<string> courses;

public:
    Student() : Person(), id(0), gpa(0.0) {}

    Student(int id, const string& name, double gpa)
        : Person(name), id(id), gpa(gpa) {}

    int    getId()  const { return id;  }
    double getGpa() const { return gpa; }
    const vector<string>& getCourses() const { return courses; }

    void setGpa(double g) { gpa = g; }

    // Returns false if course already exists
    bool enrollCourse(const string& course) {
        for (int i = 0; i < (int)courses.size(); i++) {
            if (courses[i] == course)
                return false;
        }
        courses.push_back(course);
        return true;
    }

    void display() const override {
        cout << "ID: "      << id
             << " | Name: " << name
             << " | GPA: "  << gpa;
    }

    void showCourses() const {
        if (courses.empty()) {
            cout << "  (no courses enrolled)\n";
            return;
        }
        for (int i = 0; i < (int)courses.size(); i++)
            cout << "  - " << courses[i] << "\n";
    }
};

// ============================================================
//  StudentManager
// ============================================================
class StudentManager {
private:
    vector<Student> students;

    // Find index by ID, returns -1 if not found
    int findIndex(int id) const {
        for (int i = 0; i < (int)students.size(); i++) {
            if (students[i].getId() == id)
                return i;
        }
        return -1;
    }

    // Input helpers
    static int    readInt(const string& prompt);
    static double readDouble(const string& prompt, double lo, double hi);
    static string readLine(const string& prompt);

public:
    void addStudent();
    void removeStudent();
    void searchStudent();
    void displayAll() const;
    void enrollInCourse();
    void showStudentCourses();
    void sortByGpa();

    void run();
};

// ============================================================
//  Input helpers
// ============================================================
int StudentManager::readInt(const string& prompt) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val) break;
        cout << "  [!] Invalid input. Please enter an integer.\n";
        cin.clear();
        char c;
        while (cin.get(c) && c != '\n') {}
    }
    char c;
    while (cin.get(c) && c != '\n') {}
    return val;
}

double StudentManager::readDouble(const string& prompt, double lo, double hi) {
    double val;
    while (true) {
        cout << prompt;
        bool ok = (bool)(cin >> val);
        char c;
        while (cin.get(c) && c != '\n') {}
        if (ok && val >= lo && val <= hi) break;
        cout << "  [!] Invalid input. Value must be between "
             << lo << " and " << hi << ".\n";
        cin.clear();
    }
    return val;
}

string StudentManager::readLine(const string& prompt) {
    cout << prompt;
    string line;
    getline(cin, line);
    return line;
}

// ============================================================
//  1. Add Student
// ============================================================
void StudentManager::addStudent() {
    int id = readInt("Enter Student ID: ");

    if (findIndex(id) != -1) {
        cout << "  [!] A student with ID " << id << " already exists.\n";
        return;
    }

    string name = readLine("Enter Name: ");
    double gpa  = readDouble("Enter GPA (0.0 - 4.0): ", 0.0, 4.0);

    students.push_back(Student(id, name, gpa));
    cout << "  [+] Student added successfully.\n";
}

// ============================================================
//  2. Remove Student
// ============================================================
void StudentManager::removeStudent() {
    int id  = readInt("Enter Student ID to remove: ");
    int idx = findIndex(id);

    if (idx == -1) {
        cout << "  [!] Student with ID " << id << " not found.\n";
        return;
    }

    // Swap with last then pop (only if not already the last)
    if (idx != (int)students.size() - 1)
        students[idx] = students[students.size() - 1];
    students.pop_back();
    cout << "  [-] Student removed successfully.\n";
}

// ============================================================
//  3. Search Student
// ============================================================
void StudentManager::searchStudent() {
    int id  = readInt("Enter Student ID to search: ");
    int idx = findIndex(id);

    if (idx == -1) {
        cout << "  [!] Student not found.\n";
        return;
    }

    cout << "  [Found] ";
    students[idx].display();
    cout << "\n";
}

// ============================================================
//  4. Display All Students
// ============================================================
void StudentManager::displayAll() const {
    if (students.empty()) {
        cout << "  (no students in the system)\n";
        return;
    }
    cout << "\n--- All Students ---\n";
    for (int i = 0; i < (int)students.size(); i++) {
        students[i].display();
        cout << "\n";
    }
}

// ============================================================
//  5. Enroll Student in Course
// ============================================================
void StudentManager::enrollInCourse() {
    int id  = readInt("Enter Student ID: ");
    int idx = findIndex(id);

    if (idx == -1) {
        cout << "  [!] Student with ID " << id << " not found.\n";
        return;
    }

    string course = readLine("Enter Course Name: ");
    if (course.empty()) {
        cout << "  [!] Course name cannot be empty.\n";
        return;
    }

    bool added = students[idx].enrollCourse(course);
    if (added)
        cout << "  [+] Enrolled in \"" << course << "\" successfully.\n";
    else
        cout << "  [!] Student is already enrolled in \"" << course << "\".\n";
}

// ============================================================
//  6. Show Student Courses
// ============================================================
void StudentManager::showStudentCourses() {
    int id  = readInt("Enter Student ID: ");
    int idx = findIndex(id);

    if (idx == -1) {
        cout << "  [!] Student with ID " << id << " not found.\n";
        return;
    }

    cout << "  Courses for " << students[idx].getName() << ":\n";
    students[idx].showCourses();
}

// ============================================================
//  7. Sort Students by GPA  (Bubble Sort)
// ============================================================
void StudentManager::sortByGpa() {
    if (students.empty()) {
        cout << "  (no students in the system)\n";
        return;
    }

    // Work on a copy so the original order is preserved
    vector<Student> sorted = students;
    int n = (int)sorted.size();

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (sorted[j].getGpa() < sorted[j + 1].getGpa()) {
                Student temp   = sorted[j];
                sorted[j]      = sorted[j + 1];
                sorted[j + 1]  = temp;
            }
        }
    }

    cout << "\n--- Students Sorted by GPA (High to Low) ---\n";
    for (int i = 0; i < n; i++) {
        sorted[i].display();
        cout << "\n";
    }
}

// ============================================================
//  Main menu loop
// ============================================================
void StudentManager::run() {
    cout << "=========================================\n";
    cout << "   Student Course Management System\n";
    cout << "=========================================\n";

    while (true) {
        cout << "\n--- Menu ---\n"
             << "1. Add Student\n"
             << "2. Remove Student\n"
             << "3. Search Student\n"
             << "4. Display All Students\n"
             << "5. Enroll Student in Course\n"
             << "6. Show Student Courses\n"
             << "7. Sort Students by GPA\n"
             << "8. Exit\n"
             << "Choice: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            char c;
            while (cin.get(c) && c != '\n') {}
            cout << "  [!] Please enter a number between 1 and 8.\n";
            continue;
        }
        char c;
        while (cin.get(c) && c != '\n') {}

        cout << "\n";
        switch (choice) {
            case 1: addStudent();         break;
            case 2: removeStudent();      break;
            case 3: searchStudent();      break;
            case 4: displayAll();         break;
            case 5: enrollInCourse();     break;
            case 6: showStudentCourses(); break;
            case 7: sortByGpa();          break;
            case 8:
                cout << "Goodbye!\n";
                return;
            default:
                cout << "  [!] Invalid choice. Please enter 1-8.\n";
        }
    }
}

// ============================================================
//  Entry point
// ============================================================
int main() {
    StudentManager manager;
    manager.run();
    return 0;
}
