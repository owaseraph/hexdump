# hexdump

Small command-line hexdump utility that prints file contents in a readable hex + ASCII format.

## Features
- Configurable bytes per line (8, 16, or 32)
- Optional ASCII column (hide with -A)
- Seek to start offset (-o)
- Limit number of bytes to read (-n)
- Extra gap after half the line for readability

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
.\build\Release\hexdump.exe [options] <file>
```

Or with Ninja:
```powershell
cmake -S . -B build -G Ninja
cmake --build build
.\build\hexdump.exe [options] <file>
```

## Usage
```
hexdump [options] <file>
```

Options:
- -w 8|16|32   Set bytes per line (default: 16). Only 8, 16, and 32 are accepted.
- -A           Hide ASCII column (print hex only).
- -o <offset>  Seek to start offset (bytes from start of file).
- -n <bytes>   Limit total bytes to read.

Examples:
```
# default 16 bytes per line with ASCII
hexdump file.bin

# 8 bytes/line, hide ASCII
hexdump -w 8 -A file.bin

# start at offset 1024 and read 256 bytes
hexdump -o 1024 -n 256 file.bin
```

## Example output
```
00000000  63 65 76 61 20 63 65 76  61 20 63 65 76 61       |ceva ceva ceva|
```

## Contributing
Fixes and small improvements welcome. Open an issue or submit a pull request.

## Development
I will add a GUI version later.
