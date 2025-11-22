#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    vector<int> bellmanFord(int V, vector<vector<int>>& edges, int node) {
        vector<int> dist(V , 1e8);
        dist[node] = 0;
        
        for(int i = 0 ; i<V-1 ; i++) {
            for(auto &edge : edges) {
                int src = edge[0];
                int dest = edge[1];
                int w = edge[2];
                
                if(dist[src] != 1e8 && dist[src] + w < dist[dest]) {
                    dist[dest] = dist[src] + w;
                }
            }
        }
        
        
        for(auto &edge : edges) {
            int src = edge[0];
            int dest = edge[1];
            int w = edge[2];
            
            if(dist[src] != 1e8 && dist[src] + w < dist[dest]) {
                return {-1};
            }
        }
        
        return dist;
    }
};