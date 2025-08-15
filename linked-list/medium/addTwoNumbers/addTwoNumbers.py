# Определение ListNode для LeetCode
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def addTwoNumbers(self, l1: ListNode, l2: ListNode) -> ListNode:
        dummy = ListNode()  # фиктивный узел
        current = dummy
        carry = 0
        
        # пока есть цифры или перенос
        while l1 or l2 or carry:
            v1 = l1.val if l1 else 0
            v2 = l2.val if l2 else 0
            s = v1 + v2 + carry
            carry = s // 10
            digit = s % 10
            
            # создаём новый узел
            current.next = ListNode(digit)
            current = current.next
            
            # двигаемся по спискам
            if l1:
                l1 = l1.next
            if l2:
                l2 = l2.next
        
        return dummy.next
