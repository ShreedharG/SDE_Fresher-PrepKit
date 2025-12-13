https://leetcode.com/problems/minimum-absolute-difference-in-bst/?envType=study-plan-v2&envId=top-interview-150

```cpp
class Solution {
public:
    int prev = -1;
  
    void inorder(TreeNode* root,int& ans){
        if(root){
            inorder(root->left, ans);
  
            if(prev != -1)
                ans = min(ans, root->val - prev);
            prev = root->val;
  
            inorder(root->right, ans);
        }
    }

    int getMinimumDifference(TreeNode* root) {
        int ans = INT_MAX;
        inorder(root,ans);    

        return ans;
    }
};
```

Return -> [[Binary search tree]]

