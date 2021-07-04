# Address book program

## Abstract
The program implements a digital address book, which users can add, delete, and update records of a person's details (first name, last name, email, telephone) through an interactive command line interface. The information is stored in a local SQLite database.

## Build
The project uses the [SQLite3 C/C++ API](https://www.sqlite.org/cintro.html) to read the SQLite database, [daniele77/cli](https://github.com/daniele77/cli) to make the CLI interface, and [nlohmann-json](https://github.com/nlohmann/json) to read the JSON file.
### Installing packages
MSYS (MinGW):
```Shell
pacman -S mingw-w64-x86_64-nlohmann-json mingw-w64-x86_64-sqlite3 mingw-w64-x86_64-cmake
```
vcpkg (Visual C++):
```Shell
vcpkg install sqlite3:x64-windows nlohmann-json:x64-windows
```
APT (Ubuntu / Debian)[^1]:
```Shell
apt install nlohmann-json3-dev libsqlite3-dev
```

### Building
```Shell
mkdir build
cd build

# vcpkg:
cmake -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake ..

# Others:
cmake ..

cmake --build .
```

## Usage
Start the main program *address-book*:
```Shell
# Windows
address-book
# Linux / MacOS
./address-book
```
For a demo example, see [DEMO.md](DEMO.md)

[^1]: On older versions of CMake, the script `FindSqlite3.cmake` might be non-existent, which makes CMake failing to find the sqlite3 library. You will have update to a newer version or load the script manually.
