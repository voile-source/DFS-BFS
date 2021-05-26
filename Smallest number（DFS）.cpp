/**
最近，gx再次在代数中得到了不好的印象。为了避免将来出现这种不愉快的事件，他决定训练他的算术技巧。他在黑板上写了四个整数a，b，c，d。在接下来的三分钟的每一分钟中，他从黑板上取了两个数字（不一定是相邻的）并用它们的总和或它们的乘积替换它们。最后他有一个号码。不幸的是，由于可怕的记忆他忘记了这个数字，但他记得四个原始数字，操作顺序和他的惊喜，因为非常小的结果。帮助gx记住遗忘的数字：找到可以通过给定的操作顺序从原始数字中获得的最小数字。

Input
第一行包含由空格隔开四个整数：0≤  a，  b，  c ，  d  ≤1000 -原号码。第二行包含三个符号（每个'+'或'*'）用空格分隔 - 操作顺序按执行顺序排列。（'+'代表加法，'*' - 乘法）

Output
输出一个整数 - 可以获得的最小结果。

Examples
Input
1 1 1 1
+ + *
Output
3
Input
2 2 2 2
* * +
Output
8
Input
1 2 3 4
* + +
Output
9

解题思路：直接DFS爆搜所有状态，测试的时候看到是cf的题以为是思维题，结果搞了半天其实dfs就行了.......
**/

#include<iostream>
#include<algorithm>
using namespace std;

long long a[4];
char s[3];
long long ans=2e18;

void dfs(long long a,long long b)
{
	long long x=s[2]=='+'?a+b:a*b;
	ans=min(ans,x);
}

void dfs1(long long a,long long b,long long c)
{
	if(s[1]=='+'){
		dfs(a+b,c);
		dfs(a+c,b);
		dfs(b+c,a);
	}else{
		dfs(a*b,c);
		dfs(a*c,b);
		dfs(b*c,a);
	}
}

void dfs2(long long a,long long b,long long c,long long d)
{
	if(s[0]=='+'){
		dfs1(a+b,c,d);
		dfs1(a+c,b,d);
		dfs1(a+d,b,c);
		dfs1(b+c,a,d);
		dfs1(b+d,a,c);
		dfs1(c+d,a,b); 
	}else{
		dfs1(a*b,c,d);
		dfs1(a*c,b,d);
		dfs1(a*d,b,c);
		dfs1(b*c,a,d);
		dfs1(b*d,a,c);
		dfs1(c*d,a,b); 
	}
}

int main() {
	for(int i=0;i<4;i++)cin>>a[i];
	for(int j=0;j<3;j++)cin>>s[j];
	dfs2(a[0],a[1],a[2],a[3]);
	cout<<ans; 
} 
