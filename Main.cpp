// email: dvirbto@gmail.com

#include "Algorithms.hpp"
#include "Queue.hpp"
#include <iostream>
using namespace graph;
using namespace std;

/**
 * The Main of the project
 */
int main()
{
    // create the graph
    Graph myGraph = Graph(7);
    myGraph.addEdge(0,2,1);
    myGraph.addEdge(0,5,0);
    myGraph.addEdge(0,1,2);
    myGraph.addEdge(1,2,0);
    myGraph.addEdge(1,3,4);
    myGraph.addEdge(1,6,3);
    myGraph.addEdge(1,4,4);
    myGraph.addEdge(2,6,2);
    myGraph.addEdge(3,6,1);
    myGraph.addEdge(4,5,1);
    cout << "This is the graph" << endl;
    cout << "-----------------" << endl;
    myGraph.print_graph();
    Algorithms algorithms = Algorithms();

    while (true)
    {
        int choice;
        cout << "Enter the number of algorithm that you want to perform:" << endl;
        cout << "1. BFS\n2. DFS\n3. Dijkstra\n4. Prims\n5. Kruskal\n0. Exit" << endl;
        cin >> choice;
        cout << endl;
        if (choice == 0)
            break;

        int source;
        switch (choice)
        {
            case 1: // BFS
            {
                cout << "Enter source vertex number 0-" << myGraph.getSize()-1 << endl;
                cin >> source;
                Graph bfs = algorithms.bfs(myGraph, source);
                cout << "BFS Algorithm" << endl;
                cout << "-------------" << endl;
                bfs.print_graph();
                break;
            }


            case 2: // DFS
            {
                cout << "Enter source vertex number 0-" << myGraph.getSize()-1 << endl;
                cin >> source;
                Graph dfs = algorithms.dfs(myGraph, source);
                cout << "DFS Algorithm" << endl;
                cout << "-------------" << endl;
                dfs.print_graph();
                break;
            }

            
            case 3: // Dijkstra
            {
                cout << "Enter source vertex number 0-" << myGraph.getSize()-1 << endl;
                cin >> source;
                cout << "Dijkstra's Algorithm" << endl;
                cout << "--------------------" << endl;
                Graph dijkstra = algorithms.dijkstra(myGraph, source);
                break;
            }

            
            case 4: // Prim's
            {
                Graph prims = algorithms.prim(myGraph);
                cout << "Prim's Algorithm" << endl;
                cout << "----------------" << endl;
                prims.print_graph();
                break;               
            }

            
            case 5: // Kruskal
            {
                Graph kruskal = algorithms.kruskal(myGraph);
                cout << "Kruskal's Algorithm" << endl;
                cout << "-------------------" << endl;
                kruskal.print_graph();
                break;
            }

            default:
                cout << "An invalid number of algorithm or exit code is recived!/nPlease try again\n" << endl;
                break;
        }
    }

    cout << "Bye bye!" << endl;
    return 0;
}