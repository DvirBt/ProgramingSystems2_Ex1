// email: dvirbto@gmail.com

#include "UnionFind.hpp"
#include <stdexcept>
using namespace std;

/**
 * Union Find's constructor
 * @param size - the number of vertices in the graph
 * Creates an array as the given size. Each index initially points to it self, because each one represents itself at the beginning
 * Also initialize maxSize to the given size
 */
UnionFind::UnionFind(int size)
{
    parents = new int[size];
    for (int i = 0; i < size; i++)
        parents[i] = i;
    
    maxSize = size;
}

/**
 * Union Find's deconstructor
 * Deletes the parents array
 */
UnionFind::~UnionFind()
{
    delete[] parents;
}

/**
 * This functions gets a number and returns it's representetive
 * @param num - an integer
 * @returns the representetive of num
 * @throws out_of_range if the given number is negative or equals/aboves the amount of vertices
 */
int UnionFind::find(int num)
{
    if (num >= maxSize)
        throw out_of_range{"The given number must be lower than the amount of vertices in the graph!"};
    
    else if (num < 0)
        throw out_of_range{"The given number can not be negative!"};


    if (parents[num] == num) // if the parent is the root it self -> representetive
        return num;
    
    return find(parents[num]); // keep searching the root
}

/**
 * This function gets two numbers and unions them if they are NOT in the same commponent
 * @param num1 - the first number
 * @param num2 - the second number
 */
void UnionFind::Union(int num1, int num2)
{
    // get representetives
    int root1 = find(num1);
    int root2 = find(num2);

    if (root1 != root2) // different commponents
        parents[root2] = root1;  
}