# Rubiks-Cube-Solver
## Overview
• Developed a virtual Rubik’s Cube (3x3) using C++ with efficient data structures.

• Achieved solving time under 3 seconds for a cube jumbled 8 times using BFS, DFS, and IDDFS.

• Implemented Korf’s IDA* Algorithm, reducing solving time to under 10 seconds for a cube jumbled 13 times.

• Optimized search heuristics to improve efficiency and reduce computation time ensuring solution in ≤20 moves


## Key Learnings from the project:  

I gained insight into how to model a real-world object, like a Rubik’s Cube, in a way that a computer can understand. I discovered how to decompose a larger problem, such as building a complete Rubik’s Cube solver, into smaller, manageable sub-problems using basic models and controllers like Rubik’s Cube representations and solvers.  

Through the project, I explored how to break down multiple representations into classes and create base classes that could be further extended, such as the Rubik’s Cube base class and the Pattern Database base class.  

Practical examples of Object-Oriented Programming (OOP) were integral to the learning process. Concepts like classes and objects, virtual functions and abstract classes, inheritance, and operator overloading were applied in real-world contexts.  

I applied pathfinding algorithms like BFS, DFS, IDDFS, and IDA* to solve real-world AI problems, realizing that these techniques have much broader applications in the field of AI. Additionally, I worked with heuristic search algorithms such as A* and IDA*, and learned how Pattern Databases can be built to provide heuristics for these searches.  

Along the way, I discovered various useful tools and techniques, such as:  
- Using `unordered_map<>` for custom objects and understanding how to create custom hash functions  
- Storing information efficiently using bit manipulation  
- Handling file saving and loading  
- The concept of Black boxing, where a system produces an expected output for a given input, as seen with the Permutation Indexer in my project.  
