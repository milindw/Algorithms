#include "SCC.h"
#include <fstream>
#include <sstream>
#include <iostream>

AdjacencyList::AdjacencyList(int nVertexCount)
: m_SCCSize {0},
  m_AdjList(nVertexCount)
{ 
}

void AdjacencyList::ReadInputFile(const string& sInputFile)
{
    std::ifstream ips(sInputFile);

    if(! ips.is_open())
        return;

    string sLine;

    while(getline(ips, sLine))
    {
        std::stringstream sEdges(sLine);

        int Vertex {0};
        int EdgeVertex {0};

        sEdges >> Vertex;
        Vertex--;

        sEdges >> EdgeVertex;
        EdgeVertex--;

        m_AdjList[Vertex].Vertex = Vertex;
        m_AdjList[Vertex].m_AdjVertex.push_back(EdgeVertex);
    }

    ips.close();
    return;
}

void AdjacencyList::RunSCC()
{
    CreateReverseAdjList();

    m_VisitedNodes.resize(m_AdjList.size(), false);
    m_FinishTime.reserve(m_AdjList.size());

    for(int nLoop = m_RevAdjList.size()-1; nLoop >= 0; nLoop--)
    {
        if(!m_VisitedNodes[nLoop])
        {
            DFS(m_RevAdjList, nLoop, true);
        }
    }

    // since all nodes are visited, flip bits to false
    m_VisitedNodes.flip();

    // in reverse order of finish time
    for(auto FinishIt = m_FinishTime.rbegin(); FinishIt != m_FinishTime.rend(); ++FinishIt)
    {
        if(!m_VisitedNodes[*FinishIt])
        {
            m_SCCSize = 0;
            DFS(m_AdjList, *FinishIt, false);
            m_CountSCCs.insert(m_SCCSize);
        }
    }
    
}

void AdjacencyList::DFS(VertexVector& AdjList, int StartNode, bool bSetFinishes)
{
    m_VisitedNodes[StartNode] = true;

    if(!bSetFinishes)
    {
        m_SCCSize++;
    }

    for(auto adjvertex : AdjList[StartNode].m_AdjVertex)
    {
        if(!m_VisitedNodes[adjvertex])
        {
            DFS(AdjList, adjvertex, bSetFinishes);
        }
    }
    if(bSetFinishes)
    {
        m_FinishTime.push_back(StartNode);
    }
}

void AdjacencyList::CreateReverseAdjList()
{
    m_RevAdjList.resize(m_AdjList.size());

    for( auto vertex : m_AdjList)
    {
        for(auto adjvertex : vertex.m_AdjVertex)
        {
            m_RevAdjList[adjvertex].Vertex = adjvertex;
            m_RevAdjList[adjvertex].m_AdjVertex.push_back(vertex.Vertex);
        }
    }
}

void AdjacencyList::PrintSCCSizes()
{
    auto SizeIt = m_CountSCCs.rbegin();
    for(int i =0; i<5; i++)
        std::cout << *(SizeIt++) << "\n";
}

int main()
{
    constexpr int nVertexCount = 875714;
    const string sInputFile {"SCCInput.txt"};

    AdjacencyList adjList(nVertexCount);

    adjList.ReadInputFile(sInputFile);
    adjList.RunSCC();
    adjList.PrintSCCSizes();

    return 0;
}
