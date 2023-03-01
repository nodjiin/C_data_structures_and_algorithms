# C data structures and algorithms

C is an excellent language for mastering fundamental development concepts and sophisticated algorithms. However, the C standard library lacks many of the prevalent data structures that modern languages offer. This repository aims to bridge this gap by providing some useful tools for anyone who wants to explore the world of algorithms in C.

## Table of Contents

- [Overview](#overview)
- [Repository structure](#repository-structure)
- [Data structures](#data-structures)
- [Algorithms](#algorithms)
- [Disclaimer](#disclaimer)
- [Reference](#reference)

## Overview

C users know that the absence of features like c++ templates makes it hard to create generic data structures in C. The two common techniques to address this issue are:

- The extensive use of C preprocessor to generate code for a specific type on demand.
- The use of void pointers items inside the data structures to store any data type.

Considering the particular goal of this repository, I chose to skip these 2 solutions and propose a simpler one.

All the data structures in the repository will hold objects of type `data_type`. `data_type` will be declared in the `datatype.h` header. Redefining this type will make the library suitable for any specific problem the user is trying to solve. Functions that perform comparisons between user-defined types will also take as input a function pointer of type `data_type_compare_fn` (also in `datatype.h`) that can be implemented as required.

## Repository structure

This repository has been organized as a Visual Studio 2022 solution, composed of 4 projects:

- core (dll)
- data_structures (dll)
- algorithms (dll)
- tests (app)

the latter contains a set of unit tests, created by exploiting the standard library's assert macro. This project is a good place to look to clear up any doubts about the use of the library.

## Data structures

- [Singly-linked list](https://nodjiin.github.io/C_data_structures_and_algorithms/structsingly__linked__list__t.html)
- [Doubly-linked list](https://nodjiin.github.io/C_data_structures_and_algorithms/structdoubly__linked__list__t.html)
- [Stack](https://nodjiin.github.io/C_data_structures_and_algorithms/structstack__t.html)
- [Queue](https://nodjiin.github.io/C_data_structures_and_algorithms/structqueue__t.html)
- [Dynamic array](https://nodjiin.github.io/C_data_structures_and_algorithms/structdynamic__array__t.html)
- [Hash Table](https://nodjiin.github.io/C_data_structures_and_algorithms/structhashtable__t.html)
- [Binary search tree](https://nodjiin.github.io/C_data_structures_and_algorithms/structbinary__search__tree__t.html)
- [Trie](https://nodjiin.github.io/C_data_structures_and_algorithms/structtrie__t.html)
- [Heap](https://nodjiin.github.io/C_data_structures_and_algorithms/structheap__t.html)
- [Graph](https://nodjiin.github.io/C_data_structures_and_algorithms/structgraph__t.html)

## Algorithms

- [Hash functions](https://nodjiin.github.io/C_data_structures_and_algorithms/hashing_8c.html)
- [Search functions](https://nodjiin.github.io/C_data_structures_and_algorithms/search_8h.html)

## Disclaimer

All the code available in this repo has been created for the purposes stated previously and therefore lacks specific attributes that should be expected in something targetting an enterprise application (logging, proper memory management, extensive input checking, etc...). Avoid using it "as is" in a production environment.

## References

The primary reference for the data structures and algorithms used in this repository is ['The Algorithm Design Manual' by Steven Skiena](https://www.algorist.com/).
Documentation related to this repository is being automatically built with doxygen on each commit and can be found on the [related github page](https://nodjiin.github.io/C_data_structures_and_algorithms/index.html).
