#ifndef _QUICKSORT_H
#define _QUICKSORT_H

#include<vector>
#include<string>

enum class PivotMethod { First, Last, Median};

template<typename T>
class QuickSort
{
public:
    QuickSort();
    long long GetCountofComparisons() const;
    void LoadInputFile(const std::string& sInputFile);
    void DoSort();
    void WriteOutputFile(const std::string& sOutputFile) const;
    void SetPivotMethod(PivotMethod method) { m_PivotMethod = method; }

private:
    std::vector<T> m_SortVector;
    long long m_NumComparisons;
    PivotMethod m_PivotMethod;

    void RecurseAndSort(int nStartIndex, int nEndIndex);
};

#endif
