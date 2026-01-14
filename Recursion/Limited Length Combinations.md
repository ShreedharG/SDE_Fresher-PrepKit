https://leetcode.com/problems/combinations/description/

```
class Solution {
public:
    void generate_combo(int id, int used, vector<int>& combo,vector<vector<int>>& ans,int n,int k){
        if(used == k){
            ans.push_back(combo);
            return;
        }
  
        if(id > n) return;
  
        combo.push_back(id);
        generate_combo(id+1,used+1,combo,ans,n,k);
  
        combo.pop_back();
        generate_combo(id+1,used,combo,ans,n,k);
    }
  
    vector<vector<int>> combine(int n, int k) {
        vector<int> combo;
        vector<vector<int>> ans;
  
        generate_combo(1,0,combo,ans,n,k);
        return ans;
    }
};
```

Return -> [[Recursion + Backtracking]]

