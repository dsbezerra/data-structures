internal vector<vector<int>>
TripletSum(vector<int> Array, int Sum)
{
    vector<vector<int>> Result;
    size_t ArraySize = Array.size();
    
    // NOTE(diego): Ensure array is sorted!
    // Linearithmic complexity O(nlogn)
    sort(Array.begin(), Array.end());
    
    // NOTE(diego): Iteration over Array gives us a O(n) time complexity.
    for (size_t NumberIndex = 0; NumberIndex < ArraySize - 3; ++NumberIndex)
    {
        // Isolate first number.
        int Number = Array[NumberIndex];
        
        // NOTE(diego): This approach only works with ascending sorted arrays.
        // This combined with the outer iteration will gives us another O(n) time
        // complexity.
        //
        // Both combined give us a O(n^2) time complexity, so the total complexity 
        // may be O(n^2) since O(nlogn) < O(n^2).
        
        size_t StartIndex = NumberIndex + 1;
        size_t EndIndex = ArraySize - 1;
        
        while (StartIndex < EndIndex)
        {
            int StartNumber = Array[StartIndex];
            int EndNumber = Array[EndIndex];
            
            int TripletSum = Number + StartNumber + EndNumber;
            if (TripletSum == Sum)
            {
                Result.push_back({Number, StartNumber, EndNumber});
                StartIndex++;
                EndIndex--;
            }
            else if (TripletSum > Sum)
            {
                EndIndex--;
            }
            else
            {
                StartIndex++;
            }
        }
    }
    
    return Result;
}


internal b32
TripletsIsValid(vector<vector<int>> Triplets)
{
    b32 Result = false;
    
    for (auto &Triplet : Triplets)
    {
        Result |= Triplet.size() == 3;
    }
    
    return Result;
}

internal void
TestTriplets(vector<int> Array, int Sum)
{
    auto CubicResult = TripletSum(Array, Sum);
    Assert(TripletsIsValid(CubicResult));
}

internal void
PrintTriplet(vector<int> Triplet)
{
    Assert(Triplet.size() == 3);
    
    cout << Triplet[0] << "," << Triplet[1] << "," << Triplet[2] << endl;
}

internal void
PrintTriplets(vector<vector<int>> &Triplets)
{
    Assert(Triplets.size() > 0);
    
    for (auto &Triplet : Triplets)
    {
        PrintTriplet(Triplet);
    }
}

internal void
Triplets(void)
{
    vector<int> Array{1, 2, 3, 4, 5, 6, 7, 8, 9, 15};
    int Sum = 18;
    int IterationCount = 1;
    
#if DS_TEST
    TestTriplets(Array, Sum);
#elif DS_PROFILE
    {
        TIMED_BLOCK("TripletSum", Quadratic);
        for (int Iteration = 0; Iteration < IterationCount; ++Iteration)
            TripletSum(Array, Sum);
    }
#else
    auto Triplets = TripletSum(Array, Sum);
    if (Triplets.size() == 0)
    {
        cout << "No such triplets";
    }
    else
    {
        PrintTriplets(Triplets);
    }
#endif
}