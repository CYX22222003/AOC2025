# AOC 2025

## Day 1

Rounding in C++ division is tricky hahaha &#x1F605;. Takes me some time to figure out the off-by-1 error for some cases in the left turn. Finally got it working by checking first zero crossing and then counting full 100s.

## Day 2

Backreference in regular expression

## Day 3

Use fixed-length monotonic stack to find the lexicographically maximum subarray of size 12

## Day 4

Standard matrix processing. Can be done asymptotic better using graph methods. But given the size of the input (about 200 $\times$ 200), the brute force LGTM.

## Day 5

Today's question is more interesting.

Solution to the first puzzle is inspired by my TA Devansh's note on data structure and algorithm: https://notes.devanshshah.dev/notes/modules/data-structures-and-algorithms/algorithms/interval-search

Solution to the second puzzle is inspired by the Leetcode question: https://leetcode.com/problems/merge-intervals/


## Day 6

Treat vector of string as a matrix of character and do the transposition.

## Day 7

This appears to have a similar pattern to the Pascal Triangle.

## Day 8

Use Priority Queue to find the top K smallest distance between junctions.Then apply the Kruskal algorithm using Union Find Disjoint Set. 

## Day 9

Solved using ray-casting algorithms: https://rosettacode.org/wiki/Ray-casting_algorithm. Brute force to check all the rectangles and use multithreading to improve efficiency.

Elapsed (wall clock) time (h:mm:ss or m:ss): 5:29.58
Maximum resident set size (kbytes): 259644