cat > README.md <<'EOF'
# DSA Lab 11

This repository contains two C++ programs that use binary heaps.

## Task 1: Huffman Coding

The program builds a Huffman tree from distinct characters and their frequencies, then prints each character's Huffman code.

Compile and run:

```bash
g++ -std=c++17 task1_huffman.cpp -o task1
./task1

Enter the distinct characters on the first line and their frequencies, in the same order, on the second line.

Example input:
abc
1 4 5

Expected output:
c: 0
a: 10
b: 11