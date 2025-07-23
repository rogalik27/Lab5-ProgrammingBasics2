#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric> 
#include <queue>

using namespace std;

class Student {
private:
    unsigned int id;
    string familyName;
    vector<int> grades;

public:
    Student(unsigned int id, const string& name, const vector<int>& grades)
        : id(id), familyName(name), grades(grades) {}

    unsigned int getId() const { return id; }
    string getFamilyName() const { return familyName; }
    vector<int> getGrades() const { return grades; }

    double getAverageGrade() const {
        if (grades.empty()) return 0.0;
        return accumulate(grades.begin(), grades.end(), 0.0) / grades.size();
    }

    void print() const {
        cout << "ID: " << id << ", Прізвище: " << familyName << ", Оцінки: ";
        for (int g : grades)
            cout << g << " ";
        cout << "(середня оцінка: " << getAverageGrade() << ")" << endl;
    }

    bool operator<(const Student& other) const {
        return familyName < other.familyName;
    }

    struct CompareByAvg {
        bool operator()(const Student& a, const Student& b) const {
            return a.getAverageGrade() < b.getAverageGrade();
        }
    };
};

class Group {
private:
    int index;
    vector<Student> students;

public:
    Group(int idx) : index(idx) {}

    void addStudent(const Student& s) {
        students.push_back(s);
    }

    void print() const {
        cout << "група #" << index << ":\n";
        for (const auto& s : students)
            s.print();
    }

    void sortByFamilyName() {
        sort(students.begin(), students.end());
    }

    void findEvenIdStudents() const {
        cout << "Студенти з парними ID:\n";
        for_each(students.begin(), students.end(), [](const Student& s) {
            if (s.getId() % 2 == 0)
                s.print();
        });
    }

    void printByAverageDesc() const {
        priority_queue<Student, vector<Student>, Student::CompareByAvg> pq;
        for (const auto& s : students)
            pq.push(s);

        cout << "Студенти сортовані за збуванням середньої оцінки:\n";
        while (!pq.empty()) {
            pq.top().print();
            pq.pop();
        }
    }
};

int main() {
    Group group(101);

    group.addStudent(Student(1002, "Ivanchenko", {90, 85, 80, 95, 88}));
    group.addStudent(Student(1001, "Shevchenko", {78, 82, 88, 90, 76}));
    group.addStudent(Student(1004, "Bondarenko", {65, 70, 72, 68, 74}));

    cout << "Виведення всіх елементів масиву: \n";
    group.print();

    cout << "\nВиведення сортованих елементів масиву в алфавітному порядку: \n";
    group.sortByFamilyName();
    group.print();

    cout << "\nВиведення сортованих елементів масиву за парними ID\n";
    group.findEvenIdStudents();

    cout << "\nВиведення сортованих елементів за середньою оцінкою по збуванню\n";
    group.printByAverageDesc();

    return 0;
}
