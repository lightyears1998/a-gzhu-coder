# Build task for bridge.cpp
g++ bridge.cpp third-party/table_printer.cpp -o bridge.exe

# Build task for checksum.cpp
g++ checksum.cpp -o checksum.exe
