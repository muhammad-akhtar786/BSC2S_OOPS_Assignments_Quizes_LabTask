#include <iostream>
#include <string>
using namespace std;

// Base Class of Employee (with Virtual Inheritance to avoid duplication)
class Employee {
private:
    string name;
    int age;
    string designation;
    float basicSalary;

public:
    Employee() {}

    Employee(string nm, int ag, string desi, float bSalary)
        : name(nm), age(ag), designation(desi), basicSalary(bSalary) {
    }

    void DisplayDetails();
    double calculateSalary();

    // Getter for basic salary
    float getBasicSalary() { return basicSalary; }
};

// Display Function of Employee Details
void Employee::DisplayDetails() {
    cout << endl << "---Displaying Details of Employee----" << endl;
    cout << "Employee Name : " << name << endl;
    cout << "Employee Age : " << age << endl;
    cout << "Employee Designation : " << designation << endl;
    cout << "Employee Basic Salary : " << basicSalary << endl;
}

// Salary Calculation Function
double Employee::calculateSalary() {
    double hra = 0.2 * getBasicSalary();  // 20% House Rent Allowance
    double da = 0.1 * getBasicSalary();   // 10% Dearness Allowance
    double tax = 0.05 * (getBasicSalary() + hra + da); // 5% Tax on Gross Salary

    double grossSalary = getBasicSalary() + hra + da;
    double netSalary = grossSalary - tax;
    return netSalary;
}

// Permanent Employee Derived Class (using Virtual Inheritance)
class PermanentEmployee : virtual public Employee {
private:
    double insuranceDeduction;
    double retirementFund;

public:
    PermanentEmployee(string nm, int ag, string desi, float bSalary, double insurance, double rFund)
        : Employee(nm, ag, desi, bSalary), insuranceDeduction(insurance), retirementFund(rFund) {
    }

    double calculateDeduction();
    double getNetSalary();
};

// Calculate Deduction Function
double PermanentEmployee::calculateDeduction() {
    return insuranceDeduction + retirementFund;
}

// Net Salary Function of Employee
double PermanentEmployee::getNetSalary() {
    double grossSalary = calculateSalary();
    return grossSalary - calculateDeduction();
}

// Contractual Employee Derived Class (using Virtual Inheritance)
class ContractualEmployee : virtual public Employee {
private:
    int contractDuration;
    int hourlyRate;
    int hoursWorked;

public:
    ContractualEmployee(string nm, int ag, string desi, int rate, int hours, int duration)
        : Employee(nm, ag, desi, 0), hourlyRate(rate), hoursWorked(hours), contractDuration(duration) {
    }

    double calculatePay();
    int getContractDuration() { return contractDuration; }
};

// Calculate Pay of Contractual Employee
double ContractualEmployee::calculatePay() {
    return hourlyRate * hoursWorked;
}

// Salary Processing Derived from both PermanentEmployee and ContractualEmployee
class SalaryProcessing : public PermanentEmployee, public ContractualEmployee {
private:
    double bonus;
    double taxRate;

public:
    SalaryProcessing(string nm, int ag, string desi, float basicSalary,
        double insuranceDeduction, double retirementFund,
        int hourlyRate, int hoursWorked, int contractDuration,
        double bonus, double taxRate)
        : Employee(nm, ag, desi, basicSalary),
        PermanentEmployee(nm, ag, desi, basicSalary, insuranceDeduction, retirementFund),
        ContractualEmployee(nm, ag, desi, hourlyRate, hoursWorked, contractDuration),
        bonus(bonus), taxRate(taxRate) {
    }

    double applyBonus();
    double applyTax(double salary);
    void generatePaySlip();
};

// Apply Bonus Function
double SalaryProcessing::applyBonus() {
    return bonus;
}

// Apply Tax Function
double SalaryProcessing::applyTax(double salary) {
    return salary - (taxRate / 100 * salary);
}

// Generate Pay Slip
void SalaryProcessing::generatePaySlip() {
    double finalSalary;

    // Determine whether it's a permanent or contractual employee
    if (getContractDuration() > 0) {
        finalSalary = calculatePay();
    }
    else {
        finalSalary = getNetSalary();
    }

    finalSalary += applyBonus();
    finalSalary = applyTax(finalSalary);

    cout << endl << "--- Pay Slip ---" << endl;
    Employee::DisplayDetails();  // Avoid ambiguity
    cout << "Final Salary after deductions: " << finalSalary << endl;
}

// Main Function
int main() {
    SalaryProcessing emp1("John Doe", 35, "Software Engineer", 5000,
        200, 300, 0, 0, 0, 500, 10);

    emp1.generatePaySlip();

    return 0;
}
