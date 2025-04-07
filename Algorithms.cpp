// email: dvirbto@gmail.com

#include "Algorithms.hpp"
#include "Queue.hpp"
#include "UnionFind.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

namespace graph
{
    /**
     * Algorithms's constructor
     */
    Algorithms::Algorithms()
    {}

    /**
     * Algorithms's deconstructor
     */
    Algorithms::~Algorithms()
    {}
    
    /**
     * This function gets a graph and a serial number of a vertex(source) and throws an exception if one of the arguments is not valid
     * @param graph - a given simple undirected graph
     * @param source - a given serial number of a vertex
     * @throws out_of_range if source is negative or above the graph's size (amount of it's vertices)
     * @throws invalid_argument if the graph is not initiallized properly
     */
    void validInputs(const Graph& graph, int source)
    {
        if (source < 0)
            throw out_of_range{"Source can not be negative!"};

        if (source >= graph.getSize())
            throw out_of_range{"Source must be below graph size!"};

        if (graph.getVerticesList() == nullptr)
            throw invalid_argument{"Vertex adjacency list is null!"};
    }

    /**
     * This function implements BFS algorithm search on a given graph and an index of a vertex
     * @param graph - a given simple undirected graph
     * @param source - a given serial number of a the first vertex in the search
     * @return the graph created as a result of the BFS search
     */
    Graph Algorithms::bfs(const Graph& graph, int source)
    {
        // check validation
        validInputs(graph, source);

        int maxSize = graph.getSize();
        Graph tree = Graph(maxSize); // will represent the bfs search order
        bool* visited = new bool[maxSize]; // create an array to check who was visited
        for (int i = 0; i < maxSize; i++) // init all to false at start
            visited[i] = false;

        Vertex** verticesList = graph.getVerticesList();
        Queue queue = Queue(graph.getSize()); // init a queue
        queue.enQueue(source); // insert the first visited vertex
        visited[source] = true;

        while (!queue.isEmpty())
        {
            int currentNum = queue.deQueue(); 
            //visited[currentNum] = true; // once dequeued -> the vertex is visited
            Vertex* currentVertex = verticesList[currentNum]; // get all it's negibhors
            while (currentVertex != nullptr)
            {
                if (!visited[currentVertex->num]) // if a vertex was not visited yet
                {
                    queue.enQueue(currentVertex->num); // enqueue him
                    visited[currentVertex->num] = true; // once equeued -> the vertex is visited (so he will not be added again to the queue)
                    tree.addEdge(currentNum, currentVertex->num, 0); // create an edge with weight 0, weight is irrelevant
                }
                
                currentVertex = currentVertex->next; // move to the next neighbor if one exists
            }
        }

        delete[] visited; // free the memory

        return tree;
    }

    /**
     * This recursive function builds a DFS graph
     * @param graph - a given simple undirected graph
     * @param tree - the current graph that is being created 
     * @param visited - a bollean array which marks each visited vertex
     * @param value - a given serial number of the current vertex that is being checked
     */
    void createDfsTree(const Graph& graph, Graph& tree, bool*& visited, int value)
    {
        visited[value] = true; // visited this vertex -> set to true
        Vertex* currentVertex = graph.getVerticesList()[value];

        while (currentVertex != nullptr)
        {
            if (!visited[currentVertex->num]) // if the current vertex has not been visited yet -> add edge
            {
                tree.addEdge(value, currentVertex->num, 0); // weight does not matter
                createDfsTree(graph, tree, visited, currentVertex->num); // recursive call with it's negibhor
            }
            currentVertex = currentVertex->next; // check the other neighbors of THIS vertex
        }
    }

    /**
     * This function implements DFS algorithm search on a given graph and an index of a vertex
     * @param graph - a given simple undirected graph
     * @param source - a given serial number of a the first vertex in the search
     * @return the graph created as a result of the DFS search
     */
    Graph Algorithms::dfs(const Graph& graph, int source)
    {
        // check validation
        validInputs(graph, source);

        int maxSize = graph.getSize();
        Graph tree = Graph(maxSize); // will represent the dfs search order
        bool* visited = new bool[maxSize];
        for (int i = 0; i < maxSize; i++) // init all to false
            visited[i] = false; // means that I didn't visit vertex i yet
      
        createDfsTree(graph, tree, visited, source); 

        delete[] visited;
        return tree;
    }

    /**
     * This function checks if one of the edges of a given graph has negative weight
     * @param graph - a given simple undirected graph
     * @param size - the amount of vertices the graph contains
     * @throws invalid_argument if one of the edges has a negative weight
     */
    void checkNoNegativeEdges(const Graph& graph, int size)
    {
        Vertex** verticesList = graph.getVerticesList();
        for (int i = 0; i < size; i++)
        {
            Vertex* currentVertex = verticesList[i];
            while (currentVertex != nullptr)
            {
                if (currentVertex->weight < 0) // negative edge
                    throw invalid_argument("Negative edge is not allowed!");

                currentVertex = currentVertex->next;
            } 
        }
    }

    /**
     * This function returns the index of the next vertex that needs to be visited based on it's weight and if not visited yet.
     * If such does not exist - the function returns -1
     * @param visited - a boolean array of the visited vertices
     * @param weightArr - an int array of the current minimal weight of each vertex 
     * @param size - the amount of the vertices the graph contains
     * @return the serial number of the next vertex that's should be visited. If all visited the function returns -1
     */
    int getNextVertexNum(bool* visited, int* weightArr, int size)
    {
        int minWeight = __INT_MAX__;
        int minNum = -1;

        for (int i = 0; i < size; i++)
        {
            if (!visited[i] && weightArr[i] < minWeight) // if not visited and weight is lower -> update
            {
                minWeight = weightArr[i];
                minNum = i;
            }
        }

        return minNum;
    }

    /**
     * This function implements Dijkstra algorithm on a given graph and an index of a vertex
     * @param graph - a given simple undirected graph
     * @param source - a given serial number of a the first vertex in the algorithm
     * @return the graph (shortest paths by weight tree) created as a result of the Dijkstra algorithm
     */
    Graph Algorithms::dijkstra(const Graph& graph, int source)
    {
        // check validation
        validInputs(graph, source);
        
        int maxSize = graph.getSize();
        // check that there are no negative edges
        checkNoNegativeEdges(graph, maxSize);

        int* weightArr = new int[maxSize]; // array will be used to determine the weight of each vertex-path
        for (int i = 0; i < maxSize; i++)
            weightArr[i] = __INT_MAX__;

        int* parent = new int[maxSize];  // array will be used to determine if it already has an edge to a vertex
        for (int i = 0; i < maxSize; i++)
            parent[i] = -1;  
        
        bool* visited = new bool[maxSize]; // array will be used to determine if a vertex has been visited
        for (int i = 0; i < maxSize; i++)
            visited[i] = false;

        weightArr[source] = 0; // first vertex in the search
        parent[source] = source; // source points to itself (no use really)
        Graph tree = Graph(maxSize);
        Queue queue = Queue(graph.getSize());
        queue.enQueue(source); // insert source

        while (true) 
        {
            int currentVertexNum = getNextVertexNum(visited, weightArr, maxSize); // get the next vertex to visit
            if (currentVertexNum == -1) // if all vertices visited -> exit
                break;

            visited[currentVertexNum] = true; // mark as visited
            Vertex* currentVertex = graph.getVerticesList()[currentVertexNum]; // get all the neighbors

            while (currentVertex != nullptr) 
            {
                if (!visited[currentVertex->num]) // if not visited yet
                {
                    int newWeight = weightArr[currentVertexNum] + currentVertex->weight; // calculate current weight
                    
                    if (newWeight < weightArr[currentVertex->num]) // check if update is necessary
                    {
                        if (parent[currentVertex->num] != -1) // an edge already exists -> needed to be removed
                            tree.removeEdge(parent[currentVertex->num], currentVertex->num); 
                     
                        weightArr[currentVertex->num] = newWeight; // update the new weight
                        parent[currentVertex->num] = currentVertexNum; // update the new path
                        tree.addEdge(currentVertexNum, currentVertex->num, currentVertex->weight); // add the new edge
                    }
                }

                currentVertex = currentVertex->next;  // move to the next neighbor
            }
        }

        // print the graph shortest paths from the given source vertex
        cout << endl;
        cout << "Shortest paths from " << source << " to vertex number: " << endl;
        cout << "---------------------------------------" << endl;
        for (int i = 0; i < maxSize; i++)
        {
            if (i == source) // skip the same vertex
                continue;

            string path = " --> " + to_string(i);
            int num = i;
            while (parent[num] != source) // as long as the parent is not the source vertex, get the path
            {
                num = parent[num]; 
                path = " --> " + to_string(num) + path;
            }
            path = to_string(parent[num]) + path;
            cout << i << ": " << path << " total weight: " << weightArr[i] << endl;
        }
        cout << "---------------------------------------" << endl;
        cout << endl;

        delete[] weightArr;
        delete[] visited;
        delete[] parent;

        return tree;
    }

    /**
     * This function implements prim's algorithm on a given graph
     * @param graph - a given simple undirected graph
     * @return the graph (MST) created as a result of the prim's algorithm
     */
    Graph Algorithms::prim(const Graph& graph)
    {
        validInputs(graph, 0); // no source given

        int maxSize = graph.getSize();

        bool* visited = new bool[maxSize]; // will be used to determine which vertex is already visited
        for (int i = 0; i < maxSize; i++)
            visited[i] = false;
        
        int* connected = new int[maxSize]; // will be used to determine the minimum edges for the MST (edge i->connected[i])
        for (int i = 0; i < maxSize; i++)
            connected[i] = -1;

        int* weight = new int[maxSize]; // will be used to check the current minimal weight of a vertex to another
        for (int i = 0; i < maxSize; i++)
            weight[i] = __INT_MAX__;

        int currentVertexNum = 0; // the source will be vertex 0
        weight[currentVertexNum] = -1;

        while (currentVertexNum != -1)
        {
            visited[currentVertexNum] = true; // mark as visited vertex
            Vertex* currentVertex = graph.getVerticesList()[currentVertexNum]; // get neigbhors
            while (currentVertex != nullptr)
            {
                if (currentVertex->weight < weight[currentVertex->num] && !visited[currentVertex->num]) // update the new edge if it's weight is lower that the existsing weight's edge
                {
                    connected[currentVertex->num] = currentVertexNum; // update the new path
                    weight[currentVertex->num] = currentVertex->weight; // update the new weight
                }

                currentVertex = currentVertex->next; // move to next neigbhor
            }

            currentVertexNum = getNextVertexNum(visited, weight, maxSize); // select the next vertex by minimum weight
        }

        // build the tree edges
        Graph tree = Graph(maxSize);
        for (int i = 0; i < maxSize; i++)
        {
            if (connected[i] != -1) // so the first index won't point to itself (even though there is an exception for this)
                tree.addEdge(i, connected[i], weight[i]); // connected array represents the minimum edges that should be picked to create the MST
        }

        // free memory
        delete[] weight;
        delete[] visited;
        delete[] connected;

        return tree;
    }

    /**
     * This function checks if a given array already exists in a given array of edges
     * @param edges - an array of edges
     * @param edge - a given edge
     * @param size - the size of the array of edges
     * @return true if the edge already exists in the array. Otherwise, returns false
     */
    bool isEdgeExist(Edge* edges, Edge edge, int size)
    {
        for (int i = 0; i < size; i++)
        {
            if (edges[i].start == edge.end && edges[i].end == edge.start) // avoid double creation of the same edge (in undirected graph)
                return true;
        }

        return false;
    }

    /**
     * This function creates all the edges based on a given graph
     * @param graph - a simple undirected graph
     * @param edges - an array of edges which will contain all the new edges created
     * @return the number of edges that were created
     */
    int createAllEdges(const Graph& graph, Edge*& edges)
    {
        int edgeIndex = 0;
        for (int i = 0; i < graph.getSize(); i++)
        {
            Vertex* currentVertex = graph.getVerticesList()[i]; // get all the neighbhors if vertex i
            while (currentVertex != nullptr)
            {
                Edge edge = Edge(edgeIndex, i, currentVertex->num, currentVertex->weight); // create new edge
                if (!isEdgeExist(edges, edge, edgeIndex)) // avoid double edges (1->2 && 2->1)
                {
                    edges[edgeIndex] = edge; // add the edge to the array
                    edgeIndex++; // number of edges increased by 1
                }
                currentVertex = currentVertex->next; // check next neighbor
            }
        }
        return edgeIndex; // reutrn the size
    }

    /**
     * This function gets an array of edges and sorts it based on their weight
     * @param edges - an array of edges
     * @param edgesSize - the amount of edges exist
     */
    void sortEdges(Edge*& edges, int edgesSize)
    {   
        for (int i = 0; i < edgesSize; i++)
        {
            int minWeight = edges[i].weight; // get initial data
            int minIndex = i;
            
            for (int j = i; j < edgesSize; j++) // j = i because all edges from i to j already sorted
            {
                if (edges[j].weight < minWeight) // new minimal edge
                {
                    minWeight = edges[j].weight;
                    minIndex = j;  
                }
            }

            if (minIndex != i) // update occured
            {
                // switch
                Edge temp = edges[i];
                edges[i] = edges[minIndex];
                edges[minIndex] = temp;
            }
        }
    }

    /**
     * This function implements kruskal's algorithm on a given graph
     * @param graph - a given simple undirected graph
     * @return the graph (MST) created as a result of the kruskal's algorithm
     */
    Graph Algorithms::kruskal(const Graph& graph)
    {
        validInputs(graph, 0);

        int graphSize = graph.getSize();
        int maxEdgesSize= graphSize*(graphSize-1)/2; // the maximum edges of a simple graph with n vertices is n*(n-1)/2
        Edge* edges = new Edge[maxEdgesSize]; 
        for (int i = 0; i < maxEdgesSize; i++)
            edges[i] = Edge(-1,-1,-1,-1);

        int numOfEdges = createAllEdges(graph, edges); // get the number of relevant edges
        sortEdges(edges, numOfEdges); // sort the edges by weight
        Graph tree = Graph(graphSize);
        UnionFind unionFind = UnionFind(graphSize);
        
        for (int i = 0; i < numOfEdges; i++)
        {
            Edge currentEdge = edges[i];
            int representorStart = unionFind.find(currentEdge.start);
            int representorEnd = unionFind.find(currentEdge.end);
            if (representorStart != representorEnd) // if not in the same component -> union them
            {   
                unionFind.Union(representorStart, representorEnd); /// joit components
                tree.addEdge(currentEdge.start, currentEdge.end, currentEdge.weight); // add the edge to the MST
            } 
        }

        delete[] edges;
        return tree;
    }
}

