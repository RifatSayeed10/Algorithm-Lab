#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// ---------- Naive Method ----------
pair<int, int> findMinMaxNaive(const vector<int>& arr, int& comparisons) {
    int minVal = INT_MAX, maxVal = INT_MIN;
    for (int num : arr) {
        comparisons++;
        if (num < minVal) minVal = num;
        comparisons++;
        if (num > maxVal) maxVal = num;
    }
    return {minVal, maxVal};
}

// ---------- Divide and Conquer Method ----------
pair<int, int> findMinMaxDC(const vector<int>& arr, int low, int high, int& comparisons) {
    if (low == high) {
        return {arr[low], arr[low]};
    }
    if (high == low + 1) {
        comparisons++;
        if (arr[low] < arr[high])
            return {arr[low], arr[high]};
        else
            return {arr[high], arr[low]};
    }

    int mid = (low + high) / 2;
    auto left = findMinMaxDC(arr, low, mid, comparisons);
    auto right = findMinMaxDC(arr, mid + 1, high, comparisons);

    comparisons++;
    int finalMin = (left.first < right.first) ? left.first : right.first;
    comparisons++;
    int finalMax = (left.second > right.second) ? left.second : right.second;

    return {finalMin, finalMax};
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter " << n << " unsorted integers:\n";
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    // --- Naive Method ---
    int naiveComparisons = 0;
    auto naiveResult = findMinMaxNaive(arr, naiveComparisons);

    // --- Divide and Conquer Method ---
    int dcComparisons = 0;
    auto dcResult = findMinMaxDC(arr, 0, n - 1, dcComparisons);

    // --- Output ---
    cout << "\nMax = " << naiveResult.second << ", Min = " << naiveResult.first << endl;
    cout << "By Native method: " << naiveComparisons << " comparisons\n";
    cout << "By Divide and Conquer: " << dcComparisons << " comparisons\n";

    return 0;
}