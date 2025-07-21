# 📚 Student Management System (C++)

A modern, object-oriented **Student Management System** implemented in C++20. It offers an extensible and binary-safe backend for handling student records, admin roles, and grade analytics—all through a file-based system with serialization.

> 🧠 This is a backend logic showcase. A user interface or `main()` function is **intentionally omitted** to allow integration with different frontends (CLI, GUI, Web, etc.).

---

## ✨ Features

- 🔐 **Admin Access Control**  
  Manage admin roles with access levels: `NoAccess`, `LowAccess`, `FullAccess`. File-safe and atomic permission updates.

- 🧑‍🎓 **Student Record Management**  
  Add, update, and delete student records with binary serialization.

- 📊 **Grade Analytics**  
  GPA calculation and sorting mechanisms for academic tracking.

- 🔍 **Search & Filter**  
  Load all students or filter by `StudentStatus` or `RecordStatus`.

- 🧹 **Soft Deletion System**  
  Supports marking records as "Erased" for safe rollback or auditing.

---

## 📂 File Structure

| File               | Purpose                          |
|--------------------|----------------------------------|
| `Student.bin`      | Stores all student records       |
| `Admin.bin`        | Stores admin credentials         |
| `tempAdmin.bin`    | Temporary file for updates       |
| `Studenttemp.bin`  | Temporary file for safe deletion |

---

## ⚙️ Technologies Used

- C++20 (`std::format`, `std::ranges`, etc.)
- STL containers (`std::map`, `std::vector`)
- Strong `enum class` usage for type safety
- Manual binary I/O (`seekg`, `read`, `write`)
- Modern patterns (RAII, default constructors, `constexpr`)

---

## ❌ Why No `main()` Function?

This repo focuses on the **core logic**. Leaving out `main()` gives you:
- Modular and flexible design
- Easier unit testing
- Freedom to add your own CLI or GUI interface

You can plug in your own frontend or ask for a demo CLI from me.

---

## 🔧 Build Instructions

> Requires a C++20-compliant compiler

```bash
g++ -std=c++20 -o app *.cpp
./app

