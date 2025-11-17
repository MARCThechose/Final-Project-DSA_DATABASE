# Database Administration Viewer

A C++ desktop application that provides a real-time view of database administration data using ImGui, GLFW, and MySQL Connector/C++.

## Overview

This application connects to a MySQL database and displays admin data in a formatted table interface. It queries the `Admin` table every 60 frames and presents the data in a clean, scrollable table format with columns for Admin_ID, Name, Username, and Password.

## Dependencies

### Required Libraries
- **GLFW 3.3+** - Cross-platform window management
- **Dear ImGui** - Immediate mode GUI library  
- **OpenGL 3.3+** - Graphics rendering
- **MySQL Connector/C++** - Database connectivity
- **CMake 3.10+** - Build system

### System Requirements
- C++17 compatible compiler
- OpenGL 3.3 capable graphics driver
- MySQL server (local or remote)

## Platform-Specific Setup

### Windows Setup

#### Prerequisites Installation

1. **Git for Windows**
   - Download from: https://git-scm.com/download/win
   - Install with default settings

2. **Visual Studio 2022 Community**
   - Download from: https://visualstudio.microsoft.com/downloads/
   - During installation, **ensure "Desktop development with C++" workload is selected**
   - This installs MSVC compiler, Windows SDK, and necessary build tools

3. **CMake**
   - Download from: https://cmake.org/download/
   - Download "Windows x64 Installer"
   - **Important:** Check "Add CMake to the system PATH" during installation

4. **MySQL Connector/C++**
   - Download from: https://dev.mysql.com/downloads/connector/cpp/
   - Select "Windows (x86, 64-bit), ZIP Archive"
   - Extract to a memorable location (e.g., `C:\mysql-connector-c++`)

#### Build Instructions

1. **Clone Repository with Submodules**
   ```cmd
   git clone --recurse-submodules <REPOSITORY_URL>
   cd FinalDSATABASE
   ```
   
   If you forget `--recurse-submodules`:
   ```cmd
   git submodule init
   git submodule update
   ```

2. **Configure Build Environment**
   - Open "Developer Command Prompt for VS 2022" from Start Menu
   - Navigate to project directory

3. **Configure CMake with MySQL Path**
   ```cmd
   mkdir build
   cd build
   cmake .. -DMySQL_INCLUDE_DIR="C:\mysql-connector-c++\include" -DMySQL_LIBRARY="C:\mysql-connector-c++\lib64\mysqlcppconn.lib"
   ```

4. **Build Project**
   ```cmd
   cmake --build . --config Release
   ```

5. **Run Application**
   - Executable located at: `build\Release\datasets.exe`
   - Ensure MySQL connector DLL is in PATH or copy to executable directory

### Linux Setup (Ubuntu/Debian)

#### Install Dependencies
```bash
sudo apt update
sudo apt install build-essential cmake git libgl1-mesa-dev libglfw3-dev libmysqlcppconn-dev
```

#### Build Instructions
```bash
git clone --recurse-submodules <REPOSITORY_URL>
cd FinalDSATABASE
mkdir build && cd build
cmake ..
make -j$(nproc)
./datasets
```

## Database Configuration

### MySQL Database Setup

1. **Create Database**
   ```sql
   CREATE DATABASE Container_Inv_Sys;
   ```

2. **Create Admin Table**
   ```sql
   USE Container_Inv_Sys;
   CREATE TABLE Admin (
       Admin_ID INT PRIMARY KEY AUTO_INCREMENT,
       Name VARCHAR(255) NOT NULL,
       Username VARCHAR(255) UNIQUE NOT NULL,
       Password VARCHAR(255) NOT NULL
   );
   ```

3. **Create User (Optional)**
   ```sql
   CREATE USER 'machina_joel'@'localhost' IDENTIFIED BY 'your_password';
   GRANT SELECT ON Container_Inv_Sys.* TO 'machina_joel'@'localhost';w   FLUSH PRIVILEGES;
   ```

### Connection Configuration

The application connects using these parameters (modify in `src/helloworld.cpp:62`):
- **Host:** `127.0.0.1:3306`
- **Database:** `Container_Inv_Sys`
- **Username:** `machina_joel`
- **Password:** (empty by default)

Update the connection string if your configuration differs:
```cpp
con = driver->connect("tcp://YOUR_HOST:3306/YOUR_DATABASE", "YOUR_USERNAME", "YOUR_PASSWORD");
```

## Usage

1. **Launch Application**
   - Run the executable after successful build

2. **Interface**
   - Admin data displays in a formatted table
   - Data refreshes automatically every ~1 second (60 frames)
   - Press `ESC` or close window to exit

3. **Features**
   - Real-time data synchronization
   - Scrollable table view
   - Column headers with borders
   - Error handling for database connection issues

## Troubleshooting

### Common Issues

**"MySQL connection failed"**
- Verify MySQL server is running
- Check connection parameters in source code
- Ensure user has proper database permissions
- Confirm firewall isn't blocking port 3306

**"GLFW window creation failed"**
- Update graphics drivers
- Ensure OpenGL 3.3+ support
- Try running with different graphics settings

**"CMake cannot find MySQL"**
- Verify MySQL Connector/C++ is installed
- Check include/library paths in CMake configuration
- On Windows, ensure paths use forward slashes or escaped backslashes

**Build errors on Windows**
- Use "Developer Command Prompt for VS 2022"
- Verify "Desktop development with C++" workload is installed
- Check CMake is in system PATH

### Debug Mode

For debugging, build with Debug configuration:
```cmd
cmake --build . --config Debug
```

## Project Structure

```
FinalDSATABASE/
├── src/
│   └── helloworld.cpp          # Main application source
├── external/
│   ├── glfw/                  # GLFW submodule (window management)
│   └── imgui/                 # ImGui submodule (GUI library)
├── CMakeLists.txt             # Build configuration
├── .gitmodules               # Submodule configuration
└── README.md                 # This file
```

## License

This project uses third-party libraries with their respective licenses:
- GLFW: zlib/libpng License
- Dear ImGui: MIT License  
- MySQL Connector/C++: GPL v2

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test on multiple platforms if possible
5. Submit a pull request
