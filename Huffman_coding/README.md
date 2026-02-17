# Huffman Coding

## Build from **this directory**

**CMake:**  
cmake -S . -B build  
cmake --build build  

**Makefile (recommended - clean build):**  
make build-clean

**Binary created in current directory** (same level as `main.c`)

## Usage
Put a file which you would like to encrypt in this directory and use command line argument in this manner:
./Huffman_coding input.txt

Generated files (same directory):
- output.bin (encoded binary)
- output.txt (decoded - should match input.txt)

## Workflow
input.txt → [encode] → output.bin → [decode] → output.txt (should match input.txt)

## Example
echo "Hello World" > input.txt  
./Huffman_coding  
diff input.txt output.txt (should be empty - perfect match)  
ls -la output.bin # Compressed binary

