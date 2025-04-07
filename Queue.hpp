// email: dvirbto@gmail.com

/**
 * This class represents a Queue data structure.
 * vertices - an array of int which represents the vertices serial number.
 * size - the current size of the Queue.
 * maxSize - the maximum size the Queue can reach.
 * Functions explained in cpp file.
 */
class Queue{
    private:
        int* vertices;
        int size;
        int maxSize;
    
    public:
        Queue(int numOfVertices);
        ~Queue();
        void enQueue(int vertexNum);
        int deQueue();
        bool isEmpty();
        bool isFull();
        int extractMin();
        int getSize();
};