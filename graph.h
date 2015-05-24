#include <vector>
#include <algorithm>
#include <set>

const long long INF = LLONG_MAX / 2;

class Graph
{
protected:
    size_t size;
    std::vector < std::vector <std::pair <size_t, long long> > > gr;
public:
    Graph()
    {
        size = 0;
    };
    Graph(size_t n)
    {
        size = n;
        gr.resize(n);
    }
    void addVertex()
    {
        size++;
        std::vector <std::pair <size_t, long long> > v;
        gr.push_back(v);
    }
    void addEdge(size_t first, size_t second, long long weight)
    {
        if (first >= size || second >= size)
            return;
        gr[first].push_back(std::make_pair(second, weight));
    }
    bool isEdge(size_t first, size_t second)
    {
        if (first >= size || second >= size)
            return false;
        for (size_t i = 0; i < gr[first].size(); i++)
            if (gr[first][i].first == second)
                return true;
        return false;
    }
    int dejkstra(size_t start, size_t finish)
    {
        if (start >= size || finish >= size)
            return -1;
        std::set <std::pair <long long, size_t> > setWithDistances;
        std::vector <long long> distance(size + 1, INF);
        for (size_t i = 0; i < size; i++)
        {
            if (i == start)
                setWithDistances.insert(std::make_pair(0, i));
            else
                setWithDistances.insert(std::make_pair(INF, i));
        }
        distance[start] = 0;
        for (size_t i = 0; i < size; i++)
        {
            long long curr = setWithDistances.begin()->second;
            distance[curr] = setWithDistances.begin()->first;
            if (distance[curr] == INF)
                break;
            for (size_t j = 0; j < gr[curr].size(); j++)
            {
                std::set <std::pair <long long, size_t> >::iterator it;
                it = setWithDistances.find(std::make_pair(distance[gr[curr][j].first], gr[curr][j].first));
                if (it == setWithDistances.end())
                    continue;
                if (it->first > distance[curr] + gr[curr][j].second)
                {
                    long long next = it->second;
                    distance[next] = distance[curr] + gr[curr][j].second;
                    setWithDistances.erase(it);
                    setWithDistances.insert(std::make_pair(distance[next], next));
                }
            }
            setWithDistances.erase(setWithDistances.begin());
        }
        if (distance[finish] == INF)
            return -1;
        else
            return distance[finish];

    }
};

class SlowGraph : public Graph
{
private:
    std::vector < std::vector < long long > > distances;
public:
    SlowGraph()
    {
        size = 0;
    };
    SlowGraph(size_t n)
    {
        size = n;
        gr.resize(n);
    }
    void floid()
    {
        std::vector <long long> v(size, INF);
        distances.assign(size, v);
        for (size_t i = 0; i < size; i++)
            for (size_t j = 0; j < gr[i].size(); j++)
                distances[i][gr[i][j].first] = std::min(distances[i][gr[i][j].first], gr[i][j].second);
        for (size_t middle = 0; middle < size; middle++)
            for (size_t i = 0; i < size; i++)
                for (size_t j = 0; j < size; j++)
                    distances[i][j] = std::min(distances[i][middle] + distances[middle][j], distances[i][j]);
        for (size_t i = 0; i < size; i++)
            for (size_t j = 0; j < size; j++)
                if (distances[i][j] == INF)
                    distances[i][j] = -1;
    }
    long long getDistance(size_t first, size_t second)
    {
        if (distances.empty() || first >= size || second >= size)
            return -1;
        else
            return distances[first][second];
    }
};
