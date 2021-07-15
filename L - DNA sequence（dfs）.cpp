/**
题目描述
21世纪是生物科技飞速发展的时代。我们都知道基因是由DNA组成的，而DNA的基本组成单位是A,C,G,T。在现代生物分子计算中，如何找到DNA之间的最长公共子序列是一个基础性问题。
但是我们的问题不是那么简单：现在我们给定了数个DNA序列，请你构造出一个最短的DNA序列，使得所有我们给定的DNA序列都是它的子序列。
例如，给定"ACGT","ATGC","CGTT","CAGT",你可以构造的一个最短序列为"ACAGTGCT"，但是需要注意的是，这并不是此问题的唯一解。
输入
第一行含有一个数t，代表数据组数。
每组数据的第一行是一个数n，代表给定的DNA序列数量；接下来的n行每行一个字符串s，代表给定的n个DNA序列。
1<=n<=8，1<=|s|<=5
输出
对于每一组数据，输出一行中含有一个数，代表满足条件的最短序列的长度。
样例输入
1
4
ACGT
ATGC
CGTT
CAGT
样例输出
8

解题思路：使用迭代加深搜索，以最长的字符串长度为下界开始迭代加深，最后的答案一定是最短序列。
**/
#include<iostream>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;

char a[4]={'A','C','G','T'};
int len[10];
int pos[10];
string s[10];
int deep,ans=-1,n;

void dfs(int step,int pos[])
{
	if(step>deep)return ;
	int tot=0;
	for(int i=1;i<=n;i++){
		tot=max(tot,len[i]-pos[i]);	
	}
	if(tot==0){
		ans=step;
		return ;
	}
	if(tot+step>deep)return ;
	for(int i=0;i<4;i++){
		int flag=0;	
		int po[10]={0};	
		for(int j=1;j<=n;j++){
			if(s[j][pos[j]]==a[i]){
				po[j]=pos[j]+1;
				flag=1;
			}else po[j]=pos[j];
		}
		if(flag)dfs(step+1,po);
		if(ans!=-1)return ;
	} 
}

int main()
{
	int t;
	cin>>t;
	while(t--){
		cin>>n;
		deep=0;
		ans=-1;
		for(int i=1;i<=n;i++){
			cin>>s[i];
			len[i]=s[i].size();
			deep=max(deep,len[i]);
		}
		while(1){
			memset(pos,0,sizeof pos);
			dfs(0,pos);
			if(ans!=-1){
				cout<<ans<<endl;
				break;
			}
			deep++;
		}
	}
}
