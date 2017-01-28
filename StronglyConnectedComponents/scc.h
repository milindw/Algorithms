#ifndef _SCC_H
#define _SCC_H

#include <vector>
#include <string>
#include <set>

class AdjacentVertex
{
public:
    int Vertex;
    std::vector<int> m_AdjVertex;
};

using string = std::string;
using VertexVector = std::vector<AdjacentVertex>;

class AdjacencyList
{
public:
    AdjacencyList(int nVertexCount=0);
    void ReadInputFile(const string& sInputFile);
    void RunSCC();
    void PrintSCCSizes();

private:
    VertexVector m_AdjList;
    VertexVector m_RevAdjList;
    std::vector<bool> m_VisitedNodes;
    std::vector<int> m_FinishTime;
    std::multiset<int> m_CountSCCs;
    int m_SCCSize;

    void CreateReverseAdjList();
    void DFS(VertexVector& AdjList, int StartNode, bool bSetFinishes);
};

#endif
