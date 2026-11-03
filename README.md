# STTCSE Calculator

A modular, robust, and tested command-line & interactive calculator written in C with Docker containerization support.

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
- **Docker Support**: Containerized build and execution via Ubuntu-based Dockerfile.

---

## Project Structure

```text
STTCSE-Calculator/
├── Dockerfile            # Container configuration matching lab specifications
├── Makefile              # Build automation script
├── README.md             # Project documentation and usage guide
├── adder/                # Source package for container ADD directive
│   ├── Makefile
│   ├── include/
│   ├── src/
│   └── tests/
├── include/
│   └── calculator.h      # Public API declarations and status codes
├── src/
│   ├── calculator.c      # Implementation of mathematical operations
│   └── main.c            # CLI and interactive interface
└── tests/
    └── test_calculator.c # Unit test suite
```

---

## Docker Instructions

### 1. Build the Docker Image
```bash
docker build -t sttcse-calculator -t adder:latest .
```

### 2. Run Single Calculations via Container
```bash
docker run --rm sttcse-calculator 10 + 5
docker run --rm sttcse-calculator 100 - 37
docker run --rm sttcse-calculator 12 '*' 8
docker run --rm sttcse-calculator 144 / 12
docker run --rm sttcse-calculator 2 ^ 8
docker run --rm sttcse-calculator sqrt 144
docker run --rm sttcse-calculator fact 5
```

### 3. Run Interactive Calculator in Container
```bash
docker run -it --rm sttcse-calculator
```

### 4. Run Unit Tests Inside Container
```bash
docker run --rm --entrypoint make sttcse-calculator test
```

---

## Native Build Instructions

Use `make` to compile locally:

```bash
make
```

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

### 2. Command-Line Arguments Mode
Run one-off expressions directly:
```bash
./calculator 10 + 5
./calculator 22 / 7
./calculator 2 ^ 10
./calculator sqrt 144
./calculator fact 6
```
