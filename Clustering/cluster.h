#include<vector>
#include<forward_list>
#include<string>

using std::string;

class VertexUnion
{
public:
    VertexUnion(int Vertex);

    int Leader;
    int Size;
    std::forward_list<int> Chain;
};


class WeightedEdge
{
public:
    WeightedEdge(int nVertex1, int nVertex2, int nWeight);
    int Vertex1;
    int Vertex2;
    int Weight;
};



class ClusterGraph
{
public:
    ClusterGraph() { }
    void ReadInputFile(const string& sInputFile);
    int GetMaxClusterDistance(const int Num_Clusters);

private:
    std::vector<VertexUnion> m_VertexUnion;
    std::vector<WeightedEdge> m_EdgeList;
};
