# Database Administration Viewer

A cross-platform C++ desktop application that provides a real-time view of database administration data using ImGui, GLFW, and MySQL Connector/C++.

## Overview

This application connects to a MySQL database and displays admin data in a formatted table interface. It queries the `admin` table every 60 frames and presents the data in a clean, scrollable table format with columns for Admin_ID, Name, Username, and Password.

**✅ Cross-Platform Support:** Works on both Windows and Linux with automatic platform detection.

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
- VS Code with C++ extensions (recommended)

## Platform-Specific Setup

### Windows Setup

#### VS Code and Development Environment Setup

1. **Install Git for Windows**
   - Download from: https://git-scm.com/download/win
   - Install with default settings
   - This provides Git Bash and Git integration

2. **Install VS Code**
   - Download from: https://code.visualstudio.com/
   - Install with default settings

3. **Install VS Code Extensions**
   - Open VS Code
   - Go to Extensions (Ctrl+Shift+X)
   - Install these essential extensions:
     - **C/C++** (Microsoft) - C++ language support
     - **CMake Tools** (Microsoft) - CMake integration
     - **CMake** (twxs) - CMake language support

4. **Install C++ Compiler**
   
   **Option A: MinGW-w64 (Recommended for VS Code)**
   - Download from: https://www.mingw-w64.org/downloads/
   - Choose x86_64 architecture, POSIX threads, sjlj exceptions
   - Extract to `C:\mingw64`
   - Add to PATH: `C:\mingw64\bin`
   
   **Option B: Visual Studio Build Tools (Alternative)**
   - Download from: https://visualstudio.microsoft.com/downloads/
   - Scroll to "Tools for Visual Studio"
   - Download "Build Tools for Visual Studio 2022"
   - During install, select "Desktop development with C++"

5. **Install CMake**
   - Download from: https://cmake.org/download/
   - Download "Windows x64 Installer"
   - **Important:** Check "Add CMake to the system PATH" during installation

6. **Verify Installation**
   - Open Command Prompt or PowerShell
   - Test each tool:
   ```cmd
   gcc --version          # Should show MinGW/GCC version
   cmake --version        # Should show CMake version
   git --version          # Should show Git version
   ```

7. **Install MySQL Connector/C++**
   - Download from: https://dev.mysql.com/downloads/connector/cpp/
   - Select "Windows (x86, 64-bit), ZIP Archive"
   - Extract to a memorable location (e.g., `C:\mysql-connector-c++`)
   - **Note:** The CMakeLists.txt automatically detects common installation paths

#### VS Code Project Setup

1. **Open Project in VS Code**
   ```cmd
   cd C:\path\to\Final-Project-DSA_DATABASE
   code .
   ```

2. **Configure VS Code**
   - VS Code will detect CMake project and prompt for configuration
   - Select your compiler kit (GCC for MinGW, or Visual Studio)
   - Choose "Release" build type

3. **Build Using VS Code**
   - Open Command Palette: `Ctrl+Shift+P`
   - Type: `CMake: Configure` (runs cmake configuration)
   - Type: `CMake: Build` (builds the project)
   - Type: `CMake: Run Without Debugging` (runs the application)

4. **Alternative: Use Integrated Terminal**
   - Open Terminal: `Ctrl+`` (backtick)
   - Run build commands manually (see Build Instructions below)

#### Build Instructions

1. **Clone Repository with Submodules**
   ```cmd
   git clone --recurse-submodules <REPOSITORY_URL>
   cd Final-Project-DSA_DATABASE
   ```
   
   If you forget `--recurse-submodules`:
   ```cmd
   git submodule init
   git submodule update
   ```

2. **Configure Build Environment**
   - Open VS Code or Command Prompt
   - Navigate to project directory

3. **Configure CMake**
   ```cmd
   mkdir build
   cd build
   cmake ..
   ```
   - **Cross-platform CMakeLists.txt** automatically detects Windows and finds MySQL Connector/C++
   - If MySQL is not found, manually specify paths:
   ```cmd
   cmake .. -DMySQL_INCLUDE_DIR="C:/Program Files/MySQL/MySQL Connector C++ 9.5/include/jdbc" -DMySQL_LIBRARY="C:/Program Files/MySQL/MySQL Connector C++ 9.5/lib64/vs14/mysqlcppconn.lib"
   ```

4. **Build Project**
   ```cmd
   cmake --build . --config Release
   ```

5. **Copy Required DLLs**
   ```cmd
   copy "C:\Program Files\MySQL\MySQL Connector C++ 9.5\lib64\mysqlcppconn-10-vs14.dll" "build\Release\"
   copy "C:\Program Files\MySQL\MySQL Connector C++ 9.5\lib64\libssl-3-x64.dll" "build\Release\"
   copy "C:\Program Files\MySQL\MySQL Connector C++ 9.5\lib64\libcrypto-3-x64.dll" "build\Release\"
   copy "C:\Program Files\MySQL\MySQL Connector C++ 9.5\lib64\plugin\mysql_native_password.dll" "build\Release\"
   ```

6. **Run Application**
   ```cmd
   cd build\Release
   datasets.exe
   ```

### Linux Setup (Ubuntu/Debian)

#### Install Dependencies
```bash
sudo apt update
sudo apt install build-essential cmake git libgl1-mesa-dev libglfw3-dev libmysqlcppconn-dev
```

#### Build Instructions
```bash
git clone --recurse-submodules <REPOSITORY_URL>
cd Final-Project-DSA_DATABASE
mkdir build && cd build
cmake ..
make -j$(nproc)
./datasets
```

**Note:** The cross-platform CMakeLists.txt automatically detects Linux and uses the correct paths.

## Database Configuration

### MySQL Database Setup

1. **Create Database**
   ```sql
   CREATE DATABASE container_inv_sys;
   ```

2. **Create Admin Table**
   ```sql
   USE container_inv_sys;
   CREATE TABLE admin (
       Admin_ID INT PRIMARY KEY AUTO_INCREMENT,
       Name VARCHAR(255) NOT NULL,
       Username VARCHAR(255) UNIQUE NOT NULL,
       Password VARCHAR(255) NOT NULL
   );
   ```

3. **Add Sample Data (Optional)**
   ```sql
   INSERT INTO admin (Name, Username, Password) VALUES 
   ('Admin User', 'admin', 'password123'),
   ('John Doe', 'johndoe', 'johnpass'),
   ('Jane Smith', 'janesmith', 'janepass');
   ```

4. **Create Application User**
   ```sql
   CREATE USER 'machina_joel'@'localhost' IDENTIFIED WITH mysql_native_password BY '';
   GRANT SELECT ON container_inv_sys.* TO 'machina_joel'@'localhost';
   FLUSH PRIVILEGES;
   ```

### Connection Configuration

The application connects using these parameters (modify in `src/helloworld.cpp:62`):
- **Host:** `127.0.0.1:3306`
- **Database:** `container_inv_sys`
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
- The cross-platform CMakeLists.txt automatically detects common paths
- On Windows, ensure paths use forward slashes or escaped backslashes
- Manual path specification: `cmake .. -DMySQL_INCLUDE_DIR="path/to/include" -DMySQL_LIBRARY="path/to/library"`

**"Authentication plugin 'mysql_native_password' cannot be loaded"**
- Copy `mysql_native_password.dll` from MySQL Connector to executable directory
- Copy all authentication plugins: `copy "C:\Program Files\MySQL\MySQL Connector C++ 9.5\lib64\plugin\*" "build\Release\"`
- Ensure user is created with `mysql_native_password` authentication

**Build errors on Windows**
- Use VS Code with C/C++ and CMake Tools extensions
- Verify C++ compiler is installed (MinGW or Visual Studio Build Tools)
- Check CMake is in system PATH
- Ensure all required DLLs are copied to executable directory
- Test compiler: `gcc --version` or `cl --version`

### Debug Mode

For debugging, build with Debug configuration:

**Using VS Code:**
1. Open Command Palette: `Ctrl+Shift+P`
2. Type: `CMake: Configure`
3. Select "Debug" build type
4. Type: `CMake: Build`
5. Set breakpoints and use F5 to debug

**Using Terminal:**
```cmd
cmake --build . --config Debug
```

## Project Structure

```
Final-Project-DSA_DATABASE/
├── src/
│   └── helloworld.cpp          # Main application source
├── external/
│   ├── glfw/                  # GLFW submodule (window management)
│   └── imgui/                 # ImGui submodule (GUI library)
├── build/
│   └── Release/
│       ├── datasets.exe       # Built executable (Windows)
│       └── *.dll              # Required MySQL DLLs
├── CMakeLists.txt             # Cross-platform build configuration
├── .gitmodules               # Submodule configuration
└── README.md                 # This file
```

## License

This project uses third-party libraries with their respective licenses:
- GLFW: zlib/libpng License
- Dear ImGui: MIT License  
- MySQL Connector/C++: GPL v2

## Contributing (For Complete Beginners)

New to programming? No problem! This guide will walk you through every step of contributing to this project.

### What is "Contributing"?
Contributing means helping improve this project. You can:
- Fix problems (bugs)
- Add new features
- Improve instructions (like this README)
- Help other users

### Why Should You Contribute?
- **Learn real skills** - Git, GitHub, and teamwork
- **Build your resume** - Show employers you can work on real projects
- **Help others** - Your changes might help thousands of users
- **Join a community** - Meet other programmers

### What You Need Before Starting

#### **Required Tools (Already installed if you followed setup):**
1. **Git** - For tracking changes
2. **VS Code** - For editing code
3. **GitHub Account** - Free at github.com

#### **Important Concepts to Understand:**
- **Repository (Repo)**: A folder that contains all project files
- **GitHub**: Website that hosts repositories online
- **Fork**: Your personal copy of someone else's repository
- **Clone**: Download a repository to your computer
- **Commit**: Save your changes with a message
- **Pull Request (PR)**: Ask the original author to include your changes

---

## Step-by-Step Contribution Guide

### Step 1: Create a GitHub Account
1. Go to https://github.com
2. Click "Sign up"
3. Fill in your details (it's free!)
4. Verify your email

### Step 2: Fork the Repository
1. Go to the project's GitHub page
2. Click the **"Fork"** button (top-right corner)
3. This creates YOUR copy of the project

**What this means:** You now have your own version where you can make changes without affecting the original.

### Step 3: Clone Your Fork to Your Computer
1. Go to YOUR fork (it should say your username)
2. Click the green **"Code"** button
3. Copy the URL (it looks like `https://github.com/YOUR_USERNAME/Final-Project-DSA_DATABASE.git`)
4. Open VS Code
5. Open Terminal: `Ctrl+`` (backtick key)
6. Type this command:
```bash
git clone PASTE_THE_URL_HERE
```
7. Navigate into the project:
```bash
cd Final-Project-DSA_DATABASE
```

**What this means:** You now have the project files on your computer to work with.

### Step 4: Make Your Changes
1. **Find something to improve:**
   - Fix a typo in the README
   - Add a helpful comment to the code
   - Improve instructions
   - Fix a bug you found

2. **Edit the files in VS Code:**
   - Open the file you want to change
   - Make your changes
   - Save the file (`Ctrl+S`)

3. **Test your changes:**
   - Try to build and run the project
   - Make sure it still works

### Step 5: Save Your Changes with Git
1. **Check what you changed:**
```bash
git status
```
   - This shows which files you modified

2. **See exactly what changed:**
```bash
git diff
```
   - This shows the specific lines you added/removed

3. **Tell Git which changes to save:**
```bash
git add .
```
   - This stages all your changes

4. **Save your changes with a message:**
```bash
git commit -m "Fix: Add better instructions for MySQL setup"
```

**Important:** Write a clear message that explains WHAT you changed and WHY.

**Good examples:**
- `Fix: Correct typo in README installation steps`
- `Docs: Add VS Code setup instructions`
- `Fix: Resolve MySQL connection error`

**Bad examples:**
- `update`
- `stuff`
- `asdf`

### Step 6: Upload Your Changes to GitHub
1. **Push your changes:**
```bash
git push
```
   - This uploads your changes to YOUR fork on GitHub

### Step 7: Create a Pull Request
1. Go to YOUR fork on GitHub
2. You should see a yellow banner saying "This branch is X commits ahead"
3. Click **"Contribute"** then **"Open pull request"**
4. Fill out the form:
   - **Title:** Brief description of your change
   - **Description:** Explain what you did and why it's helpful
5. Click **"Create pull request"**

**What this means:** You're asking the original project author to include your changes.

### Step 8: Wait for Review
- The project author will review your changes
- They might ask for changes (this is normal!)
- If they ask for changes:
  1. Make the changes in VS Code
  2. Save and commit again
  3. Push again
  4. The pull request will update automatically

### Step 9: Celebrate! 🎉
- When your pull request is merged, your changes are now part of the official project!
- You've officially contributed to open source!

---

## Common Problems and Solutions

### **Problem: "git command not found"**
**Solution:** Make sure Git is installed. Go back to the setup section and install Git.

### **Problem: "Permission denied"**
**Solution:** You might need to set up SSH keys or use HTTPS. For beginners, HTTPS is easier.

### **Problem: "Merge conflict"**
**Solution:** This happens when someone else changed the same file. Ask for help - it's normal!

### **Problem: "I don't know what to change"**
**Solution:** Look for:
- Typos in the README
- Unclear instructions
- Missing information
- Code comments that could be clearer

---

## Quick Reference Commands

### **Every time you want to contribute:**
```bash
# Get latest changes
git pull

# Make your changes in VS Code

# Check what changed
git status

# Save your changes
git add .
git commit -m "Your message here"

# Upload to GitHub
git push
```

### **Useful commands:**
```bash
git log                    # See history of changes
git checkout filename      # Undo changes to a file
git branch                 # See what branch you're on
```

---

## What Happens Next?

### **After Your First Contribution:**
- Try fixing a small bug
- Add a new feature
- Help answer questions from other new contributors
- Become a regular contributor!

### **Skills You're Learning:**
- **Version Control** - How professional developers work
- **Collaboration** - Working with other developers
- **Code Review** - Giving and receiving feedback
- **Professional Communication** - How to discuss technical changes

---

## Need Help?

### **Places to Ask:**
1. **GitHub Issues** - Ask questions about the project
2. **GitHub Discussions** - General conversations
3. **Online Communities** - Stack Overflow, Reddit r/learnprogramming

### **Search Terms to Use:**
- "how to git pull request"
- "git for beginners"
- "github contribution guide"
- "how to fix merge conflict"

---

## You Can Do This! 💪

Every professional developer was once a beginner. Contributing to open source is one of the best ways to learn and grow.

**Remember:**
- It's okay to make mistakes
- It's okay to ask for help
- Small contributions matter
- You're learning valuable skills

**Your first contribution is the hardest. After that, it gets much easier!**

### Thank You for Contributing! 🎉

Whether you fix a typo or add a major feature, you're helping make this project better for everyone.
