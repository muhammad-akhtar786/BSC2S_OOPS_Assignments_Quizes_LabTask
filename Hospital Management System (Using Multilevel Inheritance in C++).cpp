#include <iostream>
#include <string>
#include <regex>
#include <vector>

using namespace std;

class Person {
private:
    string name;
    int age;
    string gender;
    string contact;

public:
    void inputDetails();
    void displayDetails() const;
};

void Person::inputDetails() {
    cout << "\n---- Enter Person Details ----" << endl;
    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, name);

    while (true) {
        cout << "Enter Age: ";
        cin >> age;
        if (age < 0) {
            cout << "Invalid Age! Please enter a valid age.\n";
        }
        else {
            break;
        }
    }

    cout << "Enter Gender (Male/Female/Other): ";
    cin >> gender;

    while (true) {
        regex pattern(R"(\d{11}$)");
        cout << "Enter Contact Number (e.g., 03031111111): ";
        cin >> contact;
        if (regex_match(contact, pattern)) {
            cout << "Valid Contact Number.\n";
            break;
        }
        else {
            cout << "Invalid Contact Number! Please enter an 11-digit number without spaces.\n";
        }
    }
}

void Person::displayDetails() const {
    cout << "\n--- Person Details ---\n";
    cout << "Name: " << name << "\n";
    cout << "Age: " << age << "\n";
    cout << "Gender: " << gender << "\n";
    cout << "Contact Number: " << contact << "\n";
}

// Derived Class from Person
class Patient : public Person {
private:
    int id;
    string disease;
    string admissionDate;

public:
    void inputPatientDetails();
    void displayPatientDetails() const;
};

void Patient::inputPatientDetails() {
    inputDetails();
    cin.ignore();

    cout << "Enter Patient ID: ";
    cin >> id;
    cin.ignore();

    cout << "Enter Disease: ";
    getline(cin, disease);

    while (true) {
        regex pattern(R"(\d{2}/\d{2}/\d{4})");
        cout << "Enter Admission Date (DD/MM/YYYY): ";
        cin >> admissionDate;
        if (regex_match(admissionDate, pattern)) {
            break;
        }
        else {
            cout << "Invalid Date! Please enter a valid date (e.g., 01/02/2025).\n";
        }
    }
}

void Patient::displayPatientDetails() const {
    displayDetails();
    cout << "Patient ID: " << id << "\n";
    cout << "Disease: " << disease << "\n";
    cout << "Admission Date: " << admissionDate << "\n";
}

// Doctor Class
class Doctor : public Person {
private:
    int drId;
    string specialization;
    string shift;

public:
    void inputDrDetails();
    void displayDrDetails() const;
};

void Doctor::inputDrDetails() {
    inputDetails();
    cout << "Enter Doctor ID: ";
    cin >> drId;

    cout << "Enter Specialization: ";
    cin >> specialization;

    cout << "Enter Shift (D for Day, N for Night): ";
    cin >> shift;
}

void Doctor::displayDrDetails() const {
    displayDetails();
    cout << "Doctor ID: " << drId << "\n";
    cout << "Specialization: " << specialization << "\n";
    cout << "Shift: " << (shift == "D" ? "Day" : "Night") << "\n";
}

// Appointment Class - Derived from Patient and Doctor
class Appointment : public Patient, public Doctor {
private:
    int appointmentId;
    string date;
    string time;

public:
    void scheduleAppointment();
    void displayAppointment() const;
};

void Appointment::scheduleAppointment() {
    cout << "Enter Appointment ID: ";
    cin >> appointmentId;

    while (true) {
        regex pattern(R"(\d{2}/\d{2}/\d{4})");
        cout << "Enter Appointment Date (DD/MM/YYYY): ";
        cin >> date;
        if (regex_match(date, pattern)) {
            break;
        }
        else {
            cout << "Invalid Date! Please enter a valid date (e.g., 01/02/2025).\n";
        }
    }

    while (true) {
        regex pattern(R"(\d{2}:\d{2})");
        cout << "Enter Appointment Time (HH:MM 24-hour format): ";
        cin >> time;
        if (regex_match(time, pattern)) {
            break;
        }
        else {
            cout << "Invalid Time! Please enter a valid time (e.g., 13:45).\n";
        }
    }
}

void Appointment::displayAppointment() const {
    cout << "\n--- Appointment Details ---\n";
    cout << "Appointment ID: " << appointmentId << "\n";
    cout << "Date: " << date << "\n";
    cout << "Time: " << time << "\n";

    cout << "\n--- Patient Details ---\n";
    displayPatientDetails();

    cout << "\n--- Doctor Details ---\n";
    displayDrDetails();
}

// Main Function
int main() {
    vector<Appointment> appointments;
    int choice;

    do {
        cout << "\n===== Hospital Management System =====\n";
        cout << "1. Schedule Appointment\n";
        cout << "2. Display Appointments\n";
        cout << "3. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        if (choice == 1) {
            Appointment app;
            app.inputPatientDetails();
            app.inputDrDetails();
            app.scheduleAppointment();
            appointments.push_back(app);
            cout << "\nAppointment Scheduled Successfully!\n";
        }
        else if (choice == 2) {
            if (appointments.empty()) {
                cout << "\nNo Appointments Available!\n";
            }
            else {
                for (const auto& app : appointments) {
                    app.displayAppointment();
                }
            }
        }

    } while (choice != 3);

    cout << "\nThank you for using the Hospital Management System!\n";
    return 0;
}
