#include <vector>
#include <unordered_set>

internal vector<int>
PairSumQuadratic(vector<int> Array, int Sum)
{
    vector<int> Result;
    
    for (int TestNumberIndex = 0; TestNumberIndex < Array.size(); ++TestNumberIndex)
    {
        int TestNumber = Array[TestNumberIndex];
        
        for (int NumberIndex = 0; NumberIndex < Array.size(); ++NumberIndex)
        {
            int Number = Array[NumberIndex];
            if (TestNumber + Number == Sum)
            {
                Result.push_back(TestNumber);
                Result.push_back(Number);
                break;
            }
        }
        
        if (Result.size() == 2)
        {
            break;
        }
    }
    
    return Result;
}


internal vector<int>
PairSumLinear(vector<int> Array, int Sum)
{
    unordered_set<int> Set;
    vector<int> Result;
    
    for (int NumberIndex = 0; NumberIndex < Array.size(); ++NumberIndex)
    {
        int Number = Array[NumberIndex];
        int Diff = Sum - Number;
        
        // NOTE(diego): O(1) lookup
        if (Set.find(Diff) != Set.end())
        {
            Result.push_back(Diff);
            Result.push_back(Number);
            break;
        }
        
        Set.insert(Number);
    }
    
    return Result;
}

internal void
TestPairs(vector<int> Array, int Sum) {
    auto LinearResult = PairSumLinear(Array, Sum);
    Assert(LinearResult.size() == 2);
    
    auto QuadraticResult = PairSumQuadratic(Array, Sum);
    Assert(QuadraticResult.size() == 2);
}

internal void
Pairs(void)
{
    vector<int> Array{10, 5, 2, 3, -6, 9, 11};
    int Sum = 4;
    int IterationCount = 1;
    
#if DS_TEST
    TestPairs(Array, Sum);
#elif DS_PROFILE
    {
        TIMED_BLOCK("PairSumQuadratic", Quadratic);
        for (int Iteration = 0; Iteration < IterationCount; ++Iteration)
            PairSumQuadratic(Array, Sum);
    }
    {
        TIMED_BLOCK("PairSumLinear", Linear);
        for (int Iteration = 0; Iteration < IterationCount; ++Iteration)
            PairSumLinear(Array, Sum);
    }
    
#else
    auto Pair = PairSumLinear(Array, Sum);
    if (Pair.size() == 0)
    {
        cout << "No such pair";
    } 
    else
    {
        cout << Pair[0] << "," << Pair[1] << endl; 
    }
#endif
}
