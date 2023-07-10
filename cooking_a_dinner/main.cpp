#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template<class T>
bool cook_a_dinner(const vector<T>& cookingTimes, const vector<T>& freshTimes) {
    vector<size_t> dishes;
    dishes.reserve(cookingTimes.size());
    T totalCookingTime = 0;
    for (size_t i = 0; i < cookingTimes.size(); i++) {
        totalCookingTime += cookingTimes[i];
        dishes.emplace_back(i);
    }
    sort(dishes.begin(), dishes.end(), [&](const size_t i, const size_t j) {
        const auto t1 = cookingTimes[i] + freshTimes[i];
        const auto t2 = cookingTimes[j] + freshTimes[j];
        return t1 > t2;
    });
    for (const auto& x: dishes) {
        totalCookingTime -= cookingTimes[x];
        if (freshTimes[x] < totalCookingTime) {
            return false;
        }
    }
    return true;
}

int main() {
    size_t n;
    cin >> n;
    vector<unsigned int> cookingTimes(n);
    vector<unsigned int> freshTimes(n);
    for (int i = 0; i < n; ++i) {
        cin >> cookingTimes[i];
        cin >> freshTimes[i];
    }
    cout << (cook_a_dinner(cookingTimes, freshTimes) ? "Yes" : "No");
}
