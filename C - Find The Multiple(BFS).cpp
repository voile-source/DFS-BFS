/**
在2100年科学家发现了平行宇宙，但是新发现的Earth2的世界中所有数字都是由0和1组成的十进制数，如果从我们的世界穿越到Earth2，数字将发生一些变化，例如：一个正整数n，将被转化为n的一个非零的倍数m，这个m应当符合Earth2的数字规则。你可以假定n不大于200且m不多于100位。
提示：本题采用Special Judge，你无需输出所有符合条件的m，你只需要输出任一符合条件的m即可。

Input
输入包含多组数据，每组数据仅一行，只包含一个正整数n，n==0时输入结束 (1 <= n <= 200).

Output
对于输入的每组n，都输出任一符合条件的m。即使有多个符合条件的m，你也只需要输出一个即可。
（已知long long范围内存在表示数据中所有的m

Sample Input
2
6
19
0

Sample Output
10
100100100100100100
111111111111111111

题目大意：求一个整数在long long 范围内仅由1和0组成的倍数

解题思路：BFS往两个方向搜，n*10，n*10+1刚好确保了除数由1和0构成（从1开始搜）
**/

#include<iostream>
#include<queue>
using namespace std;
typedef long long ll;

void bfs(int n){
	queue<ll> Q;
	Q.push(1);
	while(!Q.empty()){
		ll p=Q.front();
		Q.pop();
		if(p%n==0){
			cout<<p<<endl;
			return ;
		}
		Q.push(p*10);
		Q.push(p*10+1);
	}
}

int main()
{
	ios::sync_with_stdio(false);   
    cin.tie(0);
    cout.tie(0);
	int n;
	while(cin>>n&&n){;
		bfs(n);
	}
}
