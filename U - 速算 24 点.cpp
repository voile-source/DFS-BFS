/**
速算24点相信绝大多数人都玩过。就是随机给你四张牌，包括A(1),2,3,4,5,6,7,8,9,10,J(11),Q(12),K(13)。要求只用'+','-','*','/'运算符以及括号改变运算顺序，使得最终运算结果为24(每个数必须且仅能用一次)。游戏很简单，但遇到无解的情况往往让人很郁闷。你的任务就是针对每一组随机产生的四张牌，判断是否有解。我们另外规定，整个计算过程中都不能出现小数。
Input
每组输入数据占一行，给定四张牌。
Output
每一组输入数据对应一行输出。如果有解则输出"Yes"，无解则输出"No"。
Sample Input
A 2 3 6
3 3 8 8
Sample Output
Yes
No

解题思路：bfs暴搜所有可能的组合情况，首先预处理好输入的每个数的值，然后使用next_permutation,求出这四个数的全排列，之后搜索所有可能的情况。
**/
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

int a[5];
int flag;

int to(string s){
	if(s[0]=='1')return 10;
	if(s[0]=='A')return 1;
	if(s[0]=='J')return 11;
	if(s[0]=='Q')return 12;
	if(s[0]=='K')return 13;
	return s[0]-'0';
}

void dfs(int x,int y,int step){

	if(step==5){
		if(x+y==24||x-y==24||x*y==24)flag=1;
		if(y&&(x%y==0)&&x/y==24)flag=1;
		return;
	}
	dfs(x+y,a[step],step+1);
	dfs(x-y,a[step],step+1);
	dfs(x*y,a[step],step+1);
	if(y&&x%y==0)dfs(x/y,a[step],step+1);
	dfs(x,y+a[step],step+1);
	dfs(x,y-a[step],step+1);
	dfs(x,y*a[step],step+1);
	if(a[step]&&y%a[step]==0)dfs(x,y/a[step],step+1);
}

int main()
{
	string s;
	while(cin>>s){
		a[1]=to(s);
		for(int i=2;i<=4;i++){
			cin>>s;
			a[i]=to(s);
		}
		sort(a+1,a+5);
		flag=0;
		do {
			dfs(a[1],a[2],3);
			if(flag)break;
		}while(next_permutation(a+1,a+5));
		if(flag)cout<<"Yes"<<endl;
		else cout<<"No"<<endl;	
	}
}
