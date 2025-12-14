# C Data Structures & Tricks 🎯

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

**Clean, efficient C implementations** from **CLRS (Cormen)**:

## 📺 **Must-Watch: Charles Cabergs "Advanced C"**  
YouTube series — [Charles Cberg Advanced C](https://www.youtube.com/@CharlesCberg)

## 📚 **Recommended Books** (read **originals** in English!)
- *Introduction to Algorithms* by Cormen et al. (CLRS) — **data structures source**  
- *Modern C* by Jens Gustedt  
- *Expert C Programming* by Peter van der Linden  

> **These are MUST-READS for serious C programmers.**

## 📋 Implemented Data Structures (from CLRS)
| Module | Complexity | Description |
|--------|------------|-------------|
| [Binary Tree](./Binary_tree) | O(log n) | Balanced tree operations |
| [Red-Black Tree](./Red_black_tree) | O(log n) | Self-balancing BST |
| [Doubly Linked List](./Doubly_linked_list) | O(1) | Bidirectional traversal |
| [Heap](./Heap) | O(log n) | Priority queue |
| [Huffman Coding](./Huffman_coding) | O(n log n) | Optimal prefix codes |

## Quick Build (from root)

**CMake (recommended):**  
cmake -S Binary_tree -B Binary_tree/build  
cmake --build Binary_tree/build  
cd Binary_tree/build && ./Binary_tree  

**Makefile:**  
make -C Binary_tree  
cd Binary_tree/build && ./Binary_tree  

## ⚠️ **Binary Location Note**
- **Most modules**: Binary in `Module/build/` (run from `build/`)
- **Huffman Coding** works differently: Binary in `Huffman_coding/` (next to `main.c`)

**Huffman example:**  
cmake -S Huffman_coding -B Huffman_coding/build  
cmake --build Huffman_coding/build  
cd Huffman_coding && ./Huffman_coding  

## C_tricks
15 examples from above books.
See [C_tricks/README.md](C_tricks/README.md) for details.

