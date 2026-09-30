#include <stdio.h>
#include <string.h>
void findAndPrintLCS(char *X, char *Y) {
    int m = strlen(X);
    int n = strlen(Y);
    int dp[m + 1][n + 1];
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
        }
    }

    int lcsLength = dp[m][n];
    printf("Length of LCS: %d\n", lcsLength);
    char lcsString[lcsLength + 1];
    lcsString[lcsLength] = '\0'; 
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcsString[lcsLength - 1] = X[i - 1];
            i--;
            j--;
            lcsLength--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    printf("LCS String: %s\n", lcsString);
}
int main() {
    char X[] = "ABCBDAB";
    char Y[] = "BDCABA";
    printf("Sequence X: %s\n", X);
    printf("Sequence Y: %s\n", Y);
    findAndPrintLCS(X, Y);
    return 0;
}
