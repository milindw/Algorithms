#include "dijkstra.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <array>

using std::cout;
using std::cin;
using std::array;

DijkstraMinPath::DijkstraMinPath()
{

}

void DijkstraMinPath::ReadInputFile(const string& sInputFile)
{
    std::ifstream ips(sInputFile);

    if(! ips.is_open())
        return;

    string sLine;

    while(getline(ips, sLine))
    {
        std::stringstream ssWeightedEdges(sLine);

        int Vertex {0}, EdgeVertex {0}, EdgeWeight {0};
        char Comma;

        ssWeightedEdges >> Vertex;
        Vertex--;

        AdjacentVertex AdjVertex;
        AdjVertex.nVertex = Vertex;

        while(!ssWeightedEdges.eof())
        {
            ssWeightedEdges >> EdgeVertex >> Comma >> EdgeWeight;
            if(ssWeightedEdges.fail())
                break;

            EdgeVertex--;
	    
            AdjVertex.m_AdjVertices.push_back(WeightedVertex{EdgeVertex, EdgeWeight});
        }

        m_AdjList.push_back(AdjVertex);
    }

    ips.close();

    return;
}

void DijkstraMinPath::CalcMinPath()
{
    m_MinPath.resize(m_AdjList.size());
    m_Visited.resize(m_AdjList.size(), false);

    // populate multiset with max distances, except for source vertex
    m_GreedyScore.insert(WeightedVertex {0,0});
    for(auto it = m_AdjList.begin()+1; it != m_AdjList.end(); it++)
    {
        m_GreedyScore.insert(WeightedVertex {(*it).nVertex, m_MaxDistance});
    }

    // start loop and pick shortest paths from the heap

    while(m_GreedyScore.size() != 0)
    {
        auto MinIt = m_GreedyScore.begin();

        auto MinVertex = (*MinIt).nVertex;
        auto MinWeight = (*MinIt).nWeight;

        // update the min path vector
        m_MinPath[MinVertex] = MinWeight;
        m_Visited[MinVertex] = true;

        // remove this from the heap
        m_GreedyScore.erase(MinIt);

        // using adjacency list, find the vertices that need to be updated
        // not a very optimal solution, can be done better
        for(auto it = m_AdjList[MinVertex].m_AdjVertices.begin(); it != m_AdjList[MinVertex].m_AdjVertices.end(); ++it)
        {
            if(m_Visited[(*it).nVertex])
                continue;

            for(auto itg = m_GreedyScore.begin(); itg != m_GreedyScore.end(); ++itg)
            {
                if((*itg).nVertex == (*it).nVertex)
                {
                    // check if greedy score needs to be updated
                    if(MinWeight + (*it).nWeight < (*itg).nWeight)
                    {
                        m_GreedyScore.erase(itg);
                        m_GreedyScore.insert( WeightedVertex {(*it).nVertex , MinWeight + (*it).nWeight});
                    }
                    break;
                }
            }
        }
    }
}

void DijkstraMinPath::Output()
{
/*
    array<int, 10> outputs {7,37,59,82,99,115,133,165,188,197};
    for(auto x : outputs)
        cout << "Min path to " << x << " is " << m_MinPath[x-1] << "\n";
*/
    int i = 1;
    for(auto x : m_MinPath)
        cout << "Min path to " << i++ << " is " << x << "\n";

}

int main()
{
    DijkstraMinPath dMinPath;

    dMinPath.ReadInputFile("input.txt");
    dMinPath.CalcMinPath();

    dMinPath.Output();

    return 0;
}
