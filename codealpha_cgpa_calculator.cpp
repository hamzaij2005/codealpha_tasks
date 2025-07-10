#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Function to convert letter grade to grade point
double gradeToPoint(const string& grade) {
    if (grade == "A+" || grade == "A") return 4.0;
    else if (grade == "A-") return 3.7;
    else if (grade == "B+") return 3.3;
    else if (grade == "B") return 3.0;
    else if (grade == "B-") return 2.7;
    else if (grade == "C+") return 2.3;
    else if (grade == "C") return 2.0;
    else if (grade == "C-") return 1.7;
    else if (grade == "D+") return 1.3;
    else if (grade == "D") return 1.0;
    else return 0.0; // F or invalid grades
}

int main() {
    const int MAX_COURSES = 50;  // Max courses allowed
    int numCourses;
    string grades[MAX_COURSES];       // Array to store grades
    double creditHours[MAX_COURSES];  // Array to store credit hours
    double gradePoints[MAX_COURSES];  // Array to store converted grade points

    double totalCredits = 0;
    double totalGradePoints = 0;

    // Input number of courses
    cout << "Enter the number of courses: ";
    cin >> numCourses;

    // Safety check
    if (numCourses <= 0 || numCourses > MAX_COURSES) {
        cout << "Invalid number of courses. Must be between 1 and " << MAX_COURSES << ".\n";
        return 1;
    }

    // Input data for each course
    for (int i = 0; i < numCourses; ++i) {
        cout << "\nCourse " << i + 1 << ":\n";

        cout << "Enter grade (e.g., A, B+, C-): ";
        cin >> grades[i];

        cout << "Enter credit hours: ";
        cin >> creditHours[i];

        // Convert grade to grade point
        gradePoints[i] = gradeToPoint(grades[i]);

        // Accumulate totals
        totalCredits += creditHours[i];
        totalGradePoints += gradePoints[i] * creditHours[i];
    }

    // Calculate GPA
    double GPA = (totalCredits > 0) ? (totalGradePoints / totalCredits) : 0.0;

    // Display results
    cout << "\n--- Course Grades ---\n";
    cout << fixed << setprecision(2);
    for (int i = 0; i < numCourses; ++i) {
        cout << "Course " << i + 1
             << ": Grade = " << grades[i]
             << ", Credit Hours = " << creditHours[i]
             << ", Grade Point = " << gradePoints[i] << endl;
    }

    cout << "\n✅ Final GPA / CGPA: " << GPA << endl;

    return 0;
}
