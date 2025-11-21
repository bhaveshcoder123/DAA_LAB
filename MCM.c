#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int main() {
    printf("Please enter the size of the array : ");
    int n;
    scanf("%d" , &n);

    int* arr = (int*)malloc(n*sizeof(int));
    printf("Please enter the elements of the array : ");
    for(int i = 0 ; i<n ; i++) scanf("%d" , &arr[i]);

    int** dp = (int**)malloc(n*sizeof(int*));
    for(int i = 0 ; i<n ; i++) {
        dp[i] = (int*)malloc(n*sizeof(int));
    }

    for(int i = n-1 ; i>0 ; i--) {
        for(int j = 0 ; j<n ; j++) {
            if(i>=j) dp[i][j] = 0;
            else {
                int mini = INT_MAX;
                for(int k = i ; k<j ; k++) {
                    int left = dp[i][k];
                    int right = dp[k+1][j];
                    if(mini > left + right + arr[i-1]*arr[j]*arr[k]) {
                        mini = left + right + arr[i-1]*arr[j]*arr[k];
                    }
                }
                dp[i][j] = mini;
            }
        }
    }

    int minCost = dp[1][n-1];
    printf("The minimum cost of multiplying the matrices is : %d\n" , minCost);
}
