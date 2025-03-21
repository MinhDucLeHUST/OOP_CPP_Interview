#include <bits/stdc++.h>
using namespace std;

int N, M, X;
vector<vector<int>> arr;
vector<vector<int>> vtList;
int sizeList = 0;
vector<vector<int>> vtCombination;

void input() {
    cin >> N >> M >> X;
    for (int i = 0; i < N; i++) {
        vector<int> tmp;
        for (int j = 0; j <= M; j++) {
            int x;
            cin >> x;
            tmp.push_back(x);
        }
        arr.push_back(tmp);
    }
}

void output(int minCost) {
    if (minCost == INT_MAX) minCost = -1;
    cout << minCost;
}

vector<vector<int>> combinationHelper(int n, int k, int start) {
    if (k == 0) {
        return {{}};  // Base case: return a vector containing an empty vector
    }

    vector<vector<int>> result;
    for (int i = start; i <= n; i++) {
        vector<vector<int>> subCombinations = combinationHelper(n, k - 1, i + 1);
        for (const auto& subCombination : subCombinations) {
            vector<int> newCombination = subCombination;
            newCombination.insert(newCombination.begin(), i);
            result.push_back(newCombination);
        }
    }
    return result;
}

vector<vector<int>> getCombinations(int n, int k) {
    return combinationHelper(n, k, 1);
}

void sum() {
    for (int i = 0; i < sizeList; i++) {
        vector<int> vtTemp;
        for (int k = 0; k <= M; k++) {
            int temp = 0;
            for (int j = 0; j < int(vtCombination[i].size()); j++) {
                temp += arr[vtCombination[i][j] - 1][k];
                cout << "temp: " << temp << endl;
            }
            vtTemp.push_back(temp);
        }
        vtList.push_back(vtTemp);
    }
    for (auto it : vtList) {
        for (int i = 0; i <= M; i++) {
            cout << it[i] << " ";
        }
        cout << endl;
    }
}

bool passExam(int i) {
    for (int j = 1; j <= M; j++) {
        if (vtList[i][j] < X) return false;
    }
    return true;
}

int main() {
    // input();
    // int minCost = INT_MAX;
    // for (int k = 1; k <= N; k++) {
    //     vector<vector<int>> combinations = getCombinations(N, k);
    //     for (const auto& it : combinations) {
    //         vector<int> sub;
    //         for (int num : it) {
    //             cout << num << endl;
    //             sub.push_back(num);
    //         }
    //         sizeList++;
    //         vtCombination.push_back(sub);
    //     }
    // }
    // for (auto it : vtCombination) {
    //     for (int i = 0; i <= M; i++) {
    //         cout << it[i] << " ";
    //     }
    //     cout << endl;
    // }
    // sum();
    // for (int i = 0; i < sizeList; i++) {
    //     if (passExam(i)) minCost = min(minCost, vtList[i][0]);
    // }
    // output(minCost);

    // input();
    // int minCost = INT_MAX;
    int N = 6;
    for (int k = 1; k <= N; k++) {
        vector<vector<int>> combinations = getCombinations(N, k);
        for (const auto& it : combinations) {
            vector<int> sub;
            for (int num : it) {
                cout << num << endl;
                sub.push_back(num);
            }
            sizeList++;
            vtCombination.push_back(sub);
        }
    }
    for (auto it1 : vtCombination) {
        for (auto it2 : it1) {
            cout << it2 << " ";
        }
        cout << endl;
    }
    // sum();
    // for (int i = 0; i < sizeList; i++) {
    //     if (passExam(i)) minCost = min(minCost, vtList[i][0]);
    // }
    // output(minCost);
}
