# C Tricks & Pitfalls

**Modern C** (Jens Gustedt) + **Expert C Programming** (Peter van der Linden) - direct examples + insights.

## Examples Overview
| # | Topic | Status | Key Lesson |
|---|-------|--------|------------|
| 01 | [Assembly Inline](./01_assembly_inline.c) | ✅ Works | Uses inline assembly parts |
| 02 | [Bus Error](./02_bus_error.c) | ✅ Works | Used to genereate bus error, works now |
| 03 | [Creative Comments](./03_creative_comments.c) | ✅ Works | Interesting comment syntax |
| 04 | [Const Switch](./04_const_switch_case.c) | ❌ Won't compile | `const int` in switch fails |
| 05 | [Const Overwrite](./05_const_pointer_overwrite.c) | ✅ Works | Pointer overwrites const |
| 06 | [Type Promotion](./06_implicit_char_to_int.c) | ✅ Works | `char` → `int` (size = 4) |
| 07 | [Longjmp Variables](./07_longjmp_local_variables.c) | ✅ Works | Local variables between jumps should be volatile |
| 08 | [Block Lifetime](./08_block_scope_lifetime.c) | ✅ Works | Variables visible on block entry |
| 09 | [Variable Shadowing](./09_variable_shadowing.c) | ✅ Works | Works like C++ `::` style shadowing |
| 10 | [Macro Symbols](./10_macro_defined_symbols.c) | ✅ Works | Prints macro-defined symbols |
| 11 | [Malloc Idiom](./11_malloc_idiomatic_sizing.c) | ✅ Works | Idiomatic `malloc` sizing |
| 12 | [Trace Macros](./12_trace_macros.c) | ✅ Works | Smart macro debugging |
| 13 | [Malloc Shadow](./13_malloc_shadow_conflict.c) | ❌ Won't compile | Can't redefine `malloc()` |
| 14 | [String Adjacency](./14_string_literal_adjacency.c) | ✅ Works | String literal adjacency + trailing comma |
| 15 | [Typedef vs Macro](./15_typedef_vs_macro.c) | ❌ Won't compile | `typedef` ≠ textual replacement |

## Makefile Usage

make all # Compile all 15 (exactly 3 fail: 04,13,15)  
make run # Run 12 working examples  
make clean # Remove binaries  
make status # Update this table!  
make rebuild # clean + all  

## Quick Demo
cd C_tricks/  
make run # One command = 12/15 demos work!  

## Book Attribution
Examples adapted from:

Modern C (Jens Gustedt) - C11/C17 standards

Expert C Programming (Peter van der Linden) - classic pitfalls

For educational use only. Buy original books for full context!

## Fair Use Notice
Short educational examples (<50 lines) from C literature discussions.

**Pro tip:** use `gcc -E` for macros and `gcc -S` for assembly output!
