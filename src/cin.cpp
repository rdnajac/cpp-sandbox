#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);

int main() {
    FAST_IO;

    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    sort(arr.begin(), arr.end());

    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
