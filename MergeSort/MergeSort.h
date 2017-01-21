#ifndef _MERGESORT_H
#define _MERGESORT_H

#include<vector>
#include<string>

template<typename T>
class MergeSort
{
public:
    MergeSort();
    long long GetCountofInversions() const;
    void LoadInputFile(const std::string& sInputFile);
    void DoSort();
    void WriteOutputFile(const std::string& sOutputFile) const;

private:
    std::vector<T> m_SortVector;
    long long m_NumInversions;

    void RecurseAndSort(int nStartIndex, int nEndIndex);
};

#endif
