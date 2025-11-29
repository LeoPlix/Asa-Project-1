Protein Chain Energy Maximization Project
Project Description
This project implements a dynamic programming solution to solve the protein chain energy maximization problem. The goal is to find the optimal sequence for removing amino acids from a protein chain such that the total energy released is maximized.

Problem Overview
Given a chain of n amino acids, each with:

A stability potential value (P_i)

A biochemical class (P, N, A, or B)

When removing an amino acid at position i, the energy released is calculated as:

text
E_liberated = P[i-1] × Af(C[i-1], C[i]) × P[i] + P[i] × Af(C[i], C[i+1]) × P[i+1]
Where Af is an affinity function between biochemical classes defined in a non-symmetric table.

Repository Structure
text
project/
├── protein_chain.cpp     # Main solution algorithm
├── generator.cpp         # Test instance generator
└── README.md            # This file
Solution Algorithm (protein_chain.cpp)
Approach
The implementation uses a dynamic programming algorithm with the following key components:

Core Algorithm
Dynamic Programming Table: dp[i][j] stores the maximum energy achievable for the subsequence from i to j

Reconstruction Function: Recursively reconstructs the optimal removal sequence

Affinity Table: Pre-computed values for biochemical class interactions

Key Features
Handles terminal positions with special 'T' class and unit potential

Ensures lexicographically smallest solution when multiple optimal sequences exist

Efficient O(n³) time complexity with O(n²) space complexity

Code Structure
cpp
// Main components:
- Input parsing for potentials and biochemical classes
- Affinity table initialization
- DP table computation
- Sequence reconstruction
- Output formatting
Compilation and Execution
bash
g++ --std=c++11 -O3 -Wall protein_chain.cpp -lm -o protein_chain
./protein_chain < input_file
Test Instance Generator (generator.cpp)
Overview
This C++ program generates random instances for the protein chain energy maximization problem. It creates valid input files that can be used to test the main solution algorithm.

Purpose
The generator produces random protein chain instances with:

Random chain length within specified bounds

Random potential values for each amino acid

Random biochemical classes for each amino acid

Usage
bash
g++ -O3 -Wall generator.cpp -o generator
./generator <N> <Pmax> [seed]
Parameters:
N: Number of amino acids in the chain (must be ≥ 1)

Pmax: Maximum potential value for amino acids (values will be in range [1, Pmax])

seed: (Optional) Random seed for reproducible results. If omitted, uses current time

Examples:
bash
./generator 10 20        # Chain of 10 amino acids, potentials up to 20, random seed
./generator 5 15 123     # Chain of 5 amino acids, potentials up to 15, fixed seed 123
Input/Output Formats
Input Format (for main program)
text
n
P1 P2 ... Pn
C1C2...Cn
Output Format (from main program)
text
total_energy
a1 a2 ... an
Example
Input:

text
3
10 5 12
ABA
Output:

text
359
1 2 3
Generated Input Example:
For ./generator 3 10 42:

text
3
8 3 7 
PNA
Testing Workflow
Generate test instances:

bash
./generator 10 20 > test1.in
./generator 15 25 123 > test2.in
Run solution on test instances:

bash
./protein_chain < test1.in > test1.out
./protein_chain < test2.in > test2.out
Verify results by examining the output files

Implementation Details
Main Algorithm (protein_chain.cpp)
Uses dynamic programming with memoization

Handles edge cases with terminal amino acids

Implements lexicographical ordering for multiple optimal solutions

Efficient memory management with unordered_map for reconstruction

Generator (generator.cpp)
Uses standard C++ rand() function for randomization

Validates input parameters

Produces compatible output format

Supports reproducible testing with seed parameter

Dependencies
C++11 or later

Standard Library components only

Authors
Developed as part of the Analysis and Synthesis of Algorithms course at Instituto Superior Técnico
