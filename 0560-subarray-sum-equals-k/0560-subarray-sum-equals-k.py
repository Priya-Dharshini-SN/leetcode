class Solution(object):
    def subarraySum(self, nums, k):
        count = 0 
        prefix_sum = 0 
        heapmap = {0:1}
        for num in nums:
            prefix_sum += num
            if(prefix_sum - k) in heapmap:
                count += heapmap[prefix_sum - k]
            heapmap[prefix_sum] = heapmap.get(prefix_sum, 0) + 1
        return count
        