#ifndef _MINCUT_H
#define _MINCUT_H

#include <vector>
#include <string>

class AdjacentVertex
{
public:
    int Vertex;
    std::vector<int> m_AdjVertex;
};

class AdjacencyList
{
public:
    AdjacencyList() { }
    void ReadInputFile(const std::string& sInputFile);
    int GetMinCut();

private:
    std::vector<AdjacentVertex> m_AdjList;

    int GetOneMinCut(std::vector<AdjacentVertex>& AdjList);
};

#endif
