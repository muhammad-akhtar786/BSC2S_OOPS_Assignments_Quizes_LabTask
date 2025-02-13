#include <iostream>
#include <string>
#include <cmath>
using namespace std;

 
int computeGCF(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

 
struct PowerNumber {
    int base;
    int exponent;
};

 
void multiplyPowerNumbers(const PowerNumber &num1, const PowerNumber &num2, PowerNumber &result) {
    if (num1.base != num2.base) {
        cout << "Error: Bases are different. Cannot multiply." << endl;
        return;
    }
    result.base = num1.base;
    result.exponent = num1.exponent + num2.exponent;
}

 
struct Course {
    string course_ID;
    string course_title;
    int credit_hours;
};

 
void AddCourse(Course courses[], int &courseCount) {
    if (courseCount >= 5) {
        cout << "Maximum courses reached (5). Cannot add more." << endl;
        return;
    }
    Course newCourse;
    cout << "Enter course ID: ";
    cin >> newCourse.course_ID;
    cin.ignore();  
    cout << "Enter course title: ";
    getline(cin, newCourse.course_title);
    cout << "Enter credit hours: ";
    cin >> newCourse.credit_hours;
    courses[courseCount] = newCourse;
    courseCount++;
    cout << "Course added successfully." << endl;
}

void UpdateCourse(Course courses[], int courseCount) {
    string id;
    cout << "Enter course ID to update: ";
    cin >> id;
    for (int i = 0; i < courseCount; i++) {
        if (courses[i].course_ID == id) {
            cin.ignore();
            cout << "Enter new course title: ";
            getline(cin, courses[i].course_title);
            cout << "Enter new credit hours: ";
            cin >> courses[i].credit_hours;
            cout << "Course updated successfully." << endl;
            return;
        }
    }
    cout << "Course not found." << endl;
}

void RemoveCourse(Course courses[], int &courseCount) {
    string id;
    cout << "Enter course ID to remove: ";
    cin >> id;
    for (int i = 0; i < courseCount; i++) {
        if (courses[i].course_ID == id) {
            for (int j = i; j < courseCount - 1; j++) {
                courses[j] = courses[j + 1];
            }
            courseCount--;
            cout << "Course removed successfully." << endl;
            return;
        }
    }
    cout << "Course not found." << endl;
}

void SearchCourse(Course courses[], int courseCount) {
    string id;
    cout << "Enter course ID to search: ";
    cin >> id;
    for (int i = 0; i < courseCount; i++) {
        if (courses[i].course_ID == id) {
            cout << "Course found:\n";
            cout << "ID: " << courses[i].course_ID << "\n";
            cout << "Title: " << courses[i].course_title << "\n";
            cout << "Credit Hours: " << courses[i].credit_hours << "\n";
            return;
        }
    }
    cout << "Course not found." << endl;
}

void DisplayAllCourses(Course courses[], int courseCount) {
    if (courseCount == 0) {
        cout << "No courses to display." << endl;
        return;
    }
    cout << "\nAll Courses:\n";
    for (int i = 0; i < courseCount; i++) {
        cout << "Course " << i + 1 << ":\n";
        cout << "ID: " << courses[i].course_ID << "\n";
        cout << "Title: " << courses[i].course_title << "\n";
        cout << "Credit Hours: " << courses[i].credit_hours << "\n";
        cout << "-------------------------" << endl;
    }
}

 
int main() {
     
    int num1 = 24, num2 = 36;
    cout << "Computing GCF of " << num1 << " and " << num2 << "...\n";
    int gcf = computeGCF(num1, num2);
    cout << "The GCF is: " << gcf << "\n\n";

     
    PowerNumber p1 = {2, 3};
    PowerNumber p2 = {2, 4};
    PowerNumber result;
    cout << "Multiplying power numbers: " << p1.base << "^" << p1.exponent << " and " << p2.base << "^" << p2.exponent << "\n";
    multiplyPowerNumbers(p1, p2, result);
    cout << "Result: " << result.base << "^" << result.exponent << "\n";

     
    PowerNumber p3 = {3, 2};
    cout << "\nAttempting to multiply different bases: " << p1.base << "^" << p1.exponent << " and " << p3.base << "^" << p3.exponent << "\n";
    multiplyPowerNumbers(p1, p3, result);

     
    Course courses[5];
    int courseCount = 0;
    int choice;

    do {
        cout << "\n========== CRUDS Menu ==========\n";
        cout << "1. Add Course\n";
        cout << "2. Update Course\n";
        cout << "3. Remove Course\n";
        cout << "4. Search Course\n";
        cout << "5. Display All Courses\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                AddCourse(courses, courseCount);
                break;
            case 2:
                UpdateCourse(courses, courseCount);
                break;
            case 3:
                RemoveCourse(courses, courseCount);
                break;
            case 4:
                SearchCourse(courses, courseCount);
                break;
            case 5:
                DisplayAllCourses(courses, courseCount);
                break;
            case 6:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
