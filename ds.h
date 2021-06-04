/* date = June 3rd 2021 7:32 pm */

#include <iostream>
#include <chrono>
#include <vector>
#include <unordered_set>
#include <algorithm>

#include <windows.h>
#include "ds_types.h"

using namespace std;

enum time_complexity
{
    None,
    Constant,    // O(1)
    Linear,      // O(n)
    Quadratic,   // O(n^2)
    Cubic,       // O(n^3) 
    Logarithmic, // O(logn)
    Quasilienar, // O(nlogn)
    Exponential, // 2^polyn
    Factorial,   // O(n!)
    Polynomial,  // 2^(O(logn))
};

#define COMPLEXITY_CASE(TYPE,STRING) case TYPE: Result = ##STRING; break

internal string
TimeComplexityString(time_complexity Complexity)
{
    string Result;
    
    switch (Complexity)
    {
        COMPLEXITY_CASE(None,         "");
        COMPLEXITY_CASE(Constant,     "O(1)");
        COMPLEXITY_CASE(Linear,       "O(n)");
        COMPLEXITY_CASE(Quadratic,    "O(n^2)");
        COMPLEXITY_CASE(Cubic,        "O(n^3)");
        COMPLEXITY_CASE(Quasilienar,  "O(nlogn)");
        COMPLEXITY_CASE(Logarithmic,  "O(logn)");
        COMPLEXITY_CASE(Exponential,  "2^polyn");
        COMPLEXITY_CASE(Factorial,    "O(n!)");
        COMPLEXITY_CASE(Polynomial,   "2^(O(logn))");
        InvalidDefaultCase;
    }
    
    return Result;
}

// NOTE(diego): Windows specific code.
global_variable u64 GlobalPerfCountFrequencyResolution;

internal void
InitTimeStuff()
{
    LARGE_INTEGER Result;
    QueryPerformanceFrequency(&Result);
    GlobalPerfCountFrequencyResolution= Result.QuadPart;
}

internal u64
GetWallClock()
{
    LARGE_INTEGER Result;
    QueryPerformanceCounter(&Result);
    
    return Result.QuadPart;
}

internal inline real32
GetSecondsElapsed(LARGE_INTEGER Start, LARGE_INTEGER End)
{
    real32 Result = ((real32) (End.QuadPart - Start.QuadPart) /
                     (real32) GlobalPerfCountFrequencyResolution);
    
    return Result;
}

internal inline real32
SecondsElapsed(u64 LastCounter)
{
    real32 Result;
    
    LARGE_INTEGER CurrentCounter;
    QueryPerformanceCounter(&CurrentCounter);
    
    LARGE_INTEGER Start;
    Start.QuadPart = LastCounter;
    
    Result = GetSecondsElapsed(Start, CurrentCounter);
    
    return Result;
}

#define TIMED_BLOCK(NAME, COMPLEXITY) timed_block TimedBlock##Name(##NAME, ##COMPLEXITY)
typedef chrono::high_resolution_clock::time_point time_point;
struct timed_block
{
    string Name;
    u64 Start;
    time_complexity Complexity;
    
    timed_block(string InitName, time_complexity InitComplexity)
    {
        Name = InitName;
        Complexity = InitComplexity;
        Start = GetWallClock();
    }
    
    ~timed_block()
    {
        r32 Elapsed = SecondsElapsed(Start) * 1000.f;
        
        string ComplexityString = TimeComplexityString(Complexity);
        cout << Name << " [" << ComplexityString << "] - took " << Elapsed << "ms" << endl;
    }
};

// NOTE(diego): Used to test if routines are correct 
#define DS_TEST 0
// NOTE(diego): Used to profile routines execution time
#define DS_PROFILE 1