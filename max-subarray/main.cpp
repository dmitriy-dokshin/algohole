#include <iostream>
#include <limits>
#include <vector>

using namespace std;

template<class T>
void max_subarray_divide_and_conquer(const vector<T>& v, const size_t begin, const size_t end, T& result) { // NOLINT(misc-no-recursion)
    if (end - begin == 0) {
        return;
    }
    if (end - begin == 1) {
        result = max(result, v[begin]);
        return;
    }

    const size_t mid = begin + (end - begin)/2;

    T leftSum = 0;
    T maxLeftSum = numeric_limits<T>::min();
    for (size_t i = 0; mid - i > begin; i++) {
        leftSum += v[mid - i - 1];
        maxLeftSum = max(maxLeftSum, leftSum);
    }

    T rightSum = 0;
    T maxRightSum = numeric_limits<T>::min();
    for (size_t i = mid; i < end; i++) {
        rightSum += v[i];
        maxRightSum = max(maxRightSum, rightSum);
    }

    result = max(result, maxLeftSum + maxRightSum);

    max_subarray_divide_and_conquer(v, begin, mid, result);
    max_subarray_divide_and_conquer(v, mid, end, result);
}

template<class T>
T max_subarray_greedy(const vector<T>& v) {
    T maxSum = numeric_limits<T>::min();
    T sum = 0;
    for (size_t i = 0; i < v.size(); i++) {
        sum = max(sum + v[i], v[i]);
        maxSum = max(maxSum, sum);
    }
    return maxSum;
}

int main() {
    vector<vector<int>> input{
            {-2, 1, -3, 4, -1, 2, 1, -5, 4},
            {1},
            {5,  4, -1, 7, 8}
    };

    for (const auto& v: input) {
        int maxSum = numeric_limits<int>::min();
        max_subarray_divide_and_conquer(v, 0, v.size(), maxSum);
        cerr << maxSum << "\t" << max_subarray_greedy(v) << endl;
    }
}
