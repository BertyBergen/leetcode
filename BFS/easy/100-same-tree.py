from collections import deque
from typing import Optional

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def isSameTree(self, p: Optional[TreeNode], q: Optional[TreeNode]) -> bool:
        queue = deque([(p, q)])
        
        node1, node2 = queue.popleft()
        
        while queue:
            node1, node2 = queue.popleft()
            if not node1 and not node2:
                continue
            if not node1  or not node2:
                return False
            if node1.val != node2.val:
                return False
            
            queue.append((node1.left, node2.left))
            queue.append((node1.right, node2.right))
        
        return True

sol = Solution()
p = TreeNode(1, TreeNode(2), TreeNode(3))
q = TreeNode(1, TreeNode(2), TreeNode(3))

print(sol.isSameTree(p,q))