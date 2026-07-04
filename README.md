<div align="center">

![Typing SVG](https://readme-typing-svg.demolab.com/?lines=👔+Employee+Management+System;C+++Problem+Solving+Project;&center=true&width=700&height=80&size=28&weight=700&color=378ADD&pause=1000)

</div>

---

## 📌 Overview

An **Employee Management System** is a comprehensive tool that automates and simplifies various human resource tasks, enabling organizations to manage their workforce more effectively. It acts as a centralized hub for:

- 📁 Maintaining employee records
- ⏱️ Monitoring attendance and leave
- 💰 Handling payroll
- 📈 Evaluating performance
- 🔐 Providing secure, role-based access

Overall, the EMS boosts efficiency, reduces manual effort, and enhances organizational performance.

---
## 🏗️ System Architecture

### Modules Overview

| Module | Responsibility |
|--------|---------------|
| **Main Module** | Controls program execution and user interaction via a menu-driven interface |
| **Employee Data Module** | Defines employee record structure, enums for departments and job titles, and validation functions |
| **Employee Management Module** | Handles adding, displaying, searching, updating, promoting, removing, and moving employees |
| **Salary Calculation Module** | Computes salaries based on hours worked and pay rate |
| **File I/O Module** | Manages data persistence — saving and loading employee records securely |
| **Input/Output Utilities Module** | Handles input validation, output formatting, and user prompts |
| **Validation Module** | Enforces data integrity — checks ID uniqueness, department validity, and job title compatibility |

---

### 🗃️ Data Structures Used

- **Struct** — `Employee` struct encapsulates all employee attributes:
  - ID, Name, Hours Worked, Hourly Salary, Job Title, Department

- **1D Array** — Employee records stored in a static array `employees[MAX_EMPLOYEES]` for straightforward indexing and iteration

- **Enumerations** — `Departments` and `JobTitles` enums define valid categories:
  - Departments: `HR`, `Sales`, `Customer Service`, `Finance`
  - Ensures data consistency and prevents invalid assignments

- **String** — `std::string` handles textual data such as employee names

---

## 🚀 How to Compile & Run

### Requirements
- A C++ compiler (e.g. **g++** or **Microsoft Visual C++**)
- Windows, macOS, or Linux

### Steps

**1. Clone the repository:**
```bash
git clone https://github.com/YOUR_USERNAME/Employee-Management-System.git
cd Employee-Management-System
```

**2. Compile the program:**
```bash
g++ employee_management.cpp -o employee_management
```
> On Windows, add `.exe`:
> ```bash
> g++ employee_management.cpp -o employee_management.exe
> ```

**3. Run the program:**
```bash
./employee_management
```
> On Windows:
> ```bash
> employee_management.exe
> ```

### Notes
- No additional libraries or dependencies required
- Data is automatically stored in `employees.txt` (created on first run)
- Built-in input validation ensures data integrity
- Ensure you have file read/write permissions in the working directory

---

## 🛠️ Tech Stack

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![OOP](https://img.shields.io/badge/OOP-Structs%20%26%20Enums-7F77DD?style=for-the-badge)
![File I/O](https://img.shields.io/badge/File_I/O-employees.txt-0F6E56?style=for-the-badge)

---

---

> *"Turning data into decisions."*
