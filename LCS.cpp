
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

string cleanword(string word) {
    string result = "";

    for (int i = 0; i < word.length(); i++) {
        if (isalpha((unsigned char)word[i])) {
            result += tolower((unsigned char)word[i]);
        }
    }

    return result;
}

int main() {
    string file1, file2;

    cout << "Enter first file name: ";
    cin >> file1;

    cout << "Enter second file name: ";
    cin >> file2;

    ifstream f1(file1);
    ifstream f2(file2);

    if (!f1.is_open()) {
        cout << "The file is not found or can't be opened: " << file1 << endl;
        return 1;
    }

    if (!f2.is_open()) {
        cout << "The file is not found or can't be opened: " << file2 << endl;
        return 1;
    }

    vector<string> words1;
    vector<string> words2;

    string word;

    while (f1 >> word) {
        word = cleanword(word);

        if (word != "")
            words1.push_back(word);
    }

    while (f2 >> word) {
        word = cleanword(word);

        if (word != "")
            words2.push_back(word);
    }

    int m = words1.size();
    int n = words2.size();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (words1[i - 1] == words2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
        }
    }

    vector<string> lcs;

    int i = m;
    int j = n;

    while (i > 0 && j > 0) {
        if (words1[i - 1] == words2[j - 1]) {
            lcs.push_back(words1[i - 1]);
            i--;
            j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        }
        else {
            j--;
        }
    }

    cout << "Total words in File 1: " << m << endl;
    cout << "Total words in File 2: " << n << endl;

    cout << "Length of LCS: " << lcs.size() << endl;

    cout << "LCS: ";

    for (int k = lcs.size() - 1; k >= 0; k--) {
        cout << lcs[k] << " ";
    }

    cout << endl;

    return 0;
}

