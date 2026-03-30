/*
 * Student Course Management System
 * 
 * libraries : iostream, vector, map, set, algorithm, string, utility
 * OOP       : Person (base) -> Student (derived)
 * stl       : vector, map, set  (3 containers)
 * algorithms: sort(), find_if(), count_if()
 */

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <utility>

using namespace std;

//  Base Class   person
class Person {
protected:
    string name;
public:
    Person(const string& n = "") : name(n) {}
    string getName() const { return name; }
    virtual ~Person() {}
};

//  Class  student ( craete student)
class Student : public Person {
    int id;
    double gpa;
    set<string> courses;   // bonus //    set => no duplicates, auto-sorted   
public:
    Student(int i, const string& n, double g) : Person(n), id(i), gpa(g) {}   //i put n inside person 

    int    getId()  const { return id; }
    double getGpa() const { return gpa; }
    const set<string>& getCourses() const { return courses; }

    bool enrollCourse(const string& c) { return courses.insert(c).second; }

    void display() const {
        cout << "  ID: " << id << " | Name: " << name
            << " | GPA: " << gpa << " | Courses: " << courses.size() << endl;
    }
};

//System 
class StudentSystem {
    vector<Student> students;   // stl vector  => ordered list
    map<int, int> index;  //link every Student ID(key) : (index)value   

    void rebuild() {   //اعدة ترتيب بعد الحذف
        index.clear();
        for (int i = 0; i < (int)students.size(); i++)
            index[students[i].getId()] = i;
    }

    Student* find(int id) {
        auto it = index.find(id);
        return it == index.end() ? nullptr : &students[it->second];
    }

    int readId() { int v; cout << "ID : "; cin >> v; return v; }
    double readGpa() {
        double v;
        do { cout << "GPA : "; cin >> v; } while (v < 0 || v>4);
        return v;
    }

public:
    // 1 Add
    void addStudent() {
        int id = readId();
        if (index.count(id)) { cout << "  ID exists.\n"; return; }
        cin.ignore(); string name;
        cout << "Name : "; getline(cin, name);
        double gpa = readGpa();
        students.emplace_back(id, name, gpa);
        index[id] = (int)students.size() - 1;
        cout << "Added.\n";
    }

    // 2 Remove
    void removeStudent() {
        int id = readId();
        auto it = index.find(id);
        if (it == index.end()) { cout << "  Not found.\n"; return; }
        students.erase(students.begin() + it->second);
        rebuild();
        cout << "Removed.\n";
    }

    // 3 Search  – use find_if  (STL algorithm)
    void searchStudent() {
        int id = readId();
        auto it = find_if(students.begin(), students.end(),
            [id](const Student& s) { return s.getId() == id; });
        if (it == students.end()) { cout << "  Not found.\n"; return; }
        it->display();
    }

    // 4 Display all
    void displayAll() {
        if (students.empty()) { cout << "No students.\n"; return; }
        for (auto& s : students) s.display();
    }

    // 5 Enroll
    void enrollCourse() {
        Student* s = find(readId());
        if (!s) { cout << "Not found.\n"; return; }
        cin.ignore(); string c;
        cout << "Course: "; getline(cin, c);
        cout << (s->enrollCourse(c) ? " Enrolled.\n" : "Already enrolled.\n");
    }

    // 6 Show courses
    void showCourses() {
        Student* s = find(readId());
        if (!s) { cout << "  Not found.\n"; return; }
        if (s->getCourses().empty()) { cout << "  No courses.\n"; return; }
        for (auto& c : s->getCourses()) cout << "   - " << c << "\n";
    }

    // 7 Sort by GPA – uses sort()  (STL algorithm)
    void sortByGpa() {
        sort(students.begin(), students.end(),
            [](const Student& a, const Student& b) { return a.getGpa() < b.getGpa(); });
        rebuild();
        cout << "  Sorted.\n";
        displayAll();
    }

    // Bonus: count students with GPA >= 3.0 – uses count_if (stl algorithm)
    void countHighGpa() {
        int n = count_if(students.begin(), students.end(),
            [](const Student& s) { return s.getGpa() >= 3.0; });
        cout << "  Students with GPA >= 3.0 : " << n << "\n";
    }
};

// Menu 
int main() {
    StudentSystem prog;
    int ch;
    while (true) {
        cout << "\n Student System \n"
            << "1.Add  2.Remove  3.Search  4.Display\n"
            << "5.Enroll  6.Courses  7.Sort  8.Count(GPA>=3)  0.Exit\n"
            << "Choice: ";
        cin >> ch;
        if (ch == 0) break;
        switch (ch) {
        case 1: prog.addStudent();    break;
        case 2: prog.removeStudent(); break;
        case 3: prog.searchStudent(); break;
        case 4: prog.displayAll();    break;
        case 5: prog.enrollCourse();  break;
        case 6: prog.showCourses();   break;
        case 7: prog.sortByGpa();     break;
        case 8: prog.countHighGpa();  break;
        }
    }
}
