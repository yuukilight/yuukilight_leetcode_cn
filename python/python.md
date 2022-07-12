# 二进制位运算
```python
# 461 计算汉明距离
class Solution:
    def hammingDistance(self, x: int, y: int) -> int:
        return bin(x^y).count('1')
```