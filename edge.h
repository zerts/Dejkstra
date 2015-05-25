class Edge
{
public:
    size_t first, second;
    virtual long long getDistance(long long) = 0;
    virtual void generateEdge(size_t) = 0;
};
