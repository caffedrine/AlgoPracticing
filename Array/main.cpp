#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include "ArrayFunctions.h"

using namespace std;

int main()
{
    int a[4][4] = {
            5, 4, 3, 9,
            2, 0, 7, 6,
            1, 3, 4, 0,
            9, 8, 3, 4
    };

    cout << "Input:\n";
    printMatrix(a);

    cout << "\nOutput:\n";
    make_zeroes(a);
    printMatrix(a);

    return 0;
}
