// EMPLOYEE MANAGEMENT SYSTEM

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <limits>

using namespace std;

const int MAX_EMPLOYEES = 100;

enum Departments {
    HR = 1, SALES, CUSTOMER_SERVICE, FINANCE
};

enum JobTitles {
    MANAGER = 1, ASSISTANT, ADMINISTRATOR, ACCOUNT_MANAGER,
    RECRUITER, TRAINING_COORDINATOR,
    SALES_EXECUTIVE, BUSINESS_DEV_OFFICER,
    CUSTOMER_SUPPORT, SERVICE_COORDINATOR,
    ACCOUNTANT, PAYROLL_OFFICER, FINANCIAL_ANALYST
};

struct Employee {
    int id = 0;
    string name;
    double hoursWorked = 0.0;
    double salaryPerHour = 0.0;
    int jobTitle = 0;
    int department = 0;
};


// Function prototypes
void displayMainMenu();
void addEmployee(Employee employees[], int& count);
void displayAllEmployees(const Employee employees[], int count);
void displayDepartmentEmployees(const Employee employees[], int count);
void searchEmployee(const Employee employees[], int count);
void updateEmployee(Employee employees[], int count);
void promoteEmployee(Employee employees[], int count);
void removeEmployee(Employee employees[], int& count);
void moveEmployee(Employee employees[], int count);
void calculateSalary(const Employee employees[], int count);
bool saveToFile(const Employee employees[], int count, const string& filename);
bool loadFromFile(Employee employees[], int& count, const string& filename);
void clearInput();
bool isIdUnique(const Employee employees[], int count, int id);
bool isValidDepartment(int dept);
bool isValidJobTitle(int title, int dept);
string getDepartmentName(int dept);
string getJobTitleName(int title);
void displayEmployeeDetails(const Employee& emp);

int main() {
    Employee employees[MAX_EMPLOYEES];
    int employeeCount = 0;
    int choice;

    // Try to load existing data
    loadFromFile(employees, employeeCount, "employees.load_dat");

    do {
        displayMainMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        clearInput();

        switch (choice) {
        case 1:
            addEmployee(employees, employeeCount);
            break;
        case 2:
            displayAllEmployees(employees, employeeCount);
            break;
        case 3:
            displayDepartmentEmployees(employees, employeeCount);
            break;
        case 4:
            searchEmployee(employees, employeeCount);
            break;
        case 5:
            updateEmployee(employees, employeeCount);
            break;
        case 6:
            promoteEmployee(employees, employeeCount);
            break;
        case 7:
            removeEmployee(employees, employeeCount);
            break;
        case 8:
            moveEmployee(employees, employeeCount);
            break;
        case 9:
            calculateSalary(employees, employeeCount);
            break;
        case 10:
            saveToFile(employees, employeeCount, "employees.dat");
            break;
        case 11:
            loadFromFile(employees, employeeCount, "employees.dat");
            break;
        case 12:
            cout << "Exiting program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 12);

    return 0;
}

void displayMainMenu() {
    cout << "\nEmployee Management System\n";
    cout << "1. Add a new employee\n";
    cout << "2. Display all employees\n";
    cout << "3. Display employees by department\n";
    cout << "4. Search for an employee\n";
    cout << "5. Update employee information\n";
    cout << "6. Promote an employee\n";
    cout << "7. Remove an employee\n";
    cout << "8. Move employee to another department\n";
    cout << "9. Calculate employee salary\n";
    cout << "10. Save data to file\n";
    cout << "11. Load data from file\n";
    cout << "12. Exit\n";
}

void addEmployee(Employee employees[], int& count) {
    if (count >= MAX_EMPLOYEES) {
        cout << "Maximum number of employees reached!\n";
        return;
    }

    Employee newEmployee;

    // Get employee ID
    while (true) {
        cout << "Enter employee ID: ";
        cin >> newEmployee.id;

        if (cin.fail()) {
            cin.clear();
            clearInput();
            cout << "Invalid input. Please enter a numeric ID.\n";
            continue;
        }

        if (!isIdUnique(employees, count, newEmployee.id)) {
            cout << "ID already exists. Please enter a unique ID.\n";
        }
        else {
            break;
        }
    }
    clearInput();

    // Get employee name
    cout << "Enter employee name: ";
    getline(cin, newEmployee.name);

    // Get hours worked
    while (true) {
        cout << "Enter total hours worked: ";
        cin >> newEmployee.hoursWorked;

        if (cin.fail() || newEmployee.hoursWorked < 0) {
            cin.clear();
            clearInput();
            cout << "Invalid input. Please enter a positive number.\n";
        }
        else {
            break;
        }
    }
    clearInput();

    // Get salary per hour
    while (true) {
        cout << "Enter salary per hour: ";
        cin >> newEmployee.salaryPerHour;

        if (cin.fail() || newEmployee.salaryPerHour <= 0) {
            cin.clear();
            clearInput();
            cout << "Invalid input. Please enter a positive number.\n";
        }
        else {
            break;
        }
    }
    clearInput();

    // Get department
    while (true) {
        cout << "Departments:\n";
        cout << "1. Human Resources\n";
        cout << "2. Sales\n";
        cout << "3. Customer Service\n";
        cout << "4. Finance\n";
        cout << "Enter department number: ";
        cin >> newEmployee.department;

        if (!isValidDepartment(newEmployee.department)) {
            cin.clear();
            clearInput();
            cout << "Invalid department. Please enter a number between 1 and 4.\n";
        }
        else {
            break;
        }
    }
    clearInput();

    // Get job title
    while (true) {
        cout << "\nJob Titles for " << getDepartmentName(newEmployee.department) << ":\n";
        // Display appropriate job titles based on department
        switch (newEmployee.department) {
        case HR:
            cout << "1. Manager\n2. Assistant\n3. Administrator\n4. Account Manager\n5. Recruiter\n6. Training Coordinator\n";
            break;
        case SALES:
            cout << "1. Manager\n2. Assistant\n3. Administrator\n4. Account Manager\n7. Sales Executive\n8. Business Development Officer\n";
            break;
        case CUSTOMER_SERVICE:
            cout << "1. Manager\n2. Assistant\n3. Administrator\n4. Account Manager\n9. Customer Support\n10. Service Coordinator\n";
            break;
        case FINANCE:
            cout << "1. Manager\n2. Assistant\n3. Administrator\n4. Account Manager\n11. Accountant\n12. Payroll Officer\n13. Financial Analyst\n";
            break;
        }
        cout << "Enter job title number: ";
        cin >> newEmployee.jobTitle;

        if (!isValidJobTitle(newEmployee.jobTitle, newEmployee.department)) {
            cin.clear();
            clearInput();
            cout << "Invalid job title for this department. Please try again.\n";
        }
        else {
            break;
        }
    }
    clearInput();

    employees[count] = newEmployee;
    count++;
    cout << "Employee added successfully!\n";
}

void displayAllEmployees(const Employee employees[], int count) {
    if (count == 0) {
        cout << "No employees in the system.\n";
        return;
    }

    cout << " \n All Employee ( " << count << " ) in total : \n";
    cout << " ----------------------------------------------------------------------------------- \n";
    cout << "ID\tName\t\tHours\tSalary\tTitle\t\tDepartment\n";
    cout << " ------------------------------------------------------------------------------------\n";

    for (int i = 0; i < count; i++)
    {
        const Employee& emp = employees[i];
        cout << emp.id << "\t" << emp.name << "\t\t" << emp.hoursWorked << "\t" <<
            emp.salaryPerHour << "\t" << emp.jobTitle << "\t\t" << emp.department << endl;
    }
}

void displayDepartmentEmployees(const Employee employees[], int count) {
    int dept;

    cout << "\nDepartments:\n";
    cout << "1. Human Resources\n";
    cout << "2. Sales\n";
    cout << "3. Customer Service\n";
    cout << "4. Finance\n";
    cout << "Enter department number: ";
    cin >> dept;
    clearInput();

    if (!isValidDepartment(dept)) {
        cout << "Invalid department number.\n";
        return;
    }

    bool found = false;
    cout << "\nEmployees in " << getDepartmentName(dept) << " department:\n";
    cout << "----------------------------------------------------------------------------------------------------\n";
    cout << "ID\tName\t\tJob Title\t\tHours\tSalary/Hour\n";
    cout << "----------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < count; i++) {
        if (employees[i].department == dept) {
            found = true;
            const Employee& emp = employees[i];
            cout << emp.id << "\t"
                << emp.name << "\t\t"
                << setw(20) << left << getJobTitleName(emp.jobTitle) << "\t"
                << emp.hoursWorked << "\t"
                << emp.salaryPerHour << endl;
        }
    }

    if (!found) {
        cout << "No employees found in this department.\n";
    }
}

void searchEmployee(const Employee employees[], int count) {
    if (count == 0) {
        cout << "No employees in the system.\n";
        return;
    }

    string name;
    int dept;

    cout << "Enter employee name: ";
    getline(cin, name);

    cout << "\nDepartments:\n";
    cout << "1. Human Resources\n";
    cout << "2. Sales\n";
    cout << "3. Customer Service\n";
    cout << "4. Finance\n";
    cout << "Enter department number: ";
    cin >> dept;
    clearInput();

    if (!isValidDepartment(dept)) {
        cout << "Invalid department number.\n";
        return;
    }

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (employees[i].department == dept &&
            employees[i].name.find(name) != string::npos) {
            found = true;
            cout << "\nEmployee found:\n";
            displayEmployeeDetails(employees[i]);
        }
    }

    if (!found) {
        cout << "No employee found with that name in the specified department.\n";
    }
}

void updateEmployee(Employee employees[], int count) {
    if (count == 0) {
        cout << "No employees in the system.\n";
        return;
    }

    int id;
    cout << "Enter employee ID to update: ";
    cin >> id;
    clearInput();

    int index = -1;
    for (int i = 0; i < count; i++) {
        if (employees[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Employee not found.\n";
        return;
    }

    Employee& emp = employees[index];
    cout << "\nCurrent employee information:\n";
    displayEmployeeDetails(emp);

    cout << "\nEnter new information (leave blank to keep current value):\n";

    // Update name
    cout << "Name [" << emp.name << "]: ";
    string newName;
    getline(cin, newName);
    if (!newName.empty()) {
        emp.name = newName;
    }

    // Update hours worked
    cout << "Hours worked [" << emp.hoursWorked << "]: ";
    string hoursInput;
    getline(cin, hoursInput);
    if (!hoursInput.empty()) {
        try {
            double newHours = stod(hoursInput);
            if (newHours >= 0) {
                emp.hoursWorked = newHours;
            }
            else {
                cout << "Invalid input. Hours must be positive. Keeping current value.\n";
            }
        }
        catch (...) {
            cout << "Invalid input. Keeping current value.\n";
        }
    }

    // Update salary per hour
    cout << "Salary per hour [" << emp.salaryPerHour << "]: ";
    string salaryInput;
    getline(cin, salaryInput);
    if (!salaryInput.empty()) {
        try {
            double newSalary = stod(salaryInput);
            if (newSalary > 0) {
                emp.salaryPerHour = newSalary;
            }
            else {
                cout << "Invalid input. Salary must be positive. Keeping current value.\n";
            }
        }
        catch (...) {
            cout << "Invalid input. Keeping current value.\n";
        }
    }

    // Update department
    cout << "Department [" << getDepartmentName(emp.department) << "]: ";
    string deptInput;
    getline(cin, deptInput);
    if (!deptInput.empty()) {
        try {
            int newDept = stoi(deptInput);
            if (isValidDepartment(newDept)) {
                emp.department = newDept;
            }
            else {
                cout << "Invalid department. Keeping current value.\n";
            }
        }
        catch (...) {
            cout << "Invalid input. Keeping current value.\n";
        }
    }

    // Update job title
    cout << "Job Title [" << getJobTitleName(emp.jobTitle) << "]: ";
    string titleInput;
    getline(cin, titleInput);
    if (!titleInput.empty()) {
        try {
            int newTitle = stoi(titleInput);
            if (isValidJobTitle(newTitle, emp.department)) {
                emp.jobTitle = newTitle;
            }
            else {
                cout << "Invalid job title for this department. Keeping current value.\n";
            }
        }
        catch (...) {
            cout << "Invalid input. Keeping current value.\n";
        }
    }

    cout << "Employee information updated successfully.\n";
}

void promoteEmployee(Employee employees[], int count) {
    if (count == 0) {
        cout << "No employees in the system.\n";
        return;
    }

    int id;
    cout << "Enter employee ID to promote: ";
    cin >> id;
    clearInput();

    int index = -1;
    for (int i = 0; i < count; i++) {
        if (employees[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Employee not found.\n";
        return;
    }

    Employee& emp = employees[index];
    cout << "\nCurrent employee information:\n";
    displayEmployeeDetails(emp);

    // Display available job titles for promotion
    cout << "\nAvailable job titles for promotion in " << getDepartmentName(emp.department) << ":\n";
    switch (emp.department) {
    case HR:
        cout << "5. Recruiter\n6. Training Coordinator\n";
        if (emp.jobTitle < RECRUITER) break;
        cout << "1. Manager\n2. Assistant\n3. Administrator\n4. Account Manager\n";
        break;
    case SALES:
        cout << "7. Sales Executive\n8. Business Development Officer\n";
        if (emp.jobTitle < SALES_EXECUTIVE) break;
        cout << "1. Manager\n2. Assistant\n3. Administrator\n4. Account Manager\n";
        break;
    case CUSTOMER_SERVICE:
        cout << "9. Customer Support\n10. Service Coordinator\n";
        if (emp.jobTitle < CUSTOMER_SUPPORT) break;
        cout << "1. Manager\n2. Assistant\n3. Administrator\n4. Account Manager\n";
        break;
    case FINANCE:
        cout << "11. Accountant\n12. Payroll Officer\n13. Financial Analyst\n";
        if (emp.jobTitle < ACCOUNTANT) break;
        cout << "1. Manager\n2. Assistant\n3. Administrator\n4. Account Manager\n";
        break;
    }

    // Get new job title
    int newTitle;
    while (true) {
        cout << "Enter new job title number: ";
        cin >> newTitle;
        clearInput();

        if (isValidJobTitle(newTitle, emp.department)) {
            if (newTitle <= emp.jobTitle) {
                cout << "This is not a promotion. Please enter a higher job title number.\n";
            }
            else {
                break;
            }
        }
        else {
            cout << "Invalid job title for this department.\n";
        }
    }

    // Get salary increase percentage
    double percentage;
    while (true) {
        cout << "Enter salary increase percentage (e.g., 10 for 10%): ";
        cin >> percentage;
        clearInput();

        if (percentage > 0) {
            break;
        }
        else {
            cout << "Percentage must be positive.\n";
        }
    }

    // Apply changes
    emp.jobTitle = newTitle;
    emp.salaryPerHour *= (1 + percentage / 100.0);

    cout << "\nEmployee promoted successfully!\n";
    cout << "New job title: " << getJobTitleName(emp.jobTitle) << endl;
    cout << "New salary per hour: " << emp.salaryPerHour << endl;
}

void removeEmployee(Employee employees[], int& count) {
    if (count == 0) {
        cout << "No employees in the system.\n";
        return;
    }

    int id;
    cout << "Enter employee ID to remove: ";
    cin >> id;
    clearInput();

    int index = -1;
    for (int i = 0; i < count; i++) {
        if (employees[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Employee not found.\n";
        return;
    }

    // Display employee to be removed
    cout << "\nRemoving this employee:\n";
    displayEmployeeDetails(employees[index]);

    // Confirm removal
    string confirm;
    cout << "Are you sure you want to remove this employee? (y/n): ";
    getline(cin, confirm);

    if (tolower(confirm[0]) == 'y') {
        // Shift all elements after the index one position left
        for (int i = index; i < count - 1; i++) {
            employees[i] = employees[i + 1];
        }
        count--;
        cout << "Employee removed successfully.\n";
    }
    else {
        cout << "Removal canceled.\n";
    }
}

void moveEmployee(Employee employees[], int count) {
    if (count == 0) {
        cout << "No employees in the system.\n";
        return;
    }

    int id;
    cout << "Enter employee ID to move: ";
    cin >> id;
    clearInput();

    int index = -1;
    for (int i = 0; i < count; i++) {
        if (employees[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Employee not found.\n";
        return;
    }

    Employee& emp = employees[index];
    cout << "\nCurrent employee information:\n";
    displayEmployeeDetails(emp);

    // Get new department
    int newDept;
    while (true) {
        cout << "\nDepartments:\n";
        cout << "1. Human Resources\n";
        cout << "2. Sales\n";
        cout << "3. Customer Service\n";
        cout << "4. Finance\n";
        cout << "Enter new department number: ";
        cin >> newDept;
        clearInput();

        if (isValidDepartment(newDept)) {
            if (newDept == emp.department) {
                cout << "Employee is already in this department.\n";
            }
            else {
                break;
            }
        }
        else {
            cout << "Invalid department number.\n";
        }
    }

    // Display job titles available in new department
    cout << "\nAvailable job titles in " << getDepartmentName(newDept) << ":\n";
    cout << "1. Manager\n2. Assistant\n3. Administrator\n4. Account Manager\n";
    switch (newDept) {
    case HR:
        cout << "5. Recruiter\n6. Training Coordinator\n";
        break;
    case SALES:
        cout << "7. Sales Executive\n8. Business Development Officer\n";
        break;
    case CUSTOMER_SERVICE:
        cout << "9. Customer Support\n10. Service Coordinator\n";
        break;
    case FINANCE:
        cout << "11. Accountant\n12. Payroll Officer\n13. Financial Analyst\n";
        break;
    }

    // Get new job title
    int newTitle;
    while (true) {
        cout << "Enter new job title number: ";
        cin >> newTitle;
        clearInput();

        if (isValidJobTitle(newTitle, newDept)) {
            break;
        }
        else {
            cout << "Invalid job title for this department.\n";
        }
    }

    // Apply changes
    emp.department = newDept;
    emp.jobTitle = newTitle;

    cout << "\nEmployee moved successfully!\n";
    cout << "New department: " << getDepartmentName(emp.department) << endl;
    cout << "New job title: " << getJobTitleName(emp.jobTitle) << endl;
}

void calculateSalary(const Employee employees[], int count) {
    if (count == 0) {
        cout << "No employees in the system.\n";
        return;
    }

    int id;
    while (true) {
        cout << "Enter employee ID to calculate salary: ";
        if (cin >> id) {
            clearInput();  // Clear any remaining input
            break;
        }
        else {
            cout << "Invalid input. Please enter a numeric ID.\n";
            cin.clear();  // Clear error state
            clearInput();  // Clear the input buffer
        }
    }

    int index = -1;
    for (int i = 0; i < count; i++) {
        if (employees[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Employee not found.\n";
        return;
    }

    const Employee& emp = employees[index];
    double salary = emp.hoursWorked * emp.salaryPerHour;

    cout << "\nSalary calculation for " << emp.name << ":\n";
    cout << "Hours worked: " << emp.hoursWorked << endl;
    cout << "Salary per hour: " << emp.salaryPerHour << endl;
    cout << "Total salary: " << fixed << setprecision(2) << salary << endl;
}


bool loadFromFile(Employee employees[], int& count, const string& filename = "employees.dat") {
    ifstream inFile(filename);
    count = 0; // Reset count before loading

    if (!inFile) {
        cout << "No existing data file found. Starting with empty database.\n";
        return false;
    }

    string line;
    while (getline(inFile, line) && count < MAX_EMPLOYEES) {
        Employee emp;
        size_t pos = 0;
        string token;
        int field = 0;

        try {
            while ((pos = line.find(',')) != string::npos) {
                token = line.substr(0, pos);

                switch (field) {
                case 0: emp.id = stoi(token); break;
                case 1: emp.name = token; break;
                case 2: emp.hoursWorked = stod(token); break;
                case 3: emp.salaryPerHour = stod(token); break;
                case 4: emp.jobTitle = stoi(token); break; // Read as int
                }

                line.erase(0, pos + 1);
                field++;
            }

            // The last field (department) - read as int
            if (!line.empty()) {
                emp.department = stoi(line);
            }

            // Only add if valid
            if (emp.id > 0 && isValidDepartment(emp.department) &&
                isValidJobTitle(emp.jobTitle, emp.department)) {
                employees[count] = emp;
                count++;
            }
        }
        catch (...) {
            // Skip malformed records
            continue;
        }
    }

    inFile.close();
    cout << "Employee data loaded from file successfully! (" << count << " records)\n";
    return true;
}

bool saveToFile(const Employee employees[], int count, const string& filename = "employees.load_dat") {
    ofstream outFile(filename);

    if (!outFile) {
        cout << "Error opening file for writing.\n";
        return false;
    }

    for (int i = 0; i < count; i++) {
        const Employee& emp = employees[i];
        outFile << emp.id << ","
            << emp.name << ","
            << emp.hoursWorked << ","
            << emp.salaryPerHour << ","
            << emp.jobTitle << ","  // Store as int
            << emp.department << "\n";  // Store as int
    }

    outFile.close();
    cout << "Employee data saved to file successfully! (" << count << " records)\n";
    return true;
}


void clearInput() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool isIdUnique(const Employee employees[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (employees[i].id == id) {
            return false;
        }
    }
    return true;
}

bool isValidDepartment(int dept) {
    return dept >= HR && dept <= FINANCE;
}

bool isValidJobTitle(int title, int dept) {
    // General titles available to all departments
    if (title >= MANAGER && title <= ACCOUNT_MANAGER) {
        return true;
    }

    // Department-specific titles
    switch (dept) {
    case HR:
        return (title >= RECRUITER && title <= TRAINING_COORDINATOR);
    case SALES:
        return (title >= SALES_EXECUTIVE && title <= BUSINESS_DEV_OFFICER);
    case CUSTOMER_SERVICE:
        return (title >= CUSTOMER_SUPPORT && title <= SERVICE_COORDINATOR);
    case FINANCE:
        return (title >= ACCOUNTANT && title <= FINANCIAL_ANALYST);
    default:
        return false;
    }
}

string getDepartmentName(int dept) {
    switch (dept) {
    case HR: return "Human Resources";
    case SALES: return "Sales";
    case CUSTOMER_SERVICE: return "Customer Service";
    case FINANCE: return "Finance";
    default: return "Unknown Department";
    }
}

string getJobTitleName(int title) {
    switch (title) {
    case MANAGER: return "Manager";
    case ASSISTANT: return "Assistant";
    case ADMINISTRATOR: return "Administrator";
    case ACCOUNT_MANAGER: return "Account Manager";
    case RECRUITER: return "Recruiter";
    case TRAINING_COORDINATOR: return "Training Coordinator";
    case SALES_EXECUTIVE: return "Sales Executive";
    case BUSINESS_DEV_OFFICER: return "Business Development Officer";
    case CUSTOMER_SUPPORT: return "Customer Support";
    case SERVICE_COORDINATOR: return "Service Coordinator";
    case ACCOUNTANT: return "Accountant";
    case PAYROLL_OFFICER: return "Payroll Officer";
    case FINANCIAL_ANALYST: return "Financial Analyst";
    default: return "Unknown Title";
    }
}

void displayEmployeeDetails(const Employee& emp) {
    cout << "----------------------------------------\n";
    cout << "ID: " << emp.id << endl;
    cout << "Name: " << emp.name << endl;
    cout << "Department: " << getDepartmentName(emp.department) << endl;
    cout << "Job Title: " << getJobTitleName(emp.jobTitle) << endl;
    cout << "Hours Worked: " << emp.hoursWorked << endl;
    cout << "Salary per Hour: " << emp.salaryPerHour << endl;
    cout << "Monthly Salary: " << fixed << setprecision(2) << (emp.hoursWorked * emp.salaryPerHour) << endl;
    cout << "----------------------------------------\n";
}
