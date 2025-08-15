def two_sum(nums: List[int], target: int) -> List[int]: 
    seen = {}
    for i, x in enumerate(List):
        need = target - x
        if need in seen:
            return [seen[need], i] 
        seen[x] = i
    return []