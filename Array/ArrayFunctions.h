
#ifndef _ARRAYFUNCTIONS_H_
#define _ARRAYFUNCTIONS_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <hash_set>

using namespace std;

/*
 *
Task 1
C++
Task description

This is a demo task.

Write a function:

    int solution(vector<int> &A);

that, given an array A of N integers, returns the smallest positive integer (greater than 0) that does not occur in A.

For example, given A = [1, 3, 6, 4, 1, 2], the function should return 5.

Given A = [1, 2, 3], the function should return 4.

Given A = [−1, −3], the function should return 1.

Write an efficient algorithm for the following assumptions:

        N is an integer within the range [1..100,000];
        each element of array A is an integer within the range [−1,000,000..1,000,000].
 */
int solution(vector<int> &A)
{
    // Sort array and remove duplicates
    std::sort(A.begin(), A.end());
    A.erase( unique( A.begin(), A.end() ), A.end() );

    // Remove negative numbers
    vector<int> vec;
    vec.reserve(A.size());
    for(const auto& el : A)
    {
        if(el>0)
            vec.push_back(el);
    }

    for(int i=0; i<vec.size(); ++i)
    {
        if( vec[i] != i + 1 )
            return i + 1;
    }
    return vec.back()+1;
}

/**
 * Given an array of integers and a value, determine if there are any two integers in the array whose sum is
 * equal to the given value. Return true if the sum exists and return false if it does not.
 * Consider this array and the target sums:
 *
 */
bool find_sum_of_two(vector<int>& A, int val)
{
//    for( int i = 0; i < A.size() - 1; i++ )
//        for(int j = i + 1; j < A.size(); j++)
//        {
//            if( A[i] + A[j] == val )
//                return true;
//        }
//    return false;

    unordered_set<int> found_values;
    for (int& a : A)
    {
        if (found_values.find(val - a) != found_values.end()) // 10 = 6 + 4
        {
            return true;
        }
        found_values.insert(a);
    }
    return false;
}

/**
 * https://www.educative.io/m/make-columns-and-rows-zero
 * Given a two-dimensional array, if any element within is zero, make its whole row and column zero. For example, consider the matrix below.
 * There are two zeros in the input matrix at position (1,1) and (2,3). The output of this should be a matrix in which the first and second
 * rows become zero and first and third columns become zeros. Below is the expected output matrix.
 */
void printMatrix(int a[4][4])
{
    for( int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

void make_zeroes(int a[4][4])
{
    vector<int> zerosRows;
    vector<int> zerosCols;

    // Find zeros
    for( int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if( a[i][j] == 0 )
            {
                zerosRows.push_back(i);
                zerosCols.push_back(j);
            }

    // Make rows zero
    for(int zerosRow : zerosRows)
        for( int i = 0; i < 4; i++ )
            a[zerosRow][i] = 0;

    // Make columns zero
    for(int zerosCol : zerosCols)
        for( int i = 0; i < 4; i++ )
            a[i][zerosCol] = 0;
}

#endif // _ARRAYFUNCTIONS_H_