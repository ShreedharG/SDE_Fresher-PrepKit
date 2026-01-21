https://www.geeksforgeeks.org/problems/minimum-cost-of-ropes-1587115620/1

```
class Solution {
  public:
    int minCost(vector<int>& arr) {
        int total = 0;
        
        priority_queue<int,vector<int>,greater<int>> pq;
        for(auto num: arr)
            pq.push(num);
        
        while(pq.size() > 1){
            int top1 = pq.top(); pq.pop();
            int top2 = pq.top(); pq.pop();
            
            total += (top1 + top2);
            pq.push(top1 + top2);
        }
        return total;
    }
};
```

Return -> [[Heaps]]

