// email: dvirbto@gmail.com

/**
 * This cpp file contains all the tests using doctest
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "Algorithms.hpp"
#include "Queue.hpp"
#include "UnionFind.hpp"
#include "Graph.hpp"
using namespace graph;
using namespace std;

// Queue class START
TEST_CASE("Testing the Queue class functions")
{
    Queue queue = Queue(2);
    CHECK(queue.isEmpty() == true);
    CHECK(queue.isFull() == false);
    CHECK(queue.getSize() == 0);
    queue.enQueue(1);
    CHECK(queue.isEmpty() == false);
    CHECK(queue.isFull() == false);
    CHECK(queue.getSize() == 1);
    queue.enQueue(2); 
    CHECK(queue.getSize() == 2);
    queue.enQueue(3); // exceeded limitation
    CHECK(queue.getSize() == 2);
    CHECK(queue.isFull() == true);
    int removed = queue.deQueue(); // removed = 1 -> first variable that entered the queue
    CHECK(removed == 1);
    queue.enQueue(0); // new minumum
    removed = queue.extractMin(); // removed = 0 -> the minimum
    CHECK(removed == 0);
}
// Queue class END

// Union find START
TEST_CASE("Testing the Union find class functions")
{
    UnionFind unionFind = UnionFind(4);
    CHECK(unionFind.find(0) == 0);
    CHECK(unionFind.find(1) == 1);
    CHECK(unionFind.find(2) == 2);
    CHECK(unionFind.find(3) == 3);
    CHECK_THROWS(unionFind.find(4)); // exception 
    CHECK_THROWS(unionFind.find(5)); // exception
    CHECK_THROWS(unionFind.find(-1)); // exception
    unionFind.Union(0,1);
    CHECK(unionFind.find(0) == 0);
    CHECK(unionFind.find(1) == 0);
    CHECK(unionFind.find(2) == 2);
    CHECK(unionFind.find(3) == 3);
    unionFind.Union(1,0); // should do nothing because they are in the same group
    CHECK(unionFind.find(0) == 0);
    CHECK(unionFind.find(1) == 0);
    unionFind.Union(1, 2); // 2's representetive should now be 1's representetive which is 0
    CHECK(unionFind.find(0) == 0);
    CHECK(unionFind.find(1) == 0);
    CHECK(unionFind.find(2) == 0);
    CHECK(unionFind.find(3) == 3);
    unionFind.Union(3, 2); // 2's representetive should now be 3's representetive which is 3
    CHECK(unionFind.find(0) == 3);
    CHECK(unionFind.find(1) == 3);
    CHECK(unionFind.find(2) == 3);
    CHECK(unionFind.find(3) == 3);
}
// Union find END 

// Graph class START
TEST_CASE("Testing the Graph class functions")
{
    Graph graph = Graph(5);
    CHECK(graph.getSize() == 5);
    CHECK(graph.getVerticesList()[0] == nullptr);
    CHECK(graph.getVerticesList()[1] == nullptr);
    CHECK(graph.getVerticesList()[2] == nullptr);
    CHECK(graph.getVerticesList()[3] == nullptr);
    CHECK(graph.getVerticesList()[4] == nullptr);
    CHECK(graph.isEdgeExist(0,1) == false);
    graph.addEdge(0,1,10); // added edge 0->1 and 1->0
    CHECK(graph.isEdgeExist(0,1) == true);
    CHECK(graph.getVerticesList()[0]->num == 1);
    CHECK(graph.getVerticesList()[1]->num == 0);
    CHECK(graph.getVerticesList()[2] == nullptr);
    CHECK(graph.getVerticesList()[3] == nullptr);
    CHECK(graph.getVerticesList()[4] == nullptr);
    graph.addEdge(0,2,5); // added edge 0->2 and 2->0
    graph.print_graph();
    CHECK(graph.getVerticesList()[0]->num == 2);
    CHECK(graph.getVerticesList()[1]->num == 0);
    CHECK(graph.getVerticesList()[2]->num == 0);
    CHECK(graph.getVerticesList()[3] == nullptr);
    CHECK(graph.getVerticesList()[4] == nullptr);
    graph.removeEdge(0,1); // remove edge 0->1 and 1->0
    CHECK(graph.getVerticesList()[0]->num == 2);
    CHECK(graph.getVerticesList()[1] == nullptr);
    CHECK(graph.getVerticesList()[2]->num == 0);
    CHECK(graph.getVerticesList()[3] == nullptr);
    CHECK(graph.getVerticesList()[4] == nullptr);
    graph.removeEdge(2,0); // remove edge 0->2 and 2->0
    CHECK(graph.getVerticesList()[0] == nullptr);
    CHECK(graph.getVerticesList()[1] == nullptr);
    CHECK(graph.getVerticesList()[2] == nullptr);
    CHECK(graph.getVerticesList()[3] == nullptr);
    CHECK(graph.getVerticesList()[4] == nullptr);
    graph.addEdge(1,4,0);
    CHECK(graph.getVerticesList()[1]->num == 4);
    CHECK(graph.getVerticesList()[4]->num == 1);
    // check exceptions
    CHECK_THROWS(graph.removeEdge(0,1)); // edge no longer exists
    CHECK_THROWS(graph.addEdge(1,1,0)); // no such edge from vertex to itself
    CHECK_THROWS(graph.addEdge(-1,1,0)); // negative index of a vertex is not allowed
    CHECK_THROWS(graph.addEdge(1,5,0)); // max vertex id is the (graph.Size-1)
}
// Graph class END

// Algorithms class START
TEST_CASE("Testing the Algorithms class functions")
{
    Algorithms algorithms = Algorithms();
    Graph validGraph = Graph(7);
    // build the graph
    validGraph.addEdge(0,2,1);
    validGraph.addEdge(0,5,0);
    validGraph.addEdge(0,1,2);
    validGraph.addEdge(1,2,0);
    validGraph.addEdge(1,3,4);
    validGraph.addEdge(1,6,3);
    validGraph.addEdge(1,4,4);
    validGraph.addEdge(2,6,2);
    validGraph.addEdge(3,6,1);
    validGraph.addEdge(4,5,1);

    Graph bfs = algorithms.bfs(validGraph, 0);
    cout << endl;
    cout << "BFS graph with source 0" << endl;
    cout << "-----------------------" << endl;
    bfs.print_graph();
        
    // edges that should exist
    CHECK(bfs.isEdgeExist(0,1) == true);
    CHECK(bfs.isEdgeExist(0,2) == true);
    CHECK(bfs.isEdgeExist(0,5) == true);
    CHECK(bfs.isEdgeExist(1,3) == true);
    CHECK(bfs.isEdgeExist(1,4) == true);
    CHECK(bfs.isEdgeExist(1,6) == true);

    // edges that should not exist 
    CHECK(bfs.isEdgeExist(0,4) == false);
    CHECK(bfs.isEdgeExist(0,3) == false);
    CHECK(bfs.isEdgeExist(0,6) == false);
    CHECK(bfs.isEdgeExist(1,5) == false);
    CHECK(bfs.isEdgeExist(2,1) == false);
    CHECK(bfs.isEdgeExist(2,3) == false);
    CHECK(bfs.isEdgeExist(2,4) == false);
    CHECK(bfs.isEdgeExist(2,5) == false);
    CHECK(bfs.isEdgeExist(2,6) == false);
    CHECK(bfs.isEdgeExist(3,0) == false);
    CHECK(bfs.isEdgeExist(3,4) == false);
    CHECK(bfs.isEdgeExist(3,5) == false);
    CHECK(bfs.isEdgeExist(3,6) == false);
    CHECK(bfs.isEdgeExist(4,6) == false);
    CHECK(bfs.isEdgeExist(4,5) == false);
    CHECK(bfs.isEdgeExist(5,6) == false);

    Graph dfs = algorithms.dfs(validGraph, 0);
    cout << endl;
    cout << "DFS graph with source 0" << endl;
    cout << "-----------------------" << endl;
    dfs.print_graph();

    // edges that should exist
    CHECK(dfs.isEdgeExist(2,6) == true);
    CHECK(dfs.isEdgeExist(0,1) == true);
    CHECK(dfs.isEdgeExist(1,4) == true);
    CHECK(dfs.isEdgeExist(1,6) == true);
    CHECK(dfs.isEdgeExist(6,3) == true);
    CHECK(dfs.isEdgeExist(5,4) == true);

    // edges that should not exist 
    CHECK(dfs.isEdgeExist(2,0) == false);
    CHECK(dfs.isEdgeExist(2,1) == false);
    CHECK(dfs.isEdgeExist(0,5) == false);
    CHECK(dfs.isEdgeExist(1,3) == false);
    CHECK(dfs.isEdgeExist(0,4) == false);
    CHECK(dfs.isEdgeExist(0,6) == false);
    CHECK(dfs.isEdgeExist(0,3) == false);
    CHECK(dfs.isEdgeExist(1,5) == false);
    CHECK(dfs.isEdgeExist(2,3) == false);
    CHECK(dfs.isEdgeExist(2,4) == false);
    CHECK(dfs.isEdgeExist(2,5) == false);
    CHECK(dfs.isEdgeExist(3,0) == false);
    CHECK(dfs.isEdgeExist(3,4) == false);
    CHECK(dfs.isEdgeExist(3,5) == false);
    CHECK(dfs.isEdgeExist(4,6) == false);
    CHECK(dfs.isEdgeExist(5,6) == false);
        
    validGraph.addEdge(1,5,-2); // add an edge with negative weight
    CHECK_THROWS(algorithms.dijkstra(validGraph, 0)); // dijkstra does not work with negative edges
    validGraph.removeEdge(1,5);

    Graph dijkstra = algorithms.dijkstra(validGraph, 0);
    cout << endl;
    cout << "Dijkstra graph with source 0" << endl;
    cout << "----------------------------" << endl;
    dijkstra.print_graph();
    
    // edges that should exist when the source is 0
    // from 0 to 1 the shortest path is: 0->2->1
    CHECK(dijkstra.isEdgeExist(0,2) == true);
    CHECK(dijkstra.isEdgeExist(2,1) == true);

    // from 0 to 2 the shortest path is: 0->2 (already checked above)

    // from 0 to 3 the shortest path is: 0->2->6->3
    // 0->2 checked
    CHECK(dijkstra.isEdgeExist(2,6) == true);
    CHECK(dijkstra.isEdgeExist(6,3) == true);

    // from 0 to 4 the shortest path is: 0->5->4
    CHECK(dijkstra.isEdgeExist(0,5) == true);
    CHECK(dijkstra.isEdgeExist(5,4) == true);

    // from 0 to 5 the shortest path is: 0->5 (already checked above)

    // from 0 to 6 the shortest path is: 0->2->6 (already checked above)
 
    // edges that should not exist 
    CHECK(dijkstra.isEdgeExist(0,1) == false);
    CHECK(dijkstra.isEdgeExist(0,3) == false);
    CHECK(dijkstra.isEdgeExist(0,4) == false);
    CHECK(dijkstra.isEdgeExist(0,6) == false);
    CHECK(dijkstra.isEdgeExist(1,3) == false);
    CHECK(dijkstra.isEdgeExist(1,4) == false);
    CHECK(dijkstra.isEdgeExist(1,6) == false);
    CHECK(dijkstra.isEdgeExist(2,3) == false);
    CHECK(dijkstra.isEdgeExist(2,4) == false);
    CHECK(dijkstra.isEdgeExist(3,4) == false);
    CHECK(dijkstra.isEdgeExist(3,5) == false);
    CHECK(dijkstra.isEdgeExist(4,6) == false);
    CHECK(dijkstra.isEdgeExist(5,6) == false);

    cout << endl;
    cout << "Shortest paths" << endl;
    cout << "--------------" << endl;
    for (int i = 0; i < validGraph.getSize(); i++)
        Graph shortestPaths = algorithms.dijkstra(validGraph, i); // check all shortests paths
    
    
    cout << "Prim's graph" << endl;
    cout << "------------" << endl;
    Graph prims = algorithms.prim(validGraph);
    prims.print_graph();
    
    // edges that should exist
    CHECK(prims.isEdgeExist(0,2) == true);
    CHECK(prims.isEdgeExist(0,5) == true);
    CHECK(prims.isEdgeExist(1,2) == true);
    CHECK(prims.isEdgeExist(2,6) == true);
    CHECK(prims.isEdgeExist(3,6) == true);
    CHECK(prims.isEdgeExist(4,5) == true);

    // edges that should not exist 
    CHECK(prims.isEdgeExist(0,1) == false);
    CHECK(prims.isEdgeExist(0,3) == false);
    CHECK(prims.isEdgeExist(0,4) == false);
    CHECK(prims.isEdgeExist(0,6) == false);
    CHECK(prims.isEdgeExist(1,3) == false);
    CHECK(prims.isEdgeExist(1,4) == false);
    CHECK(prims.isEdgeExist(1,6) == false);
    CHECK(prims.isEdgeExist(2,3) == false);
    CHECK(prims.isEdgeExist(2,4) == false);
    CHECK(prims.isEdgeExist(3,4) == false);
    CHECK(prims.isEdgeExist(3,5) == false);
    CHECK(prims.isEdgeExist(4,6) == false);
    CHECK(prims.isEdgeExist(5,6) == false);

    cout << endl;
    cout << "Kruskal's graph" << endl;
    cout << "---------------" << endl;
    Graph kruskal = algorithms.kruskal(validGraph);
    kruskal.print_graph();
    
    // edges that should exist
    CHECK(kruskal.isEdgeExist(0,2) == true);
    CHECK(kruskal.isEdgeExist(0,5) == true);
    CHECK(kruskal.isEdgeExist(1,2) == true);
    CHECK(kruskal.isEdgeExist(2,6) == true);
    CHECK(kruskal.isEdgeExist(3,6) == true);
    CHECK(kruskal.isEdgeExist(4,5) == true);

    // edges that should not exist 
    CHECK(kruskal.isEdgeExist(0,1) == false);
    CHECK(kruskal.isEdgeExist(0,3) == false);
    CHECK(kruskal.isEdgeExist(0,4) == false);
    CHECK(kruskal.isEdgeExist(0,6) == false);
    CHECK(kruskal.isEdgeExist(1,3) == false);
    CHECK(kruskal.isEdgeExist(1,4) == false);
    CHECK(kruskal.isEdgeExist(1,6) == false);
    CHECK(kruskal.isEdgeExist(2,3) == false);
    CHECK(kruskal.isEdgeExist(2,4) == false);
    CHECK(kruskal.isEdgeExist(3,4) == false);
    CHECK(kruskal.isEdgeExist(3,5) == false);
    CHECK(kruskal.isEdgeExist(4,6) == false);
    CHECK(kruskal.isEdgeExist(5,6) == false);
}
// Algorithms class END