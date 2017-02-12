#include "hamming.h"

#include <iostream>
#include <sstream>
#include <fstream>

using std::cout;

// *****
// This is copied from cluster.cpp. Should be moved to its own cpp file

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

// *****

void HammingGraph::ReadInputFile(const string& sInputFile)
{
    std::ifstream ips(sInputFile);

    if(! ips.is_open())
        return;

    string sLine;

    getline(ips, sLine);

    auto NumVertex {0};

    std::stringstream ssFLine(sLine);

    ssFLine >> NumVertex;

    m_VertexUnion.reserve(NumVertex);

    auto vertex_num {0};

    while(getline(ips, sLine))
    {
        string sTrimmed;

        for(auto it = sLine.begin(); it != sLine.end(); ++it)
        {
            if(*it != ' ')
                sTrimmed += *it;
        }

        hamming_bitset hamming_bits(sTrimmed);

        m_HammingHashMap.insert(std::make_pair<int, HamVertex>(hamming_bits.count(), HamVertex{vertex_num, hamming_bits}));
        m_VertexUnion.push_back( VertexUnion {vertex_num} );
        vertex_num++;
    }
    
    ips.close();
    cout << "File loaded" << "\n";
}

int HammingGraph::GetClusterSize(const int Distance)
{
    int i {0};


    for(auto ham_It = m_HammingHashMap.cbegin(); ham_It != m_HammingHashMap.cend(); ++ham_It)
    {
        auto ham_count = ham_It->first;
        HamVertex ham_vertex = ham_It->second;

        cout << i++ << "\n";

        // find vertices that have ham_count close to this one, based on distance
        for(auto find_count : {ham_count, ham_count-1, ham_count-2, ham_count+1, ham_count+2})// = ham_count -Distance; find_count <= ham_count+Distance; find_count++)
        {
            if(find_count < 0 || find_count > NumBits)
                continue;

            auto range = m_HammingHashMap.equal_range(find_count);
            for(auto hamvertex_It = range.first; hamvertex_It != range.second; ++hamvertex_It)
            {
                if( (ham_vertex.HamWeight ^ hamvertex_It->second.HamWeight).count() < Distance)
                {
                    // merge these vertices
                    auto vertex_1 = ham_vertex.Vertex;
                    auto vertex_2 = hamvertex_It->second.Vertex;

                    auto LeaderVertex1 = m_VertexUnion[vertex_1].Leader;
                    auto LeaderVertex2 = m_VertexUnion[vertex_2].Leader;

                    if(LeaderVertex1 == LeaderVertex2)
                        continue;

                    // do the merge now
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
                }
            }
        }
    }

    auto num_clusters {0};

    for(auto vunion : m_VertexUnion)
    {
        if(vunion.Size != 0)
            num_clusters++;
    }
    cout << "Number of clusters " << num_clusters << "\n";
}

int main()
{
    HammingGraph hg;
    hg.ReadInputFile("haminput.txt");
    hg.GetClusterSize(3);

    return 0;
}
