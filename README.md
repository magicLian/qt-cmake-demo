# Qt CMake Demo

A Qt application built with CMake, demonstrating the integration of Qt with CMake and the use of Qt Designer.

## Prerequisites

- CMake 3.16 or higher
- Qt 5 development packages
- C++ compiler supporting C++17

## Building the Project

1. Create a build directory:
   ```
   mkdir build
   ```

2. Configure the project:
   ```
   cmake -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH=<Qt installation path> -DCMAKE_BUILD_TYPE=Release -B build -S .
   ```
   
3. Build the project:
   ```
   cmake --build build
   ```
4. Deploy the application:
   ```
   windeployqt build/QtCMakeDemo.exe
   ```

## Running the Application

After building, you can run the application from the build directory:

```
cd build
./QtCMakeDemo.exe
```

## Project Structure

- `include/`: Header files
- `src/`: Source files
- `ui/`: Qt Designer UI files
- `resources/`: Resource files (images, icons, etc.)
- `CMakeLists.txt`: Main CMake configuration file

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details. 