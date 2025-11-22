#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    void topoSort(vector<bool> &visited , stack<int> &st , int node , vector<vector<int>> &adj) {
        visited[node] = true;
        
        for(auto &neighbour : adj[node]) {
            if(!visited[neighbour]) {
                topoSort(visited , st , neighbour , adj);
            }
        }
        
        st.push(node);
    }
    
    
    void dfs(int node , vector<vector<int>> &adj , vector<bool> &visited) {
        visited[node] = true;
        for(auto &neighbour : adj[node]) {
            if(!visited[neighbour]) {
                dfs(neighbour, adj , visited);
            }
        }
    }
    
    int kosaraju(vector<vector<int>> &adj) {
        int V = adj.size();
        stack<int> st;
        vector<bool> visited(V , false);
        
        for(int i = 0 ; i<V ; i++) {
            if(!visited[i]) {
                topoSort(visited , st , i , adj);
            }
        }
        
        vector<vector<int>> rev_adj(V);
        
        for(int node = 0 ; node<V ; node++) {
            for(auto &neighbour : adj[node]) {
                rev_adj[neighbour].push_back(node);
            }
        }
        
        for(int i = 0 ; i<V ; i++) visited[i] = false;
        
        int scc = 0;
        
        while(!st.empty()) {
            int node = st.top();
            st.pop();
            if(visited[node]) continue;
            scc++;
            dfs(node , rev_adj , visited);
        }
        
        return scc;
    }
    
    
    //Find topological Sort DFS
    // Reverse the edges
    // Empty the stack and count scc by counting how many cont dfs required.
};