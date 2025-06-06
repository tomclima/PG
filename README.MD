# PG_Project

## Prerequisites

To build and run this project, you will need:
* **Git**
* **CMake** (version 3.15 or higher recommended)
* A **C++17 compliant compiler** (e.g., GCC, Clang, MSVC)

## Building the Project

This project uses **CMake Presets** (`CMakePresets.json`) to manage all build configurations. This is the recommended way to configure and build.

The following presets are available:

* **`debug`**: Compiles in Debug mode with tests enabled. Ideal for development.
* **`release`**: Compiles in Release mode with optimizations and without tests. Ideal for production/distribution.

### Instructions (Command Line)

1.  **Clone the repository:**
    ```sh
    git clone <repository-url>
    cd <repository-name>
    ```

2.  **Configure the project using a preset:**
    *This step only needs to be done once, or when you want to switch presets.*
    ```sh
    # To configure a debug build with tests
    cmake --preset debug

    # OR

    # To configure a release build without tests
    cmake --preset release
    ```
    This will generate a `build/debug` or `build/release` directory with the necessary build files.

3.  **Build the project:**
    ```sh
    # To build the active debug configuration
    cmake --build --preset debug

    # OR

    # To build the active release configuration
    cmake --build --preset release
    ```
---

## Running the Application

The executable (`PG_Project`) will be located in the `bin` subdirectory of your build folder.

```sh
# Example for the debug build
./build/debug/bin/PG_Project
```

---

## Running Tests

Tests are only available in the **`debug`** preset.

1.  Make sure you have configured and built the project using the `debug-tests-on` preset.

2.  **Run from the command line:**
    ```sh
    # Run all tests
    ctest --preset test

    # Run tests with detailed output
    ctest --preset test --verbose
    ```
---

## Installation

This project includes rules to create a clean, distributable package in a local `install` directory. This is useful for testing the final deployment or for packaging your application.

1.  First, configure and build the project (e.g., using the `release` preset).

2.  Run the install command from the **root directory of the project**:
    ```sh
    # This will install the release build into the `install/release` directory
    cmake --install build/release
    ```
    The `install/release` folder will then contain the `PG_Project` executable and the `libPrism.so` (or `Prism.dll`) library, ready to be run together.
# PG_Project

A C++ project featuring the Prism vector library, built with a modern and robust CMake configuration.

This project is configured to be built as a shared library (`Prism`) and an executable (`PG_Project`) that uses it.

## Prerequisites

To build and run this project, you will need:
* **Git**
* **CMake** (version 3.15 or higher recommended)
* A **C++17 compliant compiler** (e.g., GCC, Clang, MSVC)

## Building the Project

This project uses **CMake Presets** (`CMakePresets.json`) to manage all build configurations. This is the recommended way to configure and build.

The following presets are available:

* **`debug`**: Compiles in Debug mode with tests enabled. Ideal for development.
* **`release`**: Compiles in Release mode with optimizations and without tests. Ideal for production/distribution.

### Instructions (Command Line)

1.  **Clone the repository:**
    ```sh
    git clone <your-repository-url>
    cd PG-Prism_development
    ```

2.  **Configure the project using a preset:**
    *This step only needs to be done once, or when you want to switch presets.*
    ```sh
    # To configure a debug build with tests
    cmake --preset debug

    # OR

    # To configure a release build without tests
    cmake --preset release
    ```
    This will generate a `build/debug` or `build/release` directory with the necessary build files.

3.  **Build the project:**
    ```sh
    # To build the active debug configuration
    cmake --build --preset debug

    # OR

    # To build the active release configuration
    cmake --build --preset release
    ```
---

## Running the Application

The executable (`PG_Project`) will be located in the `bin` subdirectory of your build folder.

```sh
# Example for the debug build
./build/debug/bin/PG_Project
```

---

## Running Tests

Tests are only available in the **`debug`** preset.

1.  Make sure you have configured and built the project using the `debug-tests-on` preset.

2.  **Run from the command line:**
    ```sh
    # Run all tests
    ctest --preset test

    # Run tests with detailed output
    ctest --preset test --verbose
    ```
---

## Installation

This project includes rules to create a clean, distributable package in a local `install` directory. This is useful for testing the final deployment or for packaging your application.

1.  First, configure and build the project (e.g., using the `release` preset).

2.  Run the install command from the **root directory of the project**:
    ```sh
    # This will install the release build into the `install/release` directory
    cmake --install build/release
    ```
    The `install/release` folder will then contain the `PG_Project` executable and the `libPrism.so` (or `Prism.dll`) library, ready to be run together.