#include "apsp.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <limits>
#include <algorithm>
#include <memory>
#include <sstream>
#include <fstream>

using std::cout;

WeightedEdge::WeightedEdge(int nVertex1, int nVertex2, int nWeight)
: Vertex1{nVertex1}, 
  Vertex2{nVertex2}, 
  Weight{nWeight}
{
}

APSP::APSP()
: m_NumVertices {0}
{ 
    
}

void APSP::ReadInputFile(const string& sInputFile)
{
    std::ifstream ips(sInputFile);

    if(! ips.is_open())
        return;

    string sLine;

    getline(ips, sLine);

    std::stringstream ssFLine(sLine);

    ssFLine >> m_NumVertices;

    auto num_edges {0};
    ssFLine >> num_edges;

    m_EdgeList.reserve(num_edges);

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

    ips.close();
    return;
}

int APSP::GetShortestPathAllVertices()
{

    for(int i = 0; i < m_NumVertices; i++)
    {
        for(int j = 0; j < m_NumVertices; j++)
        {
            if(i != j)
                Floyd_Warshall[i][j][0] = std::numeric_limits<int>::max();
                
        }
    }

    for(auto& edge : m_EdgeList)
    {
        Floyd_Warshall[edge.Vertex1][edge.Vertex2][0] = edge.Weight;
    }

    for(int k = 1; k < m_NumVertices; k++)
    {
        for(int i = 0; i < m_NumVertices; i++)
        {
            for(int j = 0; j < m_NumVertices; j++)
            {
                // if we get a max_int result, then adding will result in overflow to -ve.
                if(Floyd_Warshall[i][k][k-1] == std::numeric_limits<int>::max() || Floyd_Warshall[k][j][k-1] == std::numeric_limits<int>::max())
                    Floyd_Warshall[i][j][k] = Floyd_Warshall[i][j][k-1];
                else
                    Floyd_Warshall[i][j][k] = std::min( Floyd_Warshall[i][j][k-1], Floyd_Warshall[i][k][k-1] + Floyd_Warshall[k][j][k-1]);
            }
        }
    }

    for(int test = 0; test < m_NumVertices; test++)
    {
        if(Floyd_Warshall[test][test][m_NumVertices-1] < 0)
        {
            cout << "Negative cycle detected" << '\n';
            return std::numeric_limits<int>::max();
        }
    }

    auto shortest_path = std::numeric_limits<int>::max();

    for(int i = 0; i < m_NumVertices; i++)
    {
        for(int j = 0; j < m_NumVertices; j++)
        {
            if(i != j && Floyd_Warshall[i][j][m_NumVertices-1] < shortest_path)
                shortest_path = Floyd_Warshall[i][j][m_NumVertices-1];
        }
    }

    return shortest_path;
}

int main()
{
    std::vector<string> sFiles {"g1.txt","g2.txt","g3.txt"};

    for(auto& file : sFiles)
    {
        std::unique_ptr<APSP> obj {new APSP()};
        obj->ReadInputFile(file);
        cout << "File " << file << " Shortest path: " << obj->GetShortestPathAllVertices() << '\n';
    }
    return 0;
}
