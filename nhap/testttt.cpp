#include <bits/stdc++.h>
using namespace std;

int N;
vector<int> strength;

void input() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        strength.push_back(x);
    }
}

void output(vector<int> ans) {
    sort(ans.begin(), ans.end());
    int num = ans.size();
    cout << num << endl;
    for (int i = 0; i < num; i++) {
        cout << ans[i] + 1 << " ";
    }
}

bool do1(int mid, vector<int> vtCopy) {
    auto it = lower_bound(vtCopy.begin(), vtCopy.end(), mid, greater<int>());
    int idx = it - vtCopy.begin();
    // cout << "idx: " << idx << endl;
    int x = vtCopy[idx];
    vtCopy[idx] = 0;
    for (int i = 0; i < N; i++) {
        if (x < vtCopy[i]) return false;
        x += vtCopy[i];
    }
    return true;
}

int main() {
    input();
    vector<int> ans;
    vector<int> vtCopy(strength);
    sort(vtCopy.begin(), vtCopy.end());

    int l = *min_element(strength.begin(), strength.end());
    int r = *max_element(strength.begin(), strength.end());
    int num = r;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (do1(mid, vtCopy)) {
            l = mid + 1;
            num = mid;
        } else
            r = mid - 1;
    }
    // cout << "num: " << num << endl;
    for (int i = 0; i < N; i++) {
        if (strength[i] >= num) ans.push_back(i);
    }
    output(ans);
    return 0;
}