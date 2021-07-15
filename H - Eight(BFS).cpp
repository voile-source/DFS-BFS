/**
  简单介绍一下八数码问题：
在一个3×3的九宫格上，填有1~8八个数字，空余一个位置，例如下图：
1	2	3
4	5	6
7	8	 
在上图中，由于右下角位置是空的，你可以移动数字，比如可以将数字6下移一位：
1	2	3	 	1	2	3
4	5	6	→	4	5	 
7	8	 	 	7	8	6
或者将数字8右移一位：
1	2	3	 	1	2	3
4	5	6	→	4	5	6
7	8	 	 	7	 	8
1~8按顺序排列的情况称为“初始状态”（如最上方图）。“八数码问题”即是求解对于任意的布局，将其移动至“初始状态”的方法。
给定一个现有的九宫格布局，请输出将它移动至初始状态的移动方法的步骤。
Input
输入包含多组数据，处理至文件结束。每组数据占一行，包含8个数字和表示空位的‘x’，各项以空格分隔，表示给定的九宫格布局。
例如，对于九宫格
1	2	3
 	4	6
7	5	8
输入应为：1 2 3 x 4 6 7 5 8
注意，输入的数字之间可能有(不止一个？)空格。
Output
对于每组输入数据，输出一行，即移动的步骤。向上、下、左、右移动分别用字母u、d、l、r表示；如果给定的布局无法移动至“初始 状态”，请输出unsolvable。
如果有效的移动步骤有多种，输出任意即可。
Sample Input
2  3  4  1  5  x  7  6  8
Sample Output
ullddrurdllurdruldr

解题思路：使用康托展开值去重，将目标状态12345678x的所有变换操作情况预处理出来，然后直接根据输入数据的康托值输出答案。由于我们是从目标态推初始态，
所以在预处理的时候需要稍微做一下修改的小操作，存操作顺序是要逆序存且反向，假设从目标态到初始态的操作顺序是rrd，那么从初始态到目标态的操作顺序就
是ull了，所以操作顺序需要逆序且反向。
**/


#include<iostream>
#include<string>
#include<cstring>
#include<queue>
#include<map>
#include<algorithm>
using namespace std;
const int max_n=4e6+10;

struct node{
	string s;
	string op;
};

int vis[max_n];
map<int,string> path;
int fac[]={1,1,2,6,24,120,720,5040,40320,362880};
char c[4]={'d','u','r','l'};

int contor(string s)
{
	int ans=0,cnt;
	int len=s.size();
	for(int i=0;i<len-1;i++){
		cnt=0;
		for(int j=i+1;j<len;j++){
			if(s[j]<s[i])cnt++;
		}
		ans+=cnt*fac[len-i-1];
	}
	return ans;
}

string eight(string s,int t)
{
	char a[3][3];
	int x,y;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			a[i][j]=s[i*3+j];
			if(a[i][j]=='x'){
				x=i;
				y=j;
			}
		}
	}
	int nx=x,ny=y; 
	if(t==0)nx--; 
	else if(t==1)nx++;
	else if(t==2)ny--;
	else if(t==3)ny++;
	if(nx<0||ny<0||nx>=3||ny>=3)return "-1";
	swap(a[x][y],a[nx][ny]); 
	string k;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			k+=a[i][j];
		}
	}
	return k;
}

void bfs()
{
	queue<node> Q;
	node a;
	a.s="12345678x";
	a.op="";
	vis[contor(a.s)]=1;
	Q.push(a); 
	node p,q;
	while(!Q.empty()){
		p=Q.front();
		Q.pop();
		for(int i=0;i<4;i++){
			q=p;
			q.s=eight(q.s,i);
			if(q.s=="-1")continue;	
			if(vis[contor(q.s)])continue;
			q.op=c[i]+q.op;
			path[contor(q.s)]=q.op;
			vis[contor(q.s)]=1;
			Q.push(q);
		}
	}
}

int main()
{
	bfs();
	char c;
	while(cin>>c){
		string s;
		s+=c;
		for(int i=0;i<8;i++){
			cin>>c;
			s+=c;
		} 
		int t=contor(s);
		if(!vis[t])cout<<"unsolvable"<<endl;
		else cout<<path[t]<<endl;;
	} 
} 
