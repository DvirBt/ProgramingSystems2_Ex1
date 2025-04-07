// email: dvirbto@gmail.com

#include "Queue.hpp"
#include <iostream>
using namespace std;

/**
 * Queue's constructor
 * @param numOfVertices - number of vertices a given graph contains
 * The constructor creates an array of int as the size of numOfVertices
 * It initilizes the variables in the array to -1, @var size to 0 and @var maxSize to numOfVertices
 */
Queue::Queue(int numOfVertices)
{
    vertices = new int[numOfVertices];
    for (int i = 0; i < numOfVertices; i++)
        vertices[i] = -1;

    size = 0;
    maxSize = numOfVertices;
}

/**
 * Queue's deconstructor
 * Deletes the array
 */
Queue::~Queue()
{
    delete[] vertices;
}

/**
 * This function inserts a given number to the queue as long as the queue is not full. If the queue is full relevant message will appear
 * @param vertexNum - the number that will be inserted to the queue
 */
void Queue::enQueue(int vertexNum)
{
    if (!isFull())
    {
        vertices[size] = vertexNum;
        size++;
    }

    else // queue is full
        cout << "Queue is full!\n";
}

/**
 * This function removes the first value in the queue and returns it
 * If the queue is empty the function returns -1 and prints relevant message.
 * @return the removed number if the queue is not empty. Otherwise, returns -1
 */
int Queue::deQueue()
{
    int toReturn = -1;
    if (!isEmpty())
    {
        toReturn = vertices[0];
        for (int i = 0; i < size; i++)
            vertices[i] = vertices[i+1];

        vertices[size] = -1;
        size--;
    }

    else // queue is empty
        cout << "Queue is empty!" << endl;

    return toReturn;
}

/**
 * This function checks if the Queue is full
 * @returns true if the queue is full. Otherwise, returns false
 */
bool Queue::isFull()
{
    if (size == maxSize)
        return true;

    return false;
}

/**
 * This function checks if the Queue is empty
 * @returns true if the queue is empty. Otherwise, returns false
 */
bool Queue::isEmpty()
{
    if (vertices[0] == -1)
        return true;

    return false;
}

/**
 * This function removes the minimum number in the queue and return it as long as the queue is not empty
 * @returns the removed minimum number in the queue. If the queue is empty, -1 is returned
 */
int Queue::extractMin()
{
    if (isEmpty())
        return -1;

    int minIndex = 0;
    int minNum = vertices[0];
    for (int i = 1; i < size; i++)
    {
        if (vertices[i] < minNum)
        {
            minNum = vertices[i];
            minIndex = i;
        }
    }

    // build the new Queue
    for (int i = minIndex; i < size; i++)
        vertices[i] = vertices[i+1];
    
    vertices[size] = -1;
    size--;
    
    return minNum;
}

/**
 * This function returns the current size of the Queue
 * @returns the current size of the queue
 */
int Queue::getSize()
{
    return size;
}