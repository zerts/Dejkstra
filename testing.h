#include <iostream>
#include "graph.h"
#include "Edge.h"

const long long INF = LLONG_MAX / 2;

const size_t NUMBER_OF_TESTS_OF_GRAPH_WITH_CURRENT_SIZE = 4;

std::pair<size_t, size_t> genPairOfVertexes(size_t numberOfVertex)
{
    size_t _first = rand() % numberOfVertex, _second = rand() % numberOfVertex;
    while (_first == _second)
        _second = rand() % numberOfVertex;
    return std::make_pair(_first, _second);
}

class BasicEdge : public Edge
{
public:
    long long weightOfEdge;
    BasicEdge(){};
    BasicEdge(size_t _first, size_t _second, long long _weightOfEdge)
    {
        first = _first;
        second = _second;
        weightOfEdge = _weightOfEdge;
    }
    long long getDistance(long long currDistance)
    {
        return weightOfEdge;
    }
    void generateEdge(size_t numberOfVertex)
    {
        std::pair <size_t, size_t> edge = genPairOfVertexes(numberOfVertex);
        long long _weight = rand();
        BasicEdge(edge.first, edge.second, _weight);
    }
};

class BusEdge : public Edge
{
public:
    long long timeOfEnd, timeOfBegin;
    BusEdge(){};
    BusEdge(size_t _first, size_t _second, long long _timeOfBegin, long long _timeOfEnd)
    {
        first = _first;
        second = _second;
        timeOfEnd = _timeOfEnd;
        timeOfBegin = _timeOfBegin;
    }
    long long getDistance(long long currDistance)
    {
        if (currDistance <= timeOfBegin)
            return timeOfEnd - currDistance;
        else
            return INF;
    }
    void generateEdge(size_t numberOfVertex)
    {
        std::pair <size_t, size_t> edge = genPairOfVertexes(numberOfVertex);
        long long _timeOfBegin = rand(), _timeOfEnd = rand();
        BusEdge(edge.first, edge.second, _timeOfBegin, _timeOfEnd);
    }
};

long long weightOfCar;

class CupEdge : public Edge
{
public:
    long long weightOfEdge, maxWeightOfCar;
    CupEdge(){};
    CupEdge(size_t _first, size_t _second, long long _weightOfEdge, long long _maxWeightOfCar)
    {
        first = _first;
        second = _second;
        weightOfEdge = _weightOfEdge;
        maxWeightOfCar = _maxWeightOfCar;
    }
    long long getDistance(long long currDistance)
    {
        if (weightOfCar <= maxWeightOfCar)
            return weightOfEdge;
        else
            return INF;
    }
    void generateEdge(size_t numberOfVertex)
    {
        std::pair <size_t, size_t> edge = genPairOfVertexes(numberOfVertex);
        long long _weight = rand(), _maxWeightOfCar = rand() + 3000000ll;
        CupEdge(edge.first, edge.second, _weight, _maxWeightOfCar);
    }
};

bool testingWithCurrentSize(size_t n)
{
    if (n <= 1)
        return true;
    bool result = true;
    Graph <BasicEdge> graph(n);
    SlowGraph <BasicEdge> rightGraph(n);
    size_t maxEdges = (n * (n - 1));
    for (int i = 0; i < NUMBER_OF_TESTS_OF_GRAPH_WITH_CURRENT_SIZE; i++)
    {
        size_t numberOfEdges = (rand() % (maxEdges / 2)) + (maxEdges / 2);
        for (size_t j = 0; j < numberOfEdges; j++)
        {
            BasicEdge newEdge;
            newEdge.generateEdge(n);
            graph.addEdge(newEdge);
            rightGraph.addEdge(newEdge);
        }
        rightGraph.floyd();
        for (size_t start = 0; start < n; start++)
        {
            for (size_t finish = 0; finish < n; finish += 10)
            { 
                if (start != finish)
                {
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
    for (int i = 1; i < 2000; i += 2)
    {
        result &= testingWithCurrentSize(i);
        if (result)
            std::cout << i << " = +\n";
        else
            std::cout << i << " = -\n";
        //system("pause");
    }
    return result;
}
