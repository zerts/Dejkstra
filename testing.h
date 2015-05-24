#include <iostream>
#include "graph.h"

const size_t NUMBER_OF_TESTS_OF_GRAPH_WITH_CURRENT_SIZE = 2;

std::pair <size_t, size_t> generateEdge(size_t numberOfVertex)
{
    size_t first = rand() % numberOfVertex, second = rand() % numberOfVertex;
    while (first == second)
        second = rand() % numberOfVertex;
    return std::make_pair(first, second);
}

bool testingWithCurrentSize(size_t n)
{
    bool result = true;
    Graph graph(n);
    SlowGraph rightGraph(n);
    size_t maxEdges = (n * (n - 1));
    for (int i = 0; i < NUMBER_OF_TESTS_OF_GRAPH_WITH_CURRENT_SIZE; i++)
    {
        size_t numberOfEdges = (rand() % (maxEdges / 2)) + (maxEdges / 2);
        for (int j = 0; j < numberOfEdges; j++)
        {
            std::pair <size_t, size_t> newEdge = generateEdge(n);
            long long weight = rand();
            graph.addEdge(newEdge.first, newEdge.second, weight);
            rightGraph.addEdge(newEdge.first, newEdge.second, weight);
        }
        rightGraph.floid();
        std::cout << "floid has finished\n";
        for (size_t start = 0; start < n; start++)
        {
            for (size_t finish = 0; finish < n; finish += 10)
            { 
                if (start != finish)
                {
                    std::cout << start << ' ' << finish << '\n';
                    long long resultOfDjekstra = graph.dejkstra(start, finish);
                    if (resultOfDjekstra != rightGraph.getDistance(start, finish))
                        result = false;
                }
            }
        }
    }
    return result;
}

bool testing()
{
    bool result = true;
    for (int i = 100; i < 200; i += 2)
    {
        result &= testingWithCurrentSize(i);
        if (result)
            std::cout << i << " = +\n";
        else
            std::cout << i << " = -\n";
        system("pause");
    }
    return result;
}
