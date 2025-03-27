# Qt CMake Demo

A simple Qt application built with CMake.

## Prerequisites

- CMake 3.16 or higher
- Qt 5 packages
- C++ compiler supporting C++17

## Building the Project

1. Create a build directory:
   ```
   mkdir build
   cd build
   ```

2. Configure the project:
   ```
   cmake ..
   ```

3. Build the project:
   ```
   cmake --build .
   ```

## Running the Application

After building, you can run the application from the build directory:

```
./QtCMakeDemo
```

## Project Structure

- `include/`: Header files
- `src/`: Source files
- `resources/`: Resource files (images, icons, etc.)
- `CMakeLists.txt`: Main CMake configuration file 