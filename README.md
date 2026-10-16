# BI-PA2.21-clean

## Development

This section describes how to build this project on your own.

### Windows

1. Install Prerequisites. Open PowerShell as Administrator and run:
```
   winget install --id Git.Git -e
   winget install --id Kitware.CMake -e
   winget install --id Microsoft.VisualStudio.2022.BuildTools --force --override "--passive --wait --add Microsoft.VisualStudio.Workload.VCTools --includeRecommended"
```
2. Install and Set Up vcpkg:
```
   cd %USERPROFILE%
   git clone https://github.com/microsoft/vcpkg.git
   cd vcpkg
   .\bootstrap-vcpkg.bat
   setx VCPKG_ROOT "%USERPROFILE%\vcpkg"
```
   (Restart your terminal or VS Code after setting VCPKG_ROOT)

4. Clone and Build:
```
   cd %USERPROFILE%\Documents
   git clone https://github.com/vojtech-git/BI-PA2.21-clean
   cd BI-PA2.21-clean
   cmake --preset windows-vcpkg
   cmake --build build --config Debug
```
5. Run:
```
   .\build\Debug\CleanBomberman.exe
```

### Ubuntu

1. Install Build Tools and Dependencies:
```
   sudo apt update
   sudo apt install -y build-essential cmake git libncurses-dev
```

2. Clone and Build:
```
   cd ~/Documents
   git clone https://github.com/vojtech-git/BI-PA2.21-clean.git
   cd BI-PA2.21-clean
   cmake --preset linux-default
   cmake --build build
```

3. Run:
```
   ./build/CleanBomberman
```
