# README

A basic search tree program to solve an interesting coding challenge. 

## Problem:
You are given a set of two-dimensional rectangular boxes on a two-dimensional Cartesian plane with the
following assumptions and constraints:
- All boxes are axis-aligned, i.e. each box can be defined in terms of the Cartesian coordinates of its minimum corner {a, b} and its maximum corner {c, d} such that a < c and b < d.
- Boxes may be contained within other boxes or may be disjoint from one another, i.e. boxes do not overlap or touch one another.
- The boxes therefore partition the plane into a number of regions. The unbounded region, which lies outside of all the boxes, is classified as sea.
- All other regions are classified either as sea or as land, subject to the constraint that adjacent regions must not share the same classification.

The task is to read the definition of the rectangles from standard input formatted as defined below, and output the number of regions classified as land to standard output.

## Input Format:
Some sample data is provided below for you to use when testing your solution. The first line contains an
integer N denoting the number of boxes. The next N lines contain the four floating point values a, b, c, d
that define Cartesian coordinates of the minimum corner and maximum corner of each box separated by a
single space.
```
<N>
a1 b1 c1 d1
...
aN bN cN dN
```

## Solution:

Arrange all the rectangles into a search tree data format and tree nodes on even layers are "land".

## To run the program:

- Save the inputs at input.txt in the following format, where there are 14 rectangles and each line shows their bottom left and top right corner x, y coordinates
```
14
1.0 1.0 10.0 6.0
1.5 1.5 6.0 5.0
2.0 2.0 3.0 3.0
2.0 3.5 3.0 4.5
3.5 2.0 5.5 4.5
4.0 3.5 5.0 4.0
4.0 2.5 5.0 3.0
7.0 3.0 9.5 5.5
7.5 4.0 8.0 5.0
8.5 3.5 9.0 4.5
3.0 7.0 8.0 10.0
5.0 7.5 7.5 9.5
5.5 8.0 6.0 9.0
6.5 8.0 7.0 9.0
```
- Then use the following commands 
```
make
```
```
./main
```

- The program will then automatically run all the unit tests and print the reaults of the tests and the number of land at terminal

- If there are invalid rectange(s) or invalid inputs, the program will handle the errors, and show corresponding errors messages. 

- To execute the program again with updated inputs at input.txt, just run the executable again
```
./main
```

- clean the directory with make clean
```
make clean
```

---
## Unit tests
All the unit tests are at <b>./tests/tests.cpp</b>. Catch framework is used. Running the test will automatically run the main program as well.

- To run all tests:
```
make clean
make
./main
```
- To run test related to main.cpp only
```
make clean
make
./main [main.cpp]
```

- To run test related to tree.cpp only
```
make clean
make
./main [tree.cpp]
```

---
## Example 1
input.txt
```
14
1.0 1.0 10.0 6.0
1.5 1.5 6.0 5.0
2.0 2.0 3.0 3.0
2.0 3.5 3.0 4.5
3.5 2.0 5.5 4.5
4.0 3.5 5.0 4.0
4.0 2.5 5.0 3.0
7.0 3.0 9.5 5.5
7.5 4.0 8.0 5.0
8.5 3.5 9.0 4.5
3.0 7.0 8.0 10.0
5.0 7.5 7.5 9.5
5.5 8.0 6.0 9.0
6.5 8.0 7.0 9.0
```
Commads:
```
make clean
make
./main
```
Expected output at terminal
```
===============================================================================
All tests passed (33 assertions in 9 test cases)

Number of land: 9
```

---
## Example 2
input.txt
```
5
1.0 1.0 10.0 10.0
3.0 3.0 4.0 4.0
5.0 3.0 6.0 4.0
1.5 1.5 7.0 5.0
15.0 1.0 20.0 6.0
```
Commads:
```
make clean
make
./main
```
Expected Output at terminal
```
===============================================================================
All tests passed (33 assertions in 9 test cases)

Number of land: 4
```

---
## Example 3 - Invalid rectangle's coordinates
input.txt
```
2
1.0 1.0 10.0 10.0
4.0 4.0 3.0 3.0
```
Commads:
```
make clean
make
./main
```
Expected Output at terminal
```
===============================================================================
All tests passed (33 assertions in 9 test cases)

Invalid input at Rectangle 2
```

---
## Example 4 - Overlapping rectangles
input.txt
```
3
1.0 1.0 10.0 10.0
3.0 3.0 4.0 4.0
2.5 3.0 3.5 4.0
```
Commads:
```
make clean
make
./main
```
Expected Output at terminal
```
===============================================================================
All tests passed (33 assertions in 9 test cases)

3.000000 3.000000 4.000000 4.000000
2.500000 3.000000 3.500000 4.000000
Error: Invalid input of overlapping/touching rectangles
```
---
