#include <vector>
#include <string>
#include <set>

class WeightedVertex
{
public:
    WeightedVertex(int Vertex, int Weight) : nVertex{Vertex}, nWeight{Weight} { }

    int nVertex;
    int nWeight;
};

class WeightedVertexCompare
{
public:
    bool operator()(const WeightedVertex& lhs, const WeightedVertex& rhs) const
    {
        if(lhs.nWeight > rhs.nWeight)
            return false;
        else
            return true;
    }
};

class AdjacentVertex
{
public:
    int nVertex;
    std::vector<WeightedVertex> m_AdjVertices;
};

using std::string;
using std::vector;
using VertexVector = vector<AdjacentVertex>;
using std::multiset;


class DijkstraMinPath
{
public:
    DijkstraMinPath();
    void ReadInputFile(const string& sInputFile);
    void CalcMinPath();
    void Output();

private:
    VertexVector m_AdjList;
    vector<int> m_MinPath;
    vector<bool> m_Visited;
    multiset<WeightedVertex, WeightedVertexCompare> m_GreedyScore;   

    const int m_MaxDistance = 1000000; 
};
