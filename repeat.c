struct TreeNode {
     int val;
     struct TreeNode *left;
     struct TreeNode *right;
};


bool isSameTree(struct TreeNode* p, struct TreeNode* q) {
    struct TreeNode* q1[1000];  // очередь для дерева 1
    struct TreeNode* q2[1000];  // очередь для дерева 2
    int front = 0, rear = 0;
    
    q1[rear] = p;
    q2[rear] = q;
    rear++;
    
    while (front < rear) {
        struct TreeNode* node1 = q1[front];
        struct TreeNode* node2 = q2[front];
        front++;

        if (!node1 && !node2) continue;
        if (!node1 || !node2) return false;
        if (node1->val != node2->val) return false;

        q1[rear] = node1->left;   q2[rear] = node2->left;   rear++;
        q1[rear] = node1->right;  q2[rear] = node2->right;  rear++;
    }
    
    return true;
}
