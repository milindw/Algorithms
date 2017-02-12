#include<vector>
#include<string>

using std::string;

class WeightedEdge
{
public:
    WeightedEdge(int nVertex1, int nVertex2, int nWeight);
    int Vertex1;
    int Vertex2;
    int Weight;
};

const int arrsize = 1000;

class APSP
{
public:
    APSP();
    void ReadInputFile(const string& sInputFile);
    int GetShortestPathAllVertices();

private:
    std::vector<WeightedEdge> m_EdgeList;
    int m_NumVertices;

//    int Floyd_Warshall[m_NumVertices][m_NumVertices][m_NumVertices] {};
    int Floyd_Warshall[arrsize][arrsize][arrsize] {};
};
