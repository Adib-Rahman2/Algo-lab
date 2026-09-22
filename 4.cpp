#include <iostream>
#include <string>
using namespace std;

int main() {
    string X, Y;

    cout << "Enter first string: ";
    cin >> X;

    cout << "Enter second string: ";
    cin >> Y;

    int m = X.length();
    int n = Y.length();

    // DP table
    int dp[m + 1][n + 1];

    // Initialize DP table
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {

            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            }

            else if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }

            else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // Print LCS length
    cout << "\nLength of LCS: " << dp[m][n] << endl;

    // Reconstruct LCS
    string lcs = "";

    int i = m;
    int j = n;

    while (i > 0 && j > 0) {

        if (X[i - 1] == Y[j - 1]) {
            lcs += X[i - 1];

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

    // Reverse the LCS manually (no algorithm library)
    for (int k = 0; k < lcs.length() / 2; k++) {
        char temp = lcs[k];

        lcs[k] = lcs[lcs.length() - 1 - k];

        lcs[lcs.length() - 1 - k] = temp;
    }

    cout << "LCS: " << lcs << endl;

    return 0;
}