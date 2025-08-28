# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def minDepth(self, root: Optional[TreeNode]) -> int:
        min_count = 0
        if not root:
            return 0
        queue = deque([(root, 1)])
        while queue:
            node, min_count = queue.popleft()
            if not node.left and not node.right:
                return min_count
            if node.left:
                queue.append((node.left, min_count + 1))
            if node.right:
                queue.append((node.right, min_count + 1))
