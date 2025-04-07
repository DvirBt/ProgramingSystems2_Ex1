// email: dvirbto@gmail.com

#pragma once // see the same defention more than once

namespace graph
{
    /**
     * This struct represests a Vertex in a graph
     * @var num - the serial number of a vertex
     * @var weight - the weight of the edge between the adjacency list in index i to this vertex
     * @var next - a pointer to next vertex which the adjacency list in index i has an edge to
     */
    struct Vertex
    {
        int num;
        int weight;
        Vertex* next;
        Vertex()
        {}
        Vertex(int num, int weight, Vertex* next) : num(num), weight(weight), next(next)
        {}
    };

    /**
    * This class represents a Graph as an adjacency list
    * It contains 2 structs - Vertex an Edge
    * Each function is is explained in the cpp file
    */
    class Graph 
    {
        private:
            Vertex** verticesList;
            int numOfVertices;
    
        public:
            Graph(int num);
            ~Graph();
            void addEdge(int source, int target, int weigth);
            void removeEdge(int source, int target); // throws an exception if an edge does not exist
            void print_graph();
            Vertex** getVerticesList() const;
            int getSize() const;
            bool isEdgeExist(int source, int target) const; 
    };
    
    /**
     * This struct represests an Edge in a graph
     * @var num - the serial number of the edge
     * @var start - the serial number of the first connected vertex
     * @var end - the serial number of the second connected vertex
     * @var weight - the weight of the edge between start to end (and the opposite)
     */
    struct Edge
    {
        int num;
        int start;
        int end;
        int weight;
    
        Edge()
        {}
        Edge(int num, int start, int end, int weight) : num(num), start(start), end(end), weight(weight)
        {}
    };
}