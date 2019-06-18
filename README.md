# Artificial Intelligence Second Assignment - Adversarial Search

## Connect Four

The goal of this assignment was to create a bot that was capable of playing the Connect Four game while implementing the minimax, alpha-beta pruning and Monte Carlo Tree Search algorithms.

This was one of four assignments required by the Artificial Intelligence course in the Computer Science degree of the Faculty of Sciences of the University of Porto.

Authors:
* Ana Dias (github.com/Ana365Dias)
* João Duarte (github.com/jsilduarte)
* João Neves (github.com/jbfneves)

Commit 07d18f1a5e57a33fd5b41644d35057f2a6272a04 contains the version of the code at the time of delivery. Further changes can, and will, eventually, be made to:
* Clean up the code
* Improve the MCTS algorithm which barely works as it's intended
* Provide visualization of performance differences between the different methods

## Compiler version:
gcc (GCC) 8.2.1

## Compiling and executing

$ make

$ ./main

## File description

* Main files

main.c - main file

4linha.h - board structures and methods

minmax.h - minimax

alphabeta.h - alpha-beta pruning

monte_carlo.h - MCTS

montecarlo.h - non functioning attempt to implement MCTS

Makefile

* Structures

mytree.h - a basic tree implementation for this specific project
