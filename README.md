# C data structures and algorithms

C is a great language for learning both basic development concepts and complex algorithms. Unfortunately, the C standard library doesn't provide any implementation for many of the most common data structures offered by modern languages. The purpose of this repository is therefore to fill this gap, giving anyone who wants to approach the world of algorithms in C some working tools.

## Table of Contents

- [Overview](#overview)
- [Repository structure](#repository-structure)
- [Data structures](#data-structures)
- [Algorithms](#algorithms)
- [Disclaimer](#disclaimer)
- [Reference](#reference)

## Overview

As is well known among C users, the lack of features such as c++ templates makes it difficult to produce generic data structures in C. The two techniques usually used to overcome this problem are:

- The extended use of C preprocessor to automatically generate code suitable for a specific type from time to time.
- The use of void pointers items inside the data structures to hold all possible data types.

Given the specific target of this repository, I decided to avoid these 2 solutions and offer a simpler one.

All the data structures in the repository will contain objects of type `data_type`. `data_type` will be defined within the `datatype.h` header. The redefinition of this type will make the library adaptable to any specific exercise the user is trying to solve.
Functions that execute comparisons between user-defined types will also accept as input a function pointer of type `data_type_compare_fn` (also found within `datatype.h`) that can be implemented as needed.

## Repository structure

This repository has been organized as a Visual Studio 2022 solution, composed of 3 projects:

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
- Graph (WIP)

## Algorithms

- [Hash functions](https://nodjiin.github.io/C_data_structures_and_algorithms/hashing_8c.html)

## Disclaimer

All the code available in this repo has been created for the purposes stated previously and therefore lacks specific attributes that should be expected in something targetting an enterprise application (logging, proper memory management, extensive input checking, etc...). Avoid using it "as is" in a production environment.

## References

The primary reference for the data structures and algorithms used in this repository is ['The Algorithm Design Manual' by Steven Skiena](https://www.algorist.com/).
Documentation related to this repository is being automatically built with doxygen on each commit and can be found on the [related github page](https://nodjiin.github.io/C_data_structures_and_algorithms/index.html).
