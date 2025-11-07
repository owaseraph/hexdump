# hexdump

Small command-line hexdump utility that prints file contents in a readable hex + ASCII format.

## Features
- 16 bytes per line with an extra gap after 8 bytes
- Printable ASCII shown on the right, non-printable shown as `.`

## Prerequisites
- C compiler (MSVC, clang, or gcc)
- CMake 3.16+

## Build (PowerShell)
```powershell
# configure
cmake -S . -B build

# build (Debug by default) or specify Release
cmake --build build --config Release

# run
.\build\Release\hexdump.exe path\to\file.bin
```

Or with Ninja:
```powershell
cmake -S . -B build -G Ninja
cmake --build build
.\build\hexdump.exe path\to\file.bin
```

## Usage
```
hexdump <file>
```

Example output:
```
00000000  63 65 76 61 20 63 65 76  61 20 63 65 76 61       |ceva ceva ceva|
```

## Contributing
Fixes and small improvements welcome. Open an issue or submit a pull request.

## License
Add a LICENSE file (e.g., MIT) to indicate the project license.