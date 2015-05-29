#include <vector>
#include <algorithm>
#include <set>

const long long INF = LLONG_MAX / 2;

template <class Edge>
class Graph
{
protected:
    size_t size;
    std::vector < std::vector <Edge> > gr;
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
    void addEdge(Edge newEdge)
    {
        if (newEdge.first >= size || newEdge.second >= size)
            return;
        gr[newEdge.first].push_back(newEdge);
    }
    bool isEdge(size_t first, size_t second)
    {
        if (first >= size || second >= size)
            return false;
        for (size_t i = 0; i < gr[first].size(); i++)
            if (gr[first][i].second == second)
                return true;
        return false;
    }
    std::vector <long long> countDistances(size_t start)
    {
        std::set <std::pair <long long, size_t> > setWithDistances;
        std::vector <long long> distance(size, INF);
        distance[start] = 0;
        setWithDistances.insert(std::make_pair(distance[start], start));
        while (!setWithDistances.empty())
        {
            size_t curr = setWithDistances.begin()->second;
            setWithDistances.erase(setWithDistances.begin());
            for (size_t j = 0; j < gr[curr].size(); ++j)
            {
                size_t next = gr[curr][j].second;
                long long lengthOfCurrEdge = gr[curr][j].getDistance(distance[curr]);
                if (lengthOfCurrEdge < INF && distance[curr] + lengthOfCurrEdge < distance[next])
                {
                    setWithDistances.erase(std::make_pair(distance[next], next));
                    distance[next] = distance[curr] + lengthOfCurrEdge;
                    setWithDistances.insert(std::make_pair(distance[next], next));
                }
            }
        }
        return distance;
    }
    long long dejkstra(size_t start, size_t finish)
    {
        if (start >= size || finish >= size)
            return -1;
        std::vector <long long> distance = countDistances(start);
        if (distance[finish] >= INF)
            return INF;
        else
            return distance[finish];
    }
    void dejkstraToAll(size_t start)
    {
        if (start >= size)
            return;
        std::vector <long long> distance = countDistances(start);
        for (int i = 0; i < size; i++)
            if (distance[i] < INF)
                std::cout << distance[i] << ' ';
            else
                std::cout << "2009000999 ";
        std::cout << std::endl;
    }
};

template <class Edge>
class SlowGraph : public Graph <Edge>
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
    void floyd()
    {
        std::vector <long long> v(size, INF);
        distances.assign(size, v);
        for (size_t i = 0; i < size; i++)
            for (size_t j = 0; j < gr[i].size(); j++)
                distances[i][gr[i][j].second] = std::min(distances[i][gr[i][j].second], gr[i][j].getDistance(0ll));
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
            return -1ll;
        else
            return distances[first][second];
    }
};
