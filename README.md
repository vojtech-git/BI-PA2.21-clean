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
2. Open the Developer Command Prompt for VS 2022.
3. Download and compile PDCurses:
```
   git clone https://github.com/wmcbrine/PDCurses.git
   cd PDCurses\wincon
   nmake -f Makefile.vc
```
4. Setup library paths:
```
   Create C:\pdcurses\include and copy curses.h from the PDCurses root folder.
   Create C:\pdcurses\lib and copy pdcurses.lib from the wincon folder.
```
6. Extract BI-PA2.21-clean.zip and navigate into the project root.
7. Configure and build the project:
```
   cmake -B build -S .
   cmake --build build
```
8. Run the executable:
```
   .\build\Debug\CleanBomberman.exe
```

   ### Ubuntu

1. Install the base compilation tools:
```
   sudo apt update
   sudo apt install build-essential cmake wget tar
```
2. Download and compile ncurses from source:
```
   wget https://ftp.gnu.org/pub/gnu/ncurses/ncurses-6.4.tar.gz
   tar -xzf ncurses-6.4.tar.gz
   cd ncurses-6.4
   ./configure --with-shared
   make
   sudo make install
```
3. Extract BI-PA2.21-clean.zip and navigate into the project root.
4. Configure and build the project:
```
   cmake -B build -S .
   cmake --build build
```
5. Run the executable:
```
   ./build/CleanBomberman
```
