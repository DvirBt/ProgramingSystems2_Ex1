// email: dvirbto@gmail.com

#include "Graph.hpp"

/**
 * This class represents a Union Find data structure
 * @var parents - an array of int which are the roots
 * @var maxSize - the maximum size of the array
 * Functions explained in cpp file
 */
class UnionFind
{
    private:
        int* parents;
        int maxSize;

    public:
        UnionFind(int size);
        ~UnionFind();
        void Union(int num1, int num2);
        int find(int num);
};