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

- The extended use of C preprocessor to go automatically generate code suitable for a specific type from time to time.
- The use of void pointers items inside the data structures to hold all possible data types.

Given the specific target of this repository, I decided to avoid these 2 solutions and offer a simpler one (not suitable for a real application :^( ).

All the data structures in the repository will contain objects of type `data_type`. `data_type` will be defined within the `datatype.h` header. The redefinition of this type will make the library adaptable to any specific exercise the user is facing!
Functions that execute comparisons between user-defined types will also accept as input a function pointer of type `data_type_compare_fn` (also found within `datatype.h`) that can be implemented as needed.

## Repository structure

WIP

## Data structures

The following data structures will be implemented:

- linked lists
- stacks
- queues
- dynamic arrays
- dictionaries
- trees
- heaps
- graphs

## Algorithms

WIP

## Disclaimer

All the code available in this repo has been created for the purposes stated previously and therefore lacks specific attributes that should be expected in something targetting an enterprise application (logging, extensive input checking, etc...). Avoid using it "as is" in a production environment.

## Reference

The primary reference for the data structures and algorithms used in this repository is [`The Algorithm Design Manual` by Steven Skiena](https://www.algorist.com/).
