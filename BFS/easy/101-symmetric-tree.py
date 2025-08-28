from collections import deque
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def isSymmetric(self, root: Optional[TreeNode]) -> bool:
        
        queue = queue([(root.left, root.right)])

        while queue:
            node1, node2 = queue.popleft()

            if not node1 and not node2:
                continue
            if not node1 or not node2:
                return False
            if node1.val != node2.val:
                return False
            
            queue.append((node1.left, node2.right))
            queue.append((node1.right, node2.right))
        
        return True
        


class Solution:
    def isSymmetric(self, root: Optional[TreeNode]) -> bool:
        def isMirror(t1, t2):
            if not t1 and not t2: return True
            if not t1 or not t2: return False
            return (t1.val == t2.val 
                    and isMirror(t1.left, t2.right) 
                    and isMirror(t1.right, t2.left))
        
        return isMirror(root, root)
