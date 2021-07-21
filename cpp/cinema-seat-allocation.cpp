/* 查找连续空位 匹配指定位置模式 
https://leetcode-cn.com/problems/cinema-seat-allocation/
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    // 直接查找
    int maxNumberOfFamilies1(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, bool> map;
        int maxNum = 0;
        // write down the seats reserved
        for(int i=0;i<reservedSeats.size();i++)
        {
            if(reservedSeats[i][1]!=1&&reservedSeats[i][1]!=10)
            {
                map[reservedSeats[i][0]*10+reservedSeats[i][1]]=1;
            }
        }
        for(int r=1;r<=n;r++)
        {
            int c=2;
            while(c<10&&map[r*10+c]==0)
            {
                c++;
            }
            // 2 families
            if(c==10) maxNum+=2;
            // 1 families
            else if(c>5) maxNum+=1;
            else if(map[r*10+6]==0&&map[r*10+7]==0)
            {
                // middle
                if(map[r*10+4]==0&&map[r*10+5]==0) maxNum+=1;
                else if(map[r*10+8]==0&&map[r*10+9]==0) maxNum+=1;

            }
        }
        return maxNum;
    }

    //bitmap
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, int> map;
        int maxNum = 0;
        int right = 0b11110000; // 0 is empty seat
        int middle = 0b11000011;
        int left = 0b00001111;

        // write down the seats reserved
        for(const vector<int>& seat:reservedSeats)
        {
            if(seat[1]!=1&&seat[1]!=10)
            {
                map[seat[0]] |= 1 << (seat[1]-2);
            }
        }
        maxNum = (n-map.size())*2; // no reserved row fits 2 families
        for(auto& [row,bitvalue]:map)
        {
            // 1 families
            if((bitvalue|left)==left||(bitvalue|middle)==middle||(bitvalue|right)==right) ++maxNum;
        }
        return maxNum;
    }
};

int main(){
    int n;
   vector<vector<int>> r={{1,6},{1,8},{1,3},{2,3},{1,10},{1,2},{1,5},{2,2},{2,4},{2,10},{1,7},{2,5}};
    n=2;
    Solution sl;
	cout << sl.maxNumberOfFamilies(n,r);
}