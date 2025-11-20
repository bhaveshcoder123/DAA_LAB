#include<stdio.h>
#include<stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int findLCSLength(char* str1, char* str2, int n1, int n2) {

    int** dp = (int**)malloc((n1 + 1) * sizeof(int*));
    for (int i = 0; i <= n1; i++) {
        dp[i] = (int*)malloc((n2 + 1) * sizeof(int));
    }

    for (int i = 0; i <= n1; i++) {
        for (int j = 0; j <= n2; j++) {  
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i <= n1; i++) {
        for (int j = 1; j <= n2; j++) {
            if (str1[i - 1] == str2[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    return dp[n1][n2];
}

char* findLCS(char* str1, char* str2, int n1, int n2) {

    int** dp = (int**)malloc((n1 + 1) * sizeof(int*));
    char** dir = (char**)malloc((n1 + 1) * sizeof(char*));

    for (int i = 0; i <= n1; i++) {
        dp[i] = (int*)malloc((n2 + 1) * sizeof(int));
        dir[i] = (char*)malloc((n2 + 1) * sizeof(char));
    }

    for (int i = 0; i <= n1; i++) {
        for (int j = 0; j <= n2; j++) {  
            dp[i][j] = 0;
            dir[i][j] = 'p';
        }
    }

    for (int i = 1; i <= n1; i++) {
        for (int j = 1; j <= n2; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
                dir[i][j] = 'd';
            } else if (dp[i - 1][j] > dp[i][j - 1]) {
                dp[i][j] = dp[i - 1][j];
                dir[i][j] = 'u';
            } else {
                dp[i][j] = dp[i][j - 1];
                dir[i][j] = 'l';
            }
        }
    }

    char* lcs = (char*)malloc((max(n1, n2) + 1) * sizeof(char));
    int k = 0;

    int i = n1, j = n2;

    while (i > 0 && j > 0) {
        if (dir[i][j] == 'd') {
            lcs[k++] = str1[i - 1];
            i--;
            j--;
        } else if (dir[i][j] == 'l') {
            j--;
        } else {
            i--;
        }
    }

    lcs[k] = '\0';

    int start = 0, end = k - 1;
    while (start < end) {
        char temp = lcs[start];
        lcs[start] = lcs[end];
        lcs[end] = temp;
        start++;
        end--;
    }

    return lcs;
}

int main() {
    int n1, n2;

    printf("Enter length of first string: ");
    scanf("%d", &n1);

    char* str1 = (char*)malloc((n1 + 1) * sizeof(char));
    printf("Enter first string: ");
    getchar();
    scanf("%[^\n]", str1);

    printf("Enter length of second string: ");
    scanf("%d", &n2);

    char* str2 = (char*)malloc((n2 + 1) * sizeof(char));
    printf("Enter second string: ");
    getchar();
    scanf("%[^\n]", str2);

    int length = findLCSLength(str1, str2, n1, n2);
    char* lcs = findLCS(str1, str2, n1, n2);

    printf("\nLength of LCS: %d\n", length);
    printf("LCS: %s\n", lcs);

    return 0;
}
