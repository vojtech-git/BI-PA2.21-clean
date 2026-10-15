# BI-PA2.21-clean

## Development

This section describes how to build this project on your own.

### Windows

1. Open PowerShell as Administrator and install the required build tools and utilities:
```
   winget install --id Git.Git -e
   winget install --id Kitware.CMake -e
   winget install --id Microsoft.VisualStudio.2022.BuildTools --force --override "--passive --wait --add Microsoft.VisualStudio.Workload.VCTools --includeRecommended"
```
2. Open the "x64 Native Tools Command Prompt for VS 2022" from the Windows Start menu (do not use the standard Developer Command Prompt/PowerShell).
3. Navigate to your Documents folder, download, and compile the 64-bit PDCurses library:
```
   cd %USERPROFILE%\Documents
   git clone https://github.com/wmcbrine/PDCurses.git
   cd PDCurses\wincon
   nmake -f Makefile.vc
```
4. Setup library paths and copy the compiled files:
```
   mkdir C:\pdcurses\include
   mkdir C:\pdcurses\lib
   copy %USERPROFILE%\Documents\PDCurses\curses.h C:\pdcurses\include\
   copy %USERPROFILE%\Documents\PDCurses\wincon\pdcurses.lib C:\pdcurses\lib\
```
5. Navigate back to your Documents folder, clone the project repository, and navigate into it:
```
   cd %USERPROFILE%\Documents
   git clone https://github.com/vojtech-git/BI-PA2.21-clean
   cd BI-PA2.21-clean
```
6. Configure and build the project:
```
   cmake -B build -S .
   cmake --build build
```
7. Run the executable:
```
   .\build\Debug\CleanBomberman.exe
```

   ### Ubuntu

1. Install build tools, git, and ncurses development files:
```
sudo apt update
sudo apt install -y build-essential cmake git libncurses-dev
```

2. Clone the project repository and navigate into it:
```
cd ~
git clone https://github.com/vojtech-git/BI-PA2.21-clean.git
cd BI-PA2.21-clean
```

3. Configure and build the project:
```
cmake -B build -S .
cmake --build build
```

4. Run the executable:
```
./build/CleanBomberman
```
