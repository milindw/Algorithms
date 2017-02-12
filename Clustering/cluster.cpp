#include "cluster.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>

using std::cout;

VertexUnion::VertexUnion(int Vertex)
: Leader{Vertex},
  Size{1}
{
    Chain.push_front(Vertex);
}

VertexUnion& operator+(VertexUnion& lhs, VertexUnion& rhs)
{
    rhs.Leader = lhs.Leader;
    lhs.Size += rhs.Size;
    rhs.Size = 0;

    lhs.Chain.splice_after(lhs.Chain.before_begin(), rhs.Chain);

    return lhs;
}

WeightedEdge::WeightedEdge(int nVertex1, int nVertex2, int nWeight)
: Vertex1{nVertex1}, 
  Vertex2{nVertex2}, 
  Weight{nWeight}
{
}

bool operator<(const WeightedEdge& lhs, const WeightedEdge& rhs)
{
    if(lhs.Weight < rhs.Weight)
        return true;
    else
        return false;
}

void ClusterGraph::ReadInputFile(const string& sInputFile)
{
    std::ifstream ips(sInputFile);

    if(! ips.is_open())
        return;

    string sLine;

    getline(ips, sLine);
    auto num_vertices = std::stoi(sLine);

    m_VertexUnion.reserve(num_vertices);
    for(int i = 0; i < num_vertices; i++)
        m_VertexUnion.push_back( VertexUnion {i} );

    while(getline(ips, sLine))
    {
        std::stringstream ssWeightedEdges(sLine);

        int Vertex1 {0}, Vertex2 {0}, EdgeWeight {0};

        ssWeightedEdges >> Vertex1;
        Vertex1--;

        ssWeightedEdges >> Vertex2;
        Vertex2--;

        ssWeightedEdges >> EdgeWeight;

        m_EdgeList.push_back( WeightedEdge {Vertex1, Vertex2, EdgeWeight} );        
    }
}

int ClusterGraph::GetMaxClusterDistance(const int Num_Clusters)
{
    // sort the vector by descending order of weights

    std::sort(m_EdgeList.begin(), m_EdgeList.end());

    auto ClusterSize = m_VertexUnion.size();
    auto EdgeIndex {0};

    while(ClusterSize > Num_Clusters)
    {
        auto Vertex1 = m_EdgeList[EdgeIndex].Vertex1;
        auto Vertex2 = m_EdgeList[EdgeIndex].Vertex2;

        auto LeaderVertex1 = m_VertexUnion[Vertex1].Leader;
        auto LeaderVertex2 = m_VertexUnion[Vertex2].Leader;

        if(LeaderVertex1 != LeaderVertex2)
        {
            ClusterSize--;
        }
        else
        {
            EdgeIndex++;
            continue;
        }


        if(m_VertexUnion[LeaderVertex1].Size < m_VertexUnion[LeaderVertex2].Size)
        {
            // update vertex1 leader chain to vertex2
            for(auto vertex : m_VertexUnion[LeaderVertex1].Chain)
                m_VertexUnion[vertex].Leader = LeaderVertex2;

            m_VertexUnion[LeaderVertex2] + m_VertexUnion[LeaderVertex1];
        }
        else
        {
            // update vertex2 leader chain to vertex1
            for(auto vertex : m_VertexUnion[LeaderVertex2].Chain)
                m_VertexUnion[vertex].Leader = LeaderVertex1;

            m_VertexUnion[LeaderVertex1] + m_VertexUnion[LeaderVertex2];
        }

        // join the vertices into a cluster

        EdgeIndex++;
    }

    while(EdgeIndex < m_EdgeList.size())
    {
        if(m_VertexUnion[m_EdgeList[EdgeIndex].Vertex1].Leader == 
           m_VertexUnion[m_EdgeList[EdgeIndex].Vertex2].Leader)
        {
            // they are part of a cluster, so go to next edge
            EdgeIndex++;
        }
        else
            break;
    }

    return m_EdgeList[EdgeIndex].Weight;
}

int main()
{
    ClusterGraph graph;

    graph.ReadInputFile("input.txt");
    cout << graph.GetMaxClusterDistance(4);
}
