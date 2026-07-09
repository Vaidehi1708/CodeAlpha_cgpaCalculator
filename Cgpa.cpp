#include <iostream>
#include <vector>
#include <string>
using namespace std;
 
// structure to store details of one course
struct Course {
    string grade;
    int creditHours;
    float gradePoint;   // grade point earned for this course (grade value * credit hours)
};
 
// structure to store details of one semester
struct Semester {
    vector<Course> courses;
    float totalCredits;
    float totalGradePoints;
    float sgpa;
};
 
// function to convert letter grade to grade point value (10 point scale)
float getGradeValue(string grade) {
    if (grade == "A++|| a++")  return 10;
    if (grade == "A+|| a+") return 9;
    if (grade == "A|| a")  return 8;
    if (grade == "B+||b+") return 7;
    if (grade == "B||b")  return 6;
    if (grade == "C||c")  return 5;
    if (grade == "D")  return 4;
    if (grade == "F")  return 0;
 
    // if grade entered is invalid, return -1 so we can handle it later
    return -1;
}
 
// function to take input for all courses of one semester
Semester inputSemesterData(int semNo) {
    Semester sem;
    int n;
 
    cout << "\nEnter number of courses in Semester " << semNo << ": ";
    cin >> n;
 
    sem.totalCredits = 0;
    sem.totalGradePoints = 0;
 
    for (int i = 0; i < n; i++) {
        Course c;
        float gradeValue;
 
        // keep asking until a valid grade is entered
        do {
            cout << "Course " << i + 1 << " - Enter grade (A++/A+/A/B+/B/C/D/F): ";
            cin >> c.grade;
            gradeValue = getGradeValue(c.grade);
            if (gradeValue == -1)
                cout << "Invalid grade entered, please try again.\n";
        } while (gradeValue == -1);
 
        cout << "Course " << i + 1 << " - Enter credit hours: ";
        cin >> c.creditHours;
 
        c.gradePoint = gradeValue * c.creditHours;
 
        sem.totalCredits += c.creditHours;
        sem.totalGradePoints += c.gradePoint;
 
        sem.courses.push_back(c);
    }
 
    // sgpa = total grade points / total credits
    sem.sgpa = sem.totalGradePoints / sem.totalCredits;
 
    return sem;
}
 
// function to display all course grades of a semester along with its sgpa
void displaySemesterResult(Semester sem, int semNo) {
    cout << "\n----- Semester " << semNo << " Result -----\n";
    for (int i = 0; i < sem.courses.size(); i++) {
        cout << "Course " << i + 1 << " : Grade = " << sem.courses[i].grade
             << ", Credit Hours = " << sem.courses[i].creditHours
             << ", Grade Points = " << sem.courses[i].gradePoint << endl;
    }
    cout << "Total Credits = " << sem.totalCredits << endl;
    cout << "SGPA = " << sem.sgpa << endl;
}
 
// function to calculate overall cgpa using all semesters
float calculateCGPA(vector<Semester> semesters) {
    float totalCredits = 0;
    float totalGradePoints = 0;
 
    for (int i = 0; i < semesters.size(); i++) {
        totalCredits += semesters[i].totalCredits;
        totalGradePoints += semesters[i].totalGradePoints;
    }
 
    return totalGradePoints / totalCredits;
}
 
int main() {
    int numSemesters;
    vector<Semester> allSemesters;
 
    cout << "===== CGPA CALCULATOR =====\n";
    cout << "Enter number of semesters: ";
    cin >> numSemesters;
 
    // take input semester by semester
    for (int i = 1; i <= numSemesters; i++) {
        Semester sem = inputSemesterData(i);
        allSemesters.push_back(sem);
    }
 
    // display result of every semester
    for (int i = 0; i < allSemesters.size(); i++) {
        displaySemesterResult(allSemesters[i], i + 1);
    }
 
    // final cgpa calculation
    float cgpa = calculateCGPA(allSemesters);
 
    cout<<"==RESULT=="<<endl;
    cout << "FINAL CGPA = " << cgpa << endl;
   
 
    return 0;
}
 