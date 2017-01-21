#include <fstream>
#include <iostream>
#include "MergeSort.h"

template<typename T>
MergeSort<T>::MergeSort()
: m_NumInversions {0}
{ }

template<typename T>
long long MergeSort<T>::GetCountofInversions() const
{
    return m_NumInversions;
}

template<typename T>
void MergeSort<T>::LoadInputFile(const std::string& sInputFile)
{
    std::ifstream ips(sInputFile);
    if(!ips.is_open())
        return;

    T InputElem;

    while(ips >> InputElem)
        m_SortVector.push_back(InputElem);

    ips.close();
    return;
}

template<typename T>
void MergeSort<T>::DoSort()
{
    RecurseAndSort(0, m_SortVector.size()-1);
}

template<typename T>
void MergeSort<T>::RecurseAndSort(int nStartIndex, int nEndIndex)
{
    auto nSizeOfArray = nEndIndex - nStartIndex + 1;

    if(nSizeOfArray <=1)
        return;    

    // size is > 1, so split into left & right

    auto nLeftSize = nSizeOfArray / 2;
    auto nRightSize = nSizeOfArray - nLeftSize;

    // recurse on left side & right side
    RecurseAndSort(nStartIndex, nStartIndex + nLeftSize-1);
    RecurseAndSort(nStartIndex + nLeftSize, nEndIndex);

    // merge step
    auto LeftIt = m_SortVector.begin() + nStartIndex;
    auto LeftEndIt = LeftIt + nLeftSize;

    std::vector<T> LeftSideCopy(LeftIt, LeftEndIt);

    auto RightIt = LeftEndIt;
    auto RightEndIt = RightIt + nRightSize;
    auto MergeIt = LeftIt;

    // reassign LeftIt to the copied vector
    LeftIt = LeftSideCopy.begin();
    LeftEndIt = LeftSideCopy.end();

    while(!(LeftIt == LeftEndIt || RightIt == RightEndIt))
    {
        if(*LeftIt < *RightIt)
        {
            *(MergeIt++) = *(LeftIt++);
        }
        else
        {
            // this is an inversion
            m_NumInversions += (LeftEndIt - LeftIt);
            *(MergeIt++) = *(RightIt++);
        }
    }
    while(LeftIt != LeftEndIt)
    {
        *(MergeIt++) = *(LeftIt++);
    }
    while(RightIt != RightEndIt)
    {
        *(MergeIt++) = *(RightIt++);
    }
}

template<typename T>
void MergeSort<T>::WriteOutputFile(const std::string& sOutputFile) const
{
    std::ofstream ops(sOutputFile);

    if(!ops.is_open())
        return;

    for(const auto& elem : m_SortVector)
        ops << elem << '\n';

    ops.close();
    return;
}


int main()
{
    MergeSort<int> SortClass;
    
    SortClass.LoadInputFile("input.txt");
    SortClass.DoSort();
    std::cout << "Number of Inversions:" << SortClass.GetCountofInversions() << '\n';
    SortClass.WriteOutputFile("output.txt");

    return 0;
}
