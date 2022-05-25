#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
#pragma ide diagnostic ignored "misc-no-recursion"
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;


template <typename T>
void printVector(vector<T> vector)
{
    for (auto val : vector)
        std::cout << val << " ";
}

long nThFibImpl(long n, unordered_map<long, long> &fibLookupTable)
{
    if(n <= 2 )
    {
        return 1;
    }

    if( fibLookupTable.find(n) != fibLookupTable.end() )
    {
        return fibLookupTable[n];
    }

    long s1 = nThFibImpl(n - 1, fibLookupTable);
    long s2 = nThFibImpl(n - 2, fibLookupTable);

    fibLookupTable[n] = s1 + s2;
    return  fibLookupTable[n];
}

long nThFibonacci(long n)
{
    unordered_map<long, long> fibLookupTable = {};
    return nThFibImpl(n, fibLookupTable);
}

long long gridTravelerImpl(long m, long n, unordered_map<string, long long> &lookUpTable)
{
    if( m == 0 || n == 0 )
        return 0;

    if( m == 1 && n == 1 )
        return 1;

    string key = to_string(m) + to_string(n);

    if(lookUpTable.find(key) != lookUpTable.end())
        return lookUpTable[key];

    lookUpTable[key] = gridTravelerImpl( m - 1, n, lookUpTable ) + gridTravelerImpl(m, n - 1, lookUpTable);
    return lookUpTable[key];
}

long long gridTraveler(long m, long n)
{
    unordered_map<string, long long> lookUpTable;
    return gridTravelerImpl(m, n, lookUpTable);
}

bool canSumImpl(long number, vector<long> &elements, unordered_map<long, long> &lookupTable)
{
    if(lookupTable.find(number) != lookupTable.end())
        return lookupTable[number];

    for( long e: elements )
    {
        int remainder = number - e;
        if( remainder == 0 )
            return true;
        else if( remainder > 0 )
        {
            lookupTable[number] = canSumImpl(number - e, elements, lookupTable);
            if(lookupTable[number])
                return true;
        }
    }
    return false;
}

bool canSum(long numbers, vector<long> &elements)
{
    unordered_map<long, long> lookUptable;
    return canSumImpl(numbers, elements, lookUptable);
}

bool howSumImpl(long targetSum, vector<long> &elements, vector<long> &output, unordered_map<long, long> &lookupTable)
{
    if(lookupTable.find(targetSum) != lookupTable.end())
        return lookupTable[targetSum];

    for( long e: elements )
    {
        int remainder = targetSum - e;
        if( remainder == 0 )
        {
            output.push_back(e);
            return true;
        }
        else if( remainder > 0 )
        {
            output.push_back(e);
            lookupTable[remainder] = howSumImpl(targetSum - e, elements, output, lookupTable);
            if( lookupTable[remainder] )
            {
                return true;
            }
        }
    }

    // Remove last element as tree end node result was != 0
    if( !output.empty() )
        output.pop_back();
    return false;
}

vector<long> howSum(long targetSum, vector<long> &elements)
{
    unordered_map<long, long> lookupTable;
    vector<long> output;
    howSumImpl(targetSum, elements, output, lookupTable);
    return output;
}

void bestSumImpl(long targetSum, vector<long> &elements, vector<long> &tmp, vector<long> &shortest, unordered_map<long, long> &lookupTable)
{
//    if(lookupTable.find(targetSum) != lookupTable.end())
//        return lookupTable[targetSum];

    for( long e: elements )
    {
        int remainder = targetSum - e;
        if( remainder == 0 )
        {
            // We found a path. Is this shorter than the previous one?
            if( (shortest.empty()) || (shortest.size() > tmp.size())  )
            {
                shortest = tmp;
                shortest.push_back(e);
            }
        }
        else if( remainder > 0 )
        {
            tmp.push_back(e);
//            lookupTable[remainder] = bestSumImpl(targetSum - e, elements, tmp, shortest, lookupTable);
            bestSumImpl(targetSum - e, elements, tmp, shortest, lookupTable);
        }
    }

    // Remove last element as tree end node result was != 0
    if( !tmp.empty() )
        tmp.pop_back();
}

vector<long> bestSum(long targetSum, vector<long> &elements)
{
    unordered_map<long, long> lookupTable;
    vector<long> tmp;
    vector<long> shortest;
    bestSumImpl(targetSum, elements, tmp, shortest, lookupTable);
    return shortest;
}

vector<long> bestSumImplPerf(long targetSum, vector<long> &elements, unordered_map<long, vector<long>> &lookupTable)
{
    if(lookupTable.find(targetSum) != lookupTable.end())
        return lookupTable[targetSum];

    vector<long> shortestSum;

    for( long e: elements )
    {
        int remainder = targetSum - e;
        if( remainder == 0 )
        {
            return {e};
        }
        else if( remainder > 0 )
        {
            lookupTable[targetSum] = bestSumImplPerf(targetSum - e, elements, lookupTable);
            if( !lookupTable[targetSum].empty() )
            {
                lookupTable[targetSum].push_back(e);
            }
        }

        if( (!lookupTable[targetSum].empty()) && (shortestSum.empty() || shortestSum.size() > lookupTable[targetSum].size()) )
        {
            shortestSum = lookupTable[targetSum];
        }
    }

    return shortestSum;
}

vector<long> bestSumPerf(long targetSum, vector<long> &elements)
{
    unordered_map<long, vector<long>> lookupTable;
    return bestSumImplPerf(targetSum, elements, lookupTable);
}

int main()
{
    cout << "6th fibonacci number: " << nThFibonacci(6) << endl;
    cout << "7th fibonacci number: " << nThFibonacci(7) << endl;
    cout << "8th fibonacci number: " << nThFibonacci(8) << endl;
    cout << "50th fibonacci number: " << nThFibonacci(50) << endl;
    cout << "100th fibonacci number: " << nThFibonacci(100) << endl;

    cout << "\nGrid traveler max paths for 1x1: " << gridTraveler(1, 1) << endl;
    cout << "Grid traveler max paths for 2x2: " << gridTraveler(2, 2) << endl;
    cout << "Grid traveler max paths for 2x3: " << gridTraveler(2, 3) << endl;
    cout << "Grid traveler max paths for 3x2: " << gridTraveler(3, 2) << endl;
    cout << "Grid traveler max paths for 3x3: " << gridTraveler(3, 3) << endl;
    cout << "Grid traveler max paths for 4x4: " << gridTraveler(4, 4) << endl;
    cout << "Grid traveler max paths for 5x5: " << gridTraveler(5, 5) << endl;
    cout << "Grid traveler max paths for 6x6: " << gridTraveler(6, 6) << endl;
    cout << "Grid traveler max paths for 5x4: " << gridTraveler(5, 4) << endl;
    cout << "Grid traveler max paths for 8x8: " << gridTraveler(8, 8) << endl;
    cout << "Grid traveler max paths for 18x18: " << gridTraveler(18, 18) << endl;

    vector<long> canSumVector = {3, 4};
    cout << "\nInput vector for possible sum:  "; printVector(canSumVector); cout <<endl;
    cout << "canSum(7) = " << (canSum(7, canSumVector) ? "true" : "false") << endl;
    cout << "canSum(5) = " << (canSum(5, canSumVector) ? "true" : "false") << endl;
    cout << "canSum(55) = " << (canSum(55, canSumVector) ? "true" : "false") << endl;
    cout << "canSum(10) = " << (canSum(10, canSumVector) ? "true" : "false") << endl;
    cout << "canSum(100) = " << (canSum(100, canSumVector) ? "true" : "false") << endl;
    cout << "canSum(999) = " << (canSum(999, canSumVector) ? "true" : "false") << endl;
    cout << "canSum(12552) = " << (canSum(12552, canSumVector) ? "true" : "false") << endl;

    vector<long> howSumVector = {3, 4, 5};
    cout << "\nInput vector for possible sum:  "; printVector(howSumVector); cout <<endl;
    cout << "howSum(0)   = "; printVector(howSum(0, howSumVector)); cout << endl;
    cout << "howSum(1)   = "; printVector(howSum(1, howSumVector)); cout << endl;
    cout << "howSum(2)   = "; printVector(howSum(2, howSumVector)); cout << endl;
    cout << "howSum(3)   = "; printVector(howSum(3, howSumVector)); cout << endl;
    cout << "howSum(4)   = "; printVector(howSum(4, howSumVector)); cout << endl;
    cout << "howSum(5)   = "; printVector(howSum(5, howSumVector)  ); cout << endl;
    cout << "howSum(6)   = "; printVector(howSum(6, howSumVector)  ); cout << endl;
    cout << "howSum(7)   = "; printVector(howSum(7, howSumVector)); cout << endl;
    cout << "howSum(8)   = "; printVector(howSum(8, howSumVector)); cout << endl;
    cout << "howSum(9)   = "; printVector(howSum(9, howSumVector)); cout << endl;
    cout << "howSum(10)  = "; printVector(howSum(10, howSumVector) ); cout << endl;
    cout << "howSum(55)  = "; printVector(howSum(55, howSumVector) ); cout << endl;
    cout << "howSum(100) = "; printVector(howSum(100, howSumVector)); cout << endl;
    //cout << "howSum(999) = "; printVector(howSum(999, howSumVector)); cout << endl;

    vector<long> bestSumVector = {3, 4, 5, 25, 50, 100};
    cout << "\nShortest possible sum:  "; printVector(bestSumVector); cout <<endl;
    cout << "bestSum(0)   = "; printVector(bestSumPerf(0, bestSumVector)); cout << endl;
    cout << "bestSum(1)   = "; printVector(bestSumPerf(1, bestSumVector)); cout << endl;
    cout << "bestSum(2)   = "; printVector(bestSumPerf(2, bestSumVector)); cout << endl;
    cout << "bestSum(3)   = "; printVector(bestSumPerf(3, bestSumVector)); cout << endl;
    cout << "bestSum(4)   = "; printVector(bestSumPerf(4, bestSumVector)); cout << endl;
    cout << "bestSum(5)   = "; printVector(bestSumPerf(5, bestSumVector)  ); cout << endl;
    cout << "bestSum(6)   = "; printVector(bestSumPerf(6, bestSumVector)  ); cout << endl;
    cout << "bestSum(7)   = "; printVector(bestSumPerf(7, bestSumVector)); cout << endl;
    cout << "bestSum(8)   = "; printVector(bestSumPerf(8, bestSumVector)); cout << endl;
    cout << "bestSum(9)   = "; printVector(bestSumPerf(9, bestSumVector)); cout << endl;
    cout << "bestSum(10)  = "; printVector(bestSumPerf(10, bestSumVector) ); cout << endl;
    cout << "bestSum(55)  = "; printVector(bestSumPerf(55, bestSumVector) ); cout << endl;
    cout << "bestSum(145) = "; printVector(bestSumPerf(100, bestSumVector)); cout << endl;
    cout << "bestSum(999) = "; printVector(bestSumPerf(999, bestSumVector)); cout << endl;

    return 0;
}

#pragma clang diagnostic pop