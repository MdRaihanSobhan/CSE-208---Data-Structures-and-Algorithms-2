#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <climits>

using namespace std;

int digitJump(string S) {
    int n = S.length();
    if (n == 1) return 0;

    vector<bool> visited(n, false);
    unordered_map<char, vector<int>> digit_positions;
    
    for (int i = 0; i < n; ++i) {
        digit_positions[S[i]].push_back(i);
    }

    queue<pair<int, int>> q;  // (index, number of jumps)
    q.push({0, 0});
    visited[0] = true;

    while (!q.empty()) {
        int index = q.front().first;
        int jumps = q.front().second;
        q.pop();

        // Try moving to the next index
        if (index + 1 < n && !visited[index + 1]) {
            if (index + 1 == n - 1) return jumps + 1;
            q.push({index + 1, jumps + 1});
            visited[index + 1] = true;
        }

        // Try moving to the previous index
        if (index - 1 >= 0 && !visited[index - 1]) {
            q.push({index - 1, jumps + 1});
            visited[index - 1] = true;
        }

        // Try moving to other indices with the same digit
        char current_digit = S[index];
        for (int pos : digit_positions[current_digit]) {
            if (!visited[pos]) {
                if (pos == n - 1) return jumps + 1;
                q.push({pos, jumps + 1});
                visited[pos] = true;
            }
        }
        digit_positions[current_digit].clear();  // Clear to prevent redundant checks
    }
    return -1;
}

int main() {
    string S;
    cin >> S;
    cout << digitJump(S) << endl;
    return 0;
}
