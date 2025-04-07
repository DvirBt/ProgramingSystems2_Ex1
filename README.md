# ProgrammingSystems2 - Assignment 1
This repository will contain the first assignment in the course Programming Systems 2

In this assignment we (the students) were required to implement a few algorithms that we were taught in the course Algorithms 1.
The algorithms are:
1. BFS algorithm
2. DFS algorithm
3. Dijkstra's algorithm
4. Prim's algorithm
5. Kruskal's algorithm

We were also required to implement those algorithms with a graph represented as an adjacency list. Both classes are under the namespace 'graph' - as required.
Moreover, we are not allowed to use Vector Or STL. Therefore, I created my very own Queue and UnionFind data structures.
Additionally, we were also required to create tests for each class using DocTest and to create a Makefile.

To conclude, my project includes the following files:
1. Queue Class (hpp, cpp files) - supports the basic functions of a Queue data structure.
2. UnionFind Class (hpp, cpp files) - supports the basic function of a UnionFind structure.
3. Graph Class (hpp, cpp files) - which is implemented as adjacency list. Also contains two structs in it - Vertex and Edge. Supports the function add edge, remove edge and a print of the graph.
4. Algorithms Class (hpp, cpp files) - contatins all the algorithms written above.
5. Test (cpp file) - contains 4 Test Cases (one for each class) which checks all its supported functions.
6. Makefile - supports the rules Main - runs the main, test - runs the Tests, valgrind (checks for memory leak) and clean.
Note: the 'make valgrind command' is being performed on the main. Therefore, when running this command, there is a point that the user needs to enter '0' so the valgrind will keep the check.

The logic behind every function is explained further more in the project itself.

Information sources that I used:
1. Adjacency list info - https://en.wikipedia.org/wiki/Adjacency_list
2. BFS video - https://www.youtube.com/watch?v=HZ5YTanv5QE&t=35s
3. DFS video - https://www.youtube.com/watch?v=Urx87-NMm6c&t=24s
4. Dijkstra video - https://www.youtube.com/watch?v=_lHSawdgXpI
5. Prims video - https://www.youtube.com/watch?v=cplfcGZmX7I
6. Kruskal video - https://www.youtube.com/watch?v=71UQH7Pr9kU
7. Union find info - https://algorithmist.com/wiki/Union_find
8. Union find video 1 - https://www.youtube.com/watch?v=ayW5B2W9hfo
9. Union find video 2 - https://www.youtube.com/watch?v=JZBQLXgSGfs
10. DocTest - https://blog.jetbrains.com/rscpp/2019/07/10/better-ways-testing-with-doctest/
11. Exceptions - https://en.cppreference.com/w/cpp/header/stdexcept
12. Documentation - https://developer.lsst.io/cpp/api-docs.html
13. I also used the presentations that are given in the Moodle.
