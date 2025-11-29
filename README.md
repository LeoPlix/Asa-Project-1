```markdown
# Protein Chain Energy Maximization

> Dynamic programming solution to maximize the total energy released by removing amino acids from a protein chain.

[![C++](https://img.shields.io/badge/lang-C%2B%2B-00599C.svg)](https://isocpp.org/) [![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)]

Table of Contents
- Overview
- Problem statement
- Input / Output format
- Example
- Repository structure
- Solution approach
- Complexity
- Compilation & execution
- Test instance generator
- Testing workflow
- Contributing
- Authors & License

Overview
--------
This repository contains a C++ implementation that solves the "Protein Chain Energy Maximization" problem using dynamic programming. The goal is to determine a removal order of amino acids that maximizes the total released energy. A separate generator program is included to produce random test instances.

Problem statement
-----------------
Given a chain of n amino acids (positions 1..n), each amino acid i has:
- a stability potential P_i (positive integer),
- a biochemical class C_i ∈ {P, N, A, B} (and special terminal class 'T' used for boundaries).

When removing the amino acid at position i, the energy released is computed as:
E_released = P[i-1] × Af(C[i-1], C[i]) × P[i] + P[i] × Af(C[i], C[i+1]) × P[i+1]

Af(.,.) is an affinity function between biochemical classes (a non-symmetric table). The objective is to choose a removal sequence that maximizes the sum of energies released across all removals.

Input / Output format
---------------------
Main program input format:
n
P1 P2 ... Pn
C1C2...Cn

- n: integer, number of amino acids (n ≥ 1).
- Pi: integer potential for amino acid i.
- Ci: single-letter class for amino acid i (no spaces between characters).

Main program output format:
total_energy
a1 a2 ... an

- total_energy: the maximum total energy (integer).
- a1..an: space-separated sequence of indices (1‑based) indicating the order in which amino acids are removed. The sequence length is n.

Example
-------
Input:
3
10 5 12
ABA

Possible output:
359
1 2 3

Repository structure
--------------------
project/
├── protein_chain.cpp     # Main algorithm implementation (dynamic programming + reconstruction)
├── generator.cpp         # Random test instance generator
└── README.md             # This file

Solution approach (protein_chain.cpp)
-------------------------------------
- Dynamic Programming:
  - A DP table dp[i][j] stores the maximum energy obtainable by optimally removing all amino acids in the subsequence from index i to j (inclusive).
  - Transitions consider removing each k in [i..j] as the next removed amino acid in that subsequence, combining the energy released immediately when k is removed with optimal results of the two subproblems [i..k-1] and [k+1..j].
- Reconstruction:
  - Alongside dp values, the implementation records choices to recover the removal order. The reconstruction returns the lexicographically smallest sequence when multiple optimal solutions exist.
- Affinity table:
  - Affinity values Af(class_u, class_v) are precomputed in a lookup table and are non-symmetric.
- Edge handling:
  - Terminal positions are treated via a special class 'T' with unit potential where needed.

Key features
------------
- Correctness via DP with memoization.
- Lexicographically smallest optimal sequence in case of ties.
- Robust handling of edge cases and terminal behavior.

Time and space complexity
-------------------------
- Time complexity: O(n^3) — the algorithm considers O(n^2) subproblems and O(n) choices per subproblem.
- Space complexity: O(n^2) for the DP table, plus auxiliary storage for reconstruction.

Compilation & execution
-----------------------
Compile the main solver:
g++ --std=c++11 -O3 -Wall protein_chain.cpp -lm -o protein_chain

Run the program:
./protein_chain < input_file

Compile the generator:
g++ -O3 -Wall generator.cpp -o generator

Generator usage:
./generator N Pmax [seed]

Parameters:
- N: number of amino acids (N ≥ 1).
- Pmax: maximum potential value (potentials generated uniformly in [1, Pmax]).
- seed: optional integer seed for reproducible instances. If omitted, current time is used.

Examples:
./generator 10 20           # random instance with 10 amino acids, potentials up to 20
./generator 5 15 123        # reproducible instance with seed 123

Generated input example (from: ./generator 3 10 42):
3
8 3 7
PNA

Testing workflow
----------------
1. Generate test instances:
   ./generator 10 20 > test1.in
   ./generator 15 25 123 > test2.in

2. Run solver:
   ./protein_chain < test1.in > test1.out
   ./protein_chain < test2.in > test2.out

3. Inspect output files (total energy and removal sequence). Use multiple seeds and sizes to validate performance and correctness.

Notes & implementation details
------------------------------
- The implementation uses only the C++ standard library and requires a C++11-compliant compiler.
- The generator uses the standard rand() random source; seeding ensures reproducibility when requested.
- The code includes careful handling for terminal neighbors and ensures deterministic tie-breaking to produce lexicographically minimal sequences when energies tie.

Contributing
------------
Contributions, bug reports and improvements are welcome. If you plan to submit changes:
- Open an issue describing the change or bug.
- Submit a pull request with a concise description and tests if applicable.

Authors & License
-----------------
Developed for the Analysis and Synthesis of Algorithms course at Instituto Superior Técnico.

This project is provided under the MIT License.
```
