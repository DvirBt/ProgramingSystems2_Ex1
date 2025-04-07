// email: dvirbto@gmail.com

#include "Graph.hpp"

namespace graph
{
    /**
     * This class represents all the algorithms that are required to implement.
     * Further details are given in the cpp file.
     */
    class Algorithms
    {
        public:
            Algorithms();
            ~Algorithms();
            Graph bfs(const Graph& graph, int source);
            Graph dfs(const Graph& graph, int source);
            Graph dijkstra(const Graph& graph, int source);
            Graph prim(const Graph& graph);
            Graph kruskal(const Graph& graph);
    };
}

