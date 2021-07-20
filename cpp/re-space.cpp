/*
Leetcode exercise, 17.13. 恢复空格.
哦，不！你不小心把一个长篇文章中的空格、标点都删掉了，并且大写也弄成了小写。像句子"I reset the computer. 
It still didn’t boot!"已经变成了"iresetthecomputeritstilldidntboot"。在处理标点符号和大小写之前，你得
先把它断成词语。当然了，你有一本厚厚的词典dictionary，不过，有些词没在词典里。假设文章用sentence表示，设计
一个算法，把文章断开，要求未识别的字符最少，返回未识别的字符数。

注意：本题相对原题稍作改动，只需返回未识别的字符数

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/re-space-lcci
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:	
	int respace(vector<string>& dictionary, string sentence) {
        int slen = sentence.length();
        int dlen = dictionary.size();
        // using dp , first init dp, size is the string, value is max length
        vector<int> dp(slen+1,slen);
        dp[0]=0;
        // check from every start position in string, find match word, make the word's next dp <= the start
        for(int i=0;i<=slen;i++) // i=slen to assign the total cost
        {
            // basic cost for each dp
            if(i>0)
            {
                dp[i]=min(dp[i],dp[i-1]+1); // cost+1, but <= in case matched word before
            }

            // look for each word
            for(int j=0;j<dlen;j++)
            {
                int wlen = dictionary[j].size();
                if(i+wlen>slen)//longer than the string
                {
                    continue;
                }
                if(sentence.substr(i,wlen)==dictionary[j]) // found match word
                {
                    dp[i+wlen]=min(dp[i+wlen],dp[i]); // the dp after word end <= the start
                }

            }

        }
        return dp[slen];
    }

};

int main() {
		vector<string> dict = { "looked","looked2","just","like","her","brother" };
		string s = "jesslooked2justliketimherbrother";
	    dict = { "frrrbbrrbfrfqqbbbrb", "qr", "b", "rf", "qqbbbbfrqbrrqrffbrqqqbqqfqfrr", "r", "ffqq", "bffbqfqqbrrrf", "fq", "qfr", "fr", "rqrrbfbfq", "r", "f", "qbqbrbrbqfqbbbfbbbfbq", "bqqbbbqrbbrf", "f" };
	    s = "bqqffbqbbfqrfrrrbbrrbfrfqqbbbrbfqfffffrfqfqfffffrrfqfrrqbqfrbfrqqrfrbrbbqbqbqqfqrfbfrfr";
		dict = { "aaysaayayaasyya", "yyas", "yayysaaayasasssy", "yaasassssssayaassyaayaayaasssasysssaaayysaaasaysyaasaaaaaasayaayayysasaaaa", "aya", "sya", "ysasasy", "syaaaa", "aaaas", "ysa", "a", "aasyaaassyaayaayaasyayaa", "ssaayayyssyaayyysyayaasaaa", "aya", "aaasaay", "aaaa", "ayyyayssaasasysaasaaayassasysaaayaassyysyaysaayyasayaaysyyaasasasaayyasasyaaaasysasy", "aaasa", "ysayssyasyyaaasyaaaayaaaaaaaaassaaa", "aasayaaaayssayyaayaaaaayaaays", "s" };
		s = "asasayaayaassayyayyyyssyaassasaysaaysaayaaaaysyaaaa";
		dict = { "frrrbbrrbfrfqqbbbrb", "qr", "b", "rf", "qqbbbbfrqbrrqrffbrqqqbqqfqfrr", "r", "ffqq", "bffbqfqqbrrrf", "fq", "qfr", "fr", "rqrrbfbfq", "r", "f", "qbqbrbrbqfqbbbfbbbfbq", "bqqbbbqrbbrf", "f" };
		s= "bqqffbqbbfqrfrrrbbrrbfrfqqbbbrbfqfffffrfqfqfffffrrfqfrrqbqfrbfrqqrfrbrbbqbqbqqfqrfbfrfr";
        // dict = {"jxnonurhhuanyuqahjy","phrxu","hjunypnyhajaaqhxduu"};
        // s= "qahurhoharrdjxnonurhhuanyuqahjyppnha";
	Solution sl;
	std::cout << sl.respace(dict, s);
}
