class Solution(object):
    def combinationSum(self, candidates, target):
        result = []
        
        def backtrack(start, path, total):
            # Base case
            if total == target:
                result.append(path[:])
                return
            
            if total > target:
                return
            
            for i in range(start, len(candidates)):
                # choose
                path.append(candidates[i])
                
                # stay at i (reuse same element)
                backtrack(i, path, total + candidates[i])
                
                # undo
                path.pop()
        
        backtrack(0, [], 0)
        return result
        