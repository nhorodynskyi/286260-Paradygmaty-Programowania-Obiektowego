# Copilot Instructions for OOP Lab Coursework

## Project Overview
**Course**: Object-Oriented Programming Paradigms (Paradygmaty Programowania Obiektowego)  
**Student**: Nazar Horodyskyi (286260)  
**Language**: C++  
**Purpose**: Laboratory assignments demonstrating OOP principles and design patterns

## Key Architectural Patterns

### C++ OOP Conventions
- Use **header/implementation separation** (.h/.hpp and .cpp files) for all classes and major components
- Follow **RAII** (Resource Acquisition Is Initialization) principle for automatic resource management
- Prefer **composition over inheritance** for complex object relationships
- Use **const-correctness** throughout: mark methods `const` when they don't modify state

### Code Organization
- Each lab assignment typically gets its own file or subdirectory (e.g., `lab1/`, `lab2/`)
- Main driver code in appropriately named `.cpp` files
- Class declarations in accompanying `.h` files
- Avoid putting multiple unrelated classes in a single file

### Naming Conventions
- **Classes**: PascalCase (e.g., `VehicleManager`, `DataProcessor`)
- **Functions/Methods**: camelCase (e.g., `processData()`, `calculateTotal()`)
- **Variables**: snake_case for globals, camelCase for locals and members (e.g., `int maxValue`, `double userInput`)
- **Constants**: UPPER_SNAKE_CASE (e.g., `const int MAX_SIZE = 100`)

## Critical Workflows

### Compilation
- Use a C++17-compatible compiler (g++, clang++, or MSVC)
- Example: `g++ -std=c++17 -o lab1 lab1.cpp` for single-file labs
- For multi-file projects: compile all `.cpp` files together or link object files

### Testing & Validation
- Include simple `main()` functions with test cases demonstrating functionality
- Use `assert()` or simple conditional checks for validation
- Avoid external testing frameworks—keep labs self-contained

### Debugging
- Compile with `-g` flag for debug symbols: `g++ -g -std=c++17 -o lab1_debug lab1.cpp`
- Use debugger (gdb, lldb) with breakpoints to verify object state and behavior

## Lab Assignment Patterns

### Expected Content per Lab
- **Class definitions** implementing specific OOP concepts (inheritance, polymorphism, encapsulation, etc.)
- **Demonstration code** in `main()` showing the pattern in action
- **Comments** explaining the OOP principle being illustrated

### Common OOP Topics (Expected in Future Labs)
- **Inheritance**: Base class design, virtual functions, abstract classes
- **Polymorphism**: Method overriding, operator overloading, templates
- **Encapsulation**: Public/private/protected access, getters/setters
- **Abstraction**: Interface design, pure virtual functions

## Developer Notes
- Keep each lab **self-contained** and runnable independently
- Write **clear output** to console (using `cout`) to demonstrate execution
- Add **comments** explaining non-obvious OOP decisions
- Test thoroughly before committing—coursework must demonstrate understanding

## Example Lab Structure
```cpp
// Animal.h
#pragma once

class Animal {
private:
    std::string name;
public:
    Animal(const std::string& n);
    virtual void speak() const;
    virtual ~Animal() = default;
};

// Dog.h
#pragma once
#include "Animal.h"

class Dog : public Animal {
public:
    void speak() const override;
};

// main.cpp
#include <iostream>
#include "Dog.h"

int main() {
    Dog dog("Rex");
    dog.speak();  // Output: Woof!
    return 0;
}
```
