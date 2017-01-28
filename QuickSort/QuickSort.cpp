#include <fstream>
#include <iostream>
#include <utility>
#include <algorithm>
#include "QuickSort.h"

template<typename T>
QuickSort<T>::QuickSort()
: m_NumComparisons {0}
{ }

template<typename T>
long long QuickSort<T>::GetCountofComparisons() const
{
    return m_NumComparisons;
}

template<typename T>
void QuickSort<T>::LoadInputFile(const std::string& sInputFile)
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
void QuickSort<T>::DoSort()
{
    RecurseAndSort(0, m_SortVector.size()-1);
}

template<typename T>
void QuickSort<T>::RecurseAndSort(int nStartIndex, int nEndIndex)
{
    auto nSizeOfArray = nEndIndex - nStartIndex + 1;

    if(nSizeOfArray <= 1)
        return;

    auto StartIt = m_SortVector.begin() + nStartIndex;
    auto TraversalIt = StartIt + 1;
    auto EndIt = StartIt + nSizeOfArray;

    // choose the pivot
    switch(m_PivotMethod)
    {
    case PivotMethod::First:
        break;
    case PivotMethod::Last:
    {
        std::iter_swap(StartIt, EndIt-1);
        break;
    }
    case PivotMethod::Median:
    {
        if(nSizeOfArray > 2)
        {
            auto MiddleIt = StartIt + ((nSizeOfArray-1) / 2);
            if(*StartIt < *MiddleIt)
            {
                if(*StartIt >= *(EndIt-1))
                    break;
                else if(*MiddleIt < *(EndIt-1))
                {
                    std::iter_swap(StartIt, MiddleIt);
                    break;
                }
            }
            else
            {
                if(*StartIt < *(EndIt-1))
                    break;
                else if(*MiddleIt >= *(EndIt-1))
                {
                    std::iter_swap(StartIt, MiddleIt);
                    break;
                }
            }
            std::iter_swap(StartIt, EndIt-1);
        }
        break;
    }
    }

    T Pivot = *StartIt;

    auto SeparatorIt = TraversalIt;

    for(; TraversalIt != EndIt; ++TraversalIt)
    {
        if(*TraversalIt < Pivot)
        {
            if(SeparatorIt < TraversalIt)
            {
                T TempSwap = *SeparatorIt;
                *SeparatorIt = *TraversalIt;
                *TraversalIt = TempSwap;
            }
            ++SeparatorIt;
        }
    }

    // increment comparison count
    m_NumComparisons += (nSizeOfArray -1);

    if(SeparatorIt != (StartIt + 1))
    {
        *StartIt = *(SeparatorIt-1);
        *(SeparatorIt-1) = Pivot;

        RecurseAndSort(nStartIndex, SeparatorIt - m_SortVector.begin() - 2);
    }

    if(SeparatorIt < EndIt)
        RecurseAndSort(SeparatorIt - m_SortVector.begin(), nEndIndex);
}

template<typename T>
void QuickSort<T>::WriteOutputFile(const std::string& sOutputFile) const
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
    QuickSort<int> SortClass;
    
    SortClass.LoadInputFile("input.txt");
    SortClass.SetPivotMethod(PivotMethod::Median);
    SortClass.DoSort();
    std::cout << "Number of Comparisons:" << SortClass.GetCountofComparisons() << '\n';
    SortClass.WriteOutputFile("output.txt");

    return 0;
}
