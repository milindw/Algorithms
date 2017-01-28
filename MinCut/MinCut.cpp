#include "MinCut.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>


int main()
{
    auto t0 = std::chrono::high_resolution_clock::now();

    AdjacencyList AdjListForMinCut;
    AdjListForMinCut.ReadInputFile("input.txt");
    AdjListForMinCut.GetMinCut();

    auto t1 = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count() << " msec \n";

    return 0;
}

void AdjacencyList::ReadInputFile(const std::string& sInputFile)
{
    std::ifstream ips(sInputFile);

    if(! ips.is_open())
        return;

    std::string sLine;

    while(getline(ips, sLine))
    {
        std::stringstream sEdges(sLine);

        AdjacentVertex AdjVertex;

        sEdges >> AdjVertex.Vertex;

        int EdgeVertex {0};
        while(sEdges >> EdgeVertex)
        {
            AdjVertex.m_AdjVertex.push_back(EdgeVertex);
        }
        m_AdjList.push_back(AdjVertex);
    }

    ips.close();
    return;
}


int AdjacencyList::GetMinCut()
{
    auto nMinCut {INT_MAX};
    auto nCurrentCut {0};

    int numLoops = static_cast<int>( pow( static_cast<float>(m_AdjList.size()), 2) * log(static_cast<float>(m_AdjList.size())) );

    srand(time(NULL));

    for(int i=0; i < numLoops; i++)
    {
        // back up the adjacency list
        auto AdjListCopy = m_AdjList;

        nCurrentCut = GetOneMinCut(AdjListCopy);
        if(nCurrentCut < nMinCut)
            nMinCut = nCurrentCut;

        std::cout << "Min Cut" << nMinCut << " CurrentCut " << nCurrentCut << "\n";
    }

    return nMinCut;
}

int AdjacencyList::GetOneMinCut(std::vector<AdjacentVertex>& AdjList)
{
    while(AdjList.size() > 2)
    {
        // select random edge to fuse
        int nVertex1Idx = rand() % AdjList.size();
        int nVertex1 = AdjList[nVertex1Idx].Vertex;
        int nVertex2 = AdjList[nVertex1Idx].m_AdjVertex[rand() % AdjList[nVertex1Idx].m_AdjVertex.size()];


        // vertex1 is redundant. merge vertex1 list into vertex2
        for( auto It = AdjList[nVertex1Idx].m_AdjVertex.begin(); It != AdjList[nVertex1Idx].m_AdjVertex.end(); ++It)
        {
            // this will become a self loop
            if(*It == nVertex2)
            {
                std::swap(*It, AdjList[nVertex1Idx].m_AdjVertex.back());
                AdjList[nVertex1Idx].m_AdjVertex.pop_back();
                It--;
            }

        }

        int nVertex2Idx = 0;
        for(int i = 0; i < AdjList.size(); ++i)
            if(AdjList[i].Vertex == nVertex2)
            {
                nVertex2Idx = i;
                break;
            }

        for( auto It = AdjList[nVertex2Idx].m_AdjVertex.begin(); It != AdjList[nVertex2Idx].m_AdjVertex.end(); ++It)
        {
            // this will become a self loop
            if(*It == nVertex1)
            {
                std::swap(*It, AdjList[nVertex2Idx].m_AdjVertex.back());
                AdjList[nVertex2Idx].m_AdjVertex.pop_back();
                It--;
            }

        }

        AdjList[nVertex2Idx].m_AdjVertex.insert(AdjList[nVertex2Idx].m_AdjVertex.end(), AdjList[nVertex1Idx].m_AdjVertex.begin(), AdjList[nVertex1Idx].m_AdjVertex.end());

        std::swap(AdjList[nVertex1Idx], AdjList.back());
        AdjList.pop_back();

        // rename all references to vertex1 with vertex2
        for(int i = 0; i < AdjList.size(); ++i)
            std::replace(AdjList[i].m_AdjVertex.begin(), AdjList[i].m_AdjVertex.end(), nVertex1, nVertex2);
    }

    return AdjList[0].m_AdjVertex.size();
}
