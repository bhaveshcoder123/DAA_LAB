#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
  
    bool dfs(vector<int> &visited , vector<int> &path , int node , vector<vector<int>> &adj) {
        visited[node] = true;
        path[node] = true;
        
        for(int neighbour : adj[node]) {
            if(!visited[neighbour]) {
                if(dfs(visited , path , neighbour , adj)) return true;;
            }
            else if (path[neighbour]) return true;
        }
        
        path[node] = false; 
        return false;
    }
    bool isCyclic(int V, vector<vector<int>> &edges) {
        
        int E = edges.size();
        vector<vector<int>> adj(V);
        for(int i = 0 ; i<E ; i++) {
            adj[edges[i][0]].push_back(edges[i][1]);
        }
        
        vector<int> visited(V , false);
        vector<int> path(V , false);
        for(int i = 0 ; i<V ; i++) {
            if(!visited[i]) {
                if(dfs(visited , path , i , adj)) return true;
            }
        }
        
        return false;
    }
};