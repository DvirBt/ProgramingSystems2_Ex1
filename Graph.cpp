// email: dvirbto@gmail.com

#include "Graph.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

namespace graph
{
    /**
     * Graph's constructor
     * @param numOfVertices - the number of the vertecies in the graph.
     * Initializes the adjacency list in index i to null.
     */
    Graph::Graph(int numOfVertices) : numOfVertices(numOfVertices)
    {
        verticesList = new Vertex*[numOfVertices];
        for (int i = 0; i < numOfVertices; i++)
            verticesList[i] = nullptr;
        
    }

    /**
     * Graph's Deconstructor
     * Deletes each vertex that was created.
     * Then deletes the array of the adjacency list.
     */
    Graph::~Graph()
    {
        for (int i = 0; i < numOfVertices; i++)
        {
            Vertex* current = verticesList[i];
            while (current != nullptr)
            {
                Vertex* temp = current;
                current = current->next;
                delete temp;
            }
        }

        delete[] verticesList;
    }

    /**
     * This function checks if the given arguments are valid
     * @param source - the serial number of the source vertex
     * @param target - the serial number of the target vertex
     * @param numOfVertices - the number of vertices the checked graph contains
     * @throws logic_error if source equas to target
     * @throws out_of_range if source or target negtaive or above the amount of vertices in the graph
     */
    void check(int source, int target, int numOfVertices)
    {
        if (source == target) // same verex
            throw logic_error{"Source can not be the target!"};

        if (source < 0 || target < 0) // negative values
            throw out_of_range{"Source or target can't be negative!"};
        
        if (target >= numOfVertices || source >= numOfVertices) // exceeded the max serial numbers
            throw out_of_range{"Source or target must be lower than the size of the graph!"};
    }

    /**
     * This functions adds a new edge if possible. If not, the function prints a relevant message and returns to return address
     * @param source - the serial number of the source vertex
     * @param target - the serial number of the target vertex
     * @param weight - the weight of the edge
     * If an edge already exists - a relevant message will appear and the function will return to the return address.
     */
    void Graph::addEdge(int source, int target, int weigth)
    {
        // check validation
        check(source, target, numOfVertices);
        
        Vertex* current = verticesList[source];
        while(current != nullptr) // check all the connected vertecies
        {
            if (current->num == target) // an edge already exist
            {
                cout << "An edge already exists between " << source << " to " << target << endl;
                return;
            }    
                
            current = current->next;
        }

        // create a new vertex and add an edge from target to source
        Vertex* v = new Vertex(target, weigth, verticesList[source]);
        verticesList[source] = v;

        // create a new vertex and add an edge from source to target
        v = new Vertex(source, weigth, verticesList[target]);
        verticesList[target] = v;
    }

    /**
     * This function removes an edge if one's exists based on given vertices serial numbers
     * @param source - the serial number of the source vertex
     * @param target - the serial number of the target vertex
     * @throw logic_error if such edge does not exist
     */
    void Graph::removeEdge(int source, int target)
    {
        // check validation
        check(source, target, numOfVertices);

        bool found = false;
        Vertex* previousVertex = nullptr;
        Vertex* currentVertex = verticesList[source];
        while (currentVertex != nullptr)
        {
            if (currentVertex->num == target) // edge exists
            {
                if (previousVertex == nullptr) // the head of the list is the one that we want to remove
                    verticesList[source] = currentVertex->next;
                    
                else
                    previousVertex->next = currentVertex->next;

                found = true;
                cout << "Edge from source "<< source << " to target " << currentVertex->num << " removed!" << endl;
                delete currentVertex;
                break;
            }

            // check the next vertex
            previousVertex = currentVertex;
            currentVertex = currentVertex->next;
        }

        if (!found) // edge does not exists
            throw logic_error{"Edge does not exist!"};

        // edge exists so we want to remove the edge from target to source also
        previousVertex = nullptr;
        currentVertex = verticesList[target];

        while (currentVertex != nullptr)
        {
            if (currentVertex->num == source) // edge exists
            {
                if (previousVertex == nullptr) // the head of the list is the one that we want to remove
                    verticesList[target] = currentVertex->next;
                    
                else
                    previousVertex->next = currentVertex->next;

                found = true;
                cout << "Edge from target "<< target << " to source " << currentVertex->num << " removed!" << endl;
                delete currentVertex;
                break;
            }

            previousVertex = currentVertex; // store the previous vertex
            currentVertex = currentVertex->next; // check the next one
        }
    }

    /**
     * This function prints the graph
     */
    void Graph::print_graph()
    {
        cout << "Print of the graph" << endl;
        cout << "-------------------" << endl;
        for (int i = 0; i < numOfVertices; i++)
        {
            Vertex* currentVertex = verticesList[i];
            cout << "Vertex " << i << ": ";

            if (currentVertex == nullptr)
                cout << "No edges!";

            while (currentVertex != nullptr)
            {
                cout << i << " --> " << currentVertex->num << " weight: " << currentVertex->weight;
                currentVertex = currentVertex->next;
                if (currentVertex != nullptr) // seperate each edge if more that one exists
                    cout << " | ";
            }
            cout << endl; // enter line
        }
        cout << "-------------------" << endl;
    }

    /**
     * This function returns the adjacency list
     * @return adjacency list
     */
    Vertex** Graph::getVerticesList() const
    {
        return verticesList;
    }

    /**
     * This function returns the size of the graph which is the amount of vertices
     * @return size
     */
    int Graph::getSize() const
    {
        return numOfVertices;
    }

    /**
     * This function gets the serial numbers of vertecies and checks if an edge exists between them
     * @param source - the serial number of the source vertex
     * @param target - the serial number of the target vertex
     * @returns true if an edge exists between the two. Otherwise, returns false
     */
    bool Graph::isEdgeExist(int source, int target) const
    {
        // check validation
        check(source, target, numOfVertices);

        bool foundSource = false;
        bool foundTarget = false;

        Vertex* currentVertex = verticesList[source]; // get all connected vertices to source
        while (currentVertex != nullptr)
        {
            if (currentVertex->num == target) // an edge is found
            {
                foundSource = true;
                break;
            }

            currentVertex = currentVertex->next; // check the next vertex in the list
        }

        // make sure the edge also found in target vertex list
        currentVertex = verticesList[target]; // get all connected vertices to target
        while (currentVertex != nullptr)
        {
            if (currentVertex->num == source) // an edge is found
            {
                foundTarget = true;
                break;
            }

            currentVertex = currentVertex->next; // check next one
        }

        if (foundSource == true && foundTarget == true) // both edges exists (same edge in undirected graph) 
            return true;

        return false;
    }
}

