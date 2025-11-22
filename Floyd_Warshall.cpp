#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    void floydWarshall(vector<vector<int>> &dist) {
        int n = dist.size();
        int INF = 100000000;
        for(int k = 0 ; k<n ; k++) {
            for(int i = 0 ; i<n ; i++) {
                for(int j = 0 ; j<n ; j++) {
                    if(dist[i][k] < INF && dist[k][j] < INF) {
                        dist[i][j] = min(dist[i][j] , dist[i][k] + dist[k][j]);
                    }
                }
            }
        }
    }
};