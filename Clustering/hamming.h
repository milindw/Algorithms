// use the union find data structure from cluster.h
#include "cluster.h"
#include <unordered_map>
#include <bitset>

constexpr int NumBits {24};

using hamming_bitset = std::bitset<NumBits>;

class HamVertex
{
public:
    HamVertex(int inVertex, hamming_bitset inHamWeight) : Vertex {inVertex}, HamWeight {inHamWeight} {}
    int Vertex;
    hamming_bitset HamWeight;
};

class HammingGraph
{
public:
    HammingGraph() { }
    void ReadInputFile(const string& sInputFile);
    int GetClusterSize(const int Distance);

private:
    std::vector<VertexUnion> m_VertexUnion;
    std::unordered_multimap<int, HamVertex> m_HammingHashMap;

};