/*
957. N 天后的牢房
8 间牢房排成一排，每间牢房不是有人住就是空着。

每天，无论牢房是被占用或空置，都会根据以下规则进行更改：

如果一间牢房的两个相邻的房间都被占用或都是空的，那么该牢房就会被占用。
否则，它就会被空置。
（请注意，由于监狱中的牢房排成一行，所以行中的第一个和最后一个房间无法有两个相邻的房间。）

我们用以下方式描述监狱的当前状态：如果第 i 间牢房被占用，则 cell[i]==1，否则 cell[i]==0。

根据监狱的初始状态，在 N 天后返回监狱的状况（和上述 N 种变化）。
示例 1：

输入：cells = [0,1,0,1,1,0,0,1], N = 7
输出：[0,0,1,1,0,0,0,0]
解释：
下表概述了监狱每天的状况：
Day 0: [0, 1, 0, 1, 1, 0, 0, 1]
Day 1: [0, 1, 1, 0, 0, 0, 0, 0]
Day 2: [0, 0, 0, 0, 1, 1, 1, 0]
Day 3: [0, 1, 1, 0, 0, 1, 0, 0]
Day 4: [0, 0, 0, 0, 0, 1, 0, 0]
Day 5: [0, 1, 1, 1, 0, 1, 0, 0]
Day 6: [0, 0, 1, 0, 1, 1, 0, 0]
Day 7: [0, 0, 1, 1, 0, 0, 0, 0]

示例 2：

输入：cells = [1,0,0,1,0,0,1,0], N = 1000000000
输出：[0,0,1,1,1,1,1,0]
 

提示：

cells.length == 8
cells[i] 的值为 0 或 1 
1 <= N <= 10^9

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/prison-cells-after-n-days
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
最直接的办法是暴力罗列，但是在leetcode上会超时。
随后发现，由于数列有限，可能的排列组合也有限，只要找到重复出现的组合，随后的就能直接得出：保存重复之前的序列，并计算N在重复序列中对应的位置。
*/
class Solution {
public:
    vector<int> prisonAfterNDays(vector<int>& cells, int n) {
        vector<vector<int>> result; // 用于保存已计算的序列
        
        vector<int> row(8); //临时序列，随后会判断并保存到result
        if(n==0){
            return cells;
        }else{
            int repeatStartIndex = n;
            int repeatLen = 1;
            bool repeat = false;
            result.push_back(cells);
            int r=1;
            while(r<=n){
                row[0]=0; // 由于两侧牢房无法有两个相邻的房间，从第一天开始永远为0
                row[7]=0;
                for(int i=1;i<7;i++){
                    row[i]=int(result[r-1][i-1]==result[r-1][i+1]); //其他牢房的状态由上一天两侧牢房的状态决定
                }
                // look for repeat row
                for(int j=0;j<result.size();j++){
                    if(result[j]==row){
                        repeat = true;
                        repeatStartIndex = j; // 从r天开始就重复，重复对应的是第j天，也就是j到r-1是重复的区间
                        repeatLen = r-repeatStartIndex; //
                        break;
                    }
                }
                if(!repeat){
                    result.push_back(row); // 没重复就记录
                }else{
                    break; // 重复出现后，不再计算牢房新的状态
                }
                r++;
            }
            if(n<repeatStartIndex) return result[n]; // 没重复时，直接返回记录的对应状态
            else{ //重复区间的状态
                return result[(n-repeatStartIndex)%repeatLen+repeatStartIndex];
            }
        }
    }
};