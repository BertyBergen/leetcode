# DFS 
class Solution:
    def solve(self, board: List[List[str]]) -> None:
        rows, cols = len(board), len(board[0])

        def dfs(r, c):
            if r < 0 or r >= rows or c < 0 or c >= cols or board[r][c] != "O":
                return
            board[r][c] = "S"
            dfs(r + 1, c)
            dfs(r - 1, c)
            dfs(r, c + 1)
            dfs(r, c - 1)

        for r in range(rows):
            for c in range(cols):
                if (r in [0, rows - 1] or c in [0, cols - 1]) and board[r][c] == "O":
                    dfs(r, c)

        for r in range(rows):
            for c in range(cols):
                if board[r][c] == "O":
                    board[r][c] = "X"
                elif board[r][c] == "S":
                    board[r][c] = "O"
# BFS 
from collections import deque

class Solution:
    def solve(self, board: List[List[str]]) -> None:
        if not board: return
        rows, cols = len(board), len(board[0])
        q = deque([(r, c) for r in [0, rows-1] for c in range(cols)] + [(r, c) for r in range(rows) for c in [0, cols-1]])
        while q:
            r, c = q.popleft()
            if 0 <= r < rows and 0 <= c < cols and board[r][c] == "O":
                board[r][c] = "S"
                q.extend([(r+1,c),(r-1,c),(r,c+1),(r,c-1)])
        for r in range(rows):
            for c in range(cols):
                board[r][c] = "O" if board[r][c] == "S" else "X"
