function maxFrequencyScore(nums, k) {
  nums.sort((a, b) => a - b);
  const n = nums.length;
  const pref = new Array(n);
  pref[0] = nums[0];
  for (let i = 1; i < n; i++) {
    pref[i] = pref[i - 1] + nums[i];
  }

  function sumRange(L, R) {
    if (L > R) return 0;
    return pref[R] - (L > 0 ? pref[L - 1] : 0);
  }

  let left = 0;
  let maxLen = 1;

  for (let right = 0; right < n; right++) {
    while (left <= right) {
      const length = right - left + 1;
      const mid = left + Math.floor((length - 1) / 2);
      const median = nums[mid];

      const sumL = sumRange(left, mid);
      const sumR = sumRange(mid + 1, right);

      const leftCount = mid - left + 1;
      const rightCount = right - mid;

      const cost = median * leftCount - sumL + sumR - median * rightCount;

      if (cost <= k) break;
      left++;
    }
    const curLen = right - left + 1;
    if (curLen > maxLen) maxLen = curLen;
  }

  return maxLen;
}

// Пример
const nums = [1, 2, 6, 4];
const k = 3;
console.log(maxFrequencyScore(nums, k)); // 3
