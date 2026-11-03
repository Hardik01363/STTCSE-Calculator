# STTCSE Calculator

A modular, robust, and tested command-line & interactive calculator written in C.

## Features

- **Core Mathematical Operations:**
  - Addition (`+`)
  - Subtraction (`-`)
  - Multiplication (`*`)
  - Division (`/`) with division-by-zero validation
  - Modulo (`%`)
  - Exponentiation / Power (`^`)
  - Square Root (`sqrt`) with negative value checks
  - Factorial (`!`) with negative integer and overflow handling
- **Dual Mode Operation:**
  - **Interactive Mode**: Friendly menu-driven interface with input validation and loop.
  - **CLI Mode**: Run single-line calculations directly from the terminal (ideal for scripting and testing).
- **Unit Test Suite**: Built-in test suite covering edge cases and arithmetic correctness.

---

## Project Structure

```text
STTCSE-Calculator/
├── include/
│   └── calculator.h      # Public API declarations and status codes
├── src/
│   ├── calculator.c      # Implementation of mathematical operations
│   └── main.c            # CLI and interactive interface
├── tests/
│   └── test_calculator.c # Unit test suite
├── Makefile              # Build automation script
└── README.md             # Documentation
```

---

## Building the Project

Use `make` to compile the project:

```bash
make
```

This compiles the source files into `bin/calculator` and creates a `./calculator` link at the root.

### Other Useful Make Targets

- **Run unit tests:**
  ```bash
  make test
  ```
- **Run the interactive calculator:**
  ```bash
  make run
  ```
- **Clean build artifacts:**
  ```bash
  make clean
  ```
- **Show help:**
  ```bash
  make help
  ```

---

## Usage Examples

### 1. Interactive Mode
Run the calculator without arguments:
```bash
./calculator
```
Output:
```text
===========================================
            STTCSE Calculator              
===========================================

Choose an operation:
  1. Addition (+)
  2. Subtraction (-)
  3. Multiplication (*)
  4. Division (/)
  5. Modulo (%)
  6. Power (^)
  7. Square Root (sqrt)
  8. Factorial (!)
  9. Exit
Enter choice (1-9):
```

### 2. Command-Line Arguments Mode
Run one-off expressions directly:
```bash
# Addition
./calculator 10 + 5
# Output: 10 + 5 = 15

# Division
./calculator 22 / 7
# Output: 22 / 7 = 3.14286

# Power
./calculator 2 ^ 10
# Output: 2 ^ 10 = 1024

# Square root
./calculator sqrt 144
# Output: sqrt(144) = 12

# Factorial
./calculator fact 6
# Output: 6! = 720
```
