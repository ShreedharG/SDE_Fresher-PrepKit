https://www.geeksforgeeks.org/problems/distance-from-the-source-bellman-ford-algorithm/1

```
class Solution {
  public:
    vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src){
        vector<int> dis(V,INT_MAX);
        dis[src] = 0;
    
        for(int i=1;i<=(V-1);i++){
            for(auto edge : edges){
                int u = edge[0], v = edge[1], w = edge[2];
                
                if(dis[u] != INT_MAX && dis[v] > dis[u]+w)
                    dis[v] = dis[u]+w;
            }
        }
        
        for(auto edge : edges){
            int u = edge[0], v = edge[1], w = edge[2];
            
            if(dis[u] != INT_MAX && dis[v] > dis[u] + w)
                return {-1};
        }
        
        for(int i=0;i<V;i++)
            dis[i] = dis[i]==INT_MAX ? 1e8 : dis[i];
            
        return dis;
    }
};
```


Return -> [[Shortest Path Algorithms]]

