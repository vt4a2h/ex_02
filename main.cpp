#include "arrays.h"
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <iterator>

int main()
{
    // Примеры использования одномерного статического массива.
    fixed_arrays::FixedArray<int, 5> arr1 {5, 2, 4, 1, 8};
    std::copy(arr1.begin(), arr1.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    fixed_arrays::FixedArray<int, 5> arr2(arr1);
    std::copy(arr2.begin(), arr2.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    std::transform(arr2.begin(), arr2.end(), arr1.begin(), [](int &i){ return i*2; });
    std::copy(arr1.begin(), arr1.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    // Примеры использования двумероного статического массива.
     fixed_arrays::FixedArray2D<int, 3, 2> arr2d{ {7, 5, 1}, {12, 30, 8} };

     std::for_each(arr2d.begin(), arr2d.end(), [](decltype(arr2d[0]) a){std::sort(a.begin(), a.end());} );

     std::for_each(arr2d.begin(), arr2d.end(),
        [](decltype(arr2d[0]) a){
            std::copy(a.begin(), a.end(), std::ostream_iterator<int>(std::cout, " "));
            std::cout << std::endl;
        }
     );

    return 0;
}

