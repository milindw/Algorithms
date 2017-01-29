#include<unordered_map>

using std::unordered_map;

class NumWeight
{
public:
    NumWeight(int inNum=0, int inWeight=0) : Num {inNum}, Weight {inWeight} {}

    int Num;
    int Weight;
};

class NumWeightHash
{
public:
    size_t operator()(const NumWeight& nw) const
    {
        return std::hash<int>()(nw.Num) ^ std::hash<int>()(nw.Weight);
    }
};

class NumWeightEqual
{
public:
    bool operator()(const NumWeight& lhs, const NumWeight& rhs) const
    {
        return lhs.Num == rhs.Num && lhs.Weight == rhs.Weight;
    }
};

/*
int main()
{
    unordered_map<NumWeight, int, NumWeightHash, NumWeightEqual> mymap(100);

//    NumWeight a{2,2};

    mymap.insert( std::make_pair<NumWeight, int>(NumWeight{2,2},30) );
    mymap.insert( std::make_pair<NumWeight, int>(NumWeight(2,1),50) );

    cout << mymap[NumWeight{2,12}] << std::endl;

    return 0;
}
*/