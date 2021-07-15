/**
Eight-puzzle, which is also called "Nine grids", comes from an old game.

In this game, you are given a 3 by 3 board and 8 tiles. The tiles are numbered from 1 to 8 and each covers a grid. As you see, there is a blank grid which can be represented as an 'X'. Tiles in grids having a common edge with the blank grid can be moved into that blank grid. This operation leads to an exchange of 'X' with one tile.

We use the symbol 'r' to represent exchanging 'X' with the tile on its right side, and 'l' for the left side, 'u' for the one above it, 'd' for the one below it.



A state of the board can be represented by a string S using the rule showed below.



The problem is to operate an operation list of 'r', 'u', 'l', 'd' to turn the state of the board from state A to state B. You are required to find the result which meets the following constrains:
1. It is of minimum length among all possible solutions.
2. It is the lexicographically smallest one of all solutions of minimum length.
Input
The first line is T (T <= 200), which means the number of test cases of this problem.

The input of each test case consists of two lines with state A occupying the first line and state B on the second line.
It is guaranteed that there is an available solution from state A to B.
Output
For each test case two lines are expected.

The first line is in the format of "Case x: d", in which x is the case number counted from one, d is the minimum length of operation list you need to turn A to B.
S is the operation list meeting the constraints and it should be showed on the second line.
Sample Input
2
12X453786
12345678X
564178X23
7568X4123
Sample Output
Case 1: 2
dd
Case 2: 8
urrulldr

解题思路：这题相比Eight I 多了一些条件，不仅要求出操作顺序，而且还得使操作顺序最短+字典序最小。我们先将X在“12345678X”中不同位置的九种情况的所有可能的变换情况BFS预处理出来，
然后给输入的初始状态进行一个映射，使它变成这九种初始状态中的一种，然后根据变换的情况输出答案。
**/

#include<iostream>
#include<string>
#include<queue>
#include<algorithm>
#include<cstring>
using namespace std;
const int max_n = 5e5+10;

struct node{
	string s;
	int sta;
	int con;
};

int vis[9][max_n];
int pre[9][max_n];
int fac[]={1,1,2,6,24,120,720,5040,40320,362880};
int ne[4][2]={1,0,0,-1,0,1,-1,0};
char c[4]={'d','l','r','u'};
string s[9]={"X12345678","1X2345678","12X345678","123X45678","1234X5678","12345X678","123456X78","1234567X8","12345678X"};

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

void bfs(int op,node a)
{
	queue<node> Q;
	vis[op][a.con]=1;
	Q.push(a);
	node p,q;
	while(!Q.empty()){
		p=Q.front();
		Q.pop();
		int x,y;
		x=p.sta/3;
		y=p.sta%3;
		for(int i=0;i<4;i++){
			q=p;
			int nx=x+ne[i][0];
			int ny=y+ne[i][1];
			if(nx<0||ny<0||nx>=3||ny>=3)continue;
			swap(q.s[x*3+y],q.s[nx*3+ny]);
			int t=contor(q.s);
			if(vis[op][t]!=-1)continue;
			q.sta=nx*3+ny;
			q.con=t;
			vis[op][t]=i;
			pre[op][t]=p.con;
			Q.push(q);
		}
	}	
}

void init()
{
	memset(vis,-1,sizeof vis);
	memset(pre,-1,sizeof pre);
	for(int i=0;i<9;i++){
		bfs(i,(node){s[i],i,contor(s[i])});
	}
}

int main()
{
	init();
	int t;
	cin>>t;
	for(int e=1;e<=t;e++){
		string a,b,y="000000000";
		cin>>a>>b;
		int op;
		char num[10];
		int cnt=1;
		for(int i=0;i<a.size();i++){
			if(a[i]=='X'){
				op=i;
				continue;
			}
			num[a[i]-'0']='0'+cnt++;	
		}	
		for(int i=0;i<a.size();i++){
			for(int j=0;j<b.size();j++){
				if(a[i]==b[j]){
					if(b[j]=='X')y[j]='X';
					else y[j]=num[a[i]-'0'];
				}
			}
		}
		int k=contor(y);
		string w;
		while(pre[op][k]!=-1){
			w=c[vis[op][k]]+w;
			k=pre[op][k];
		}
		cout<<"Case "<<e<<": "<<w.size()<<endl;
		cout<<w<<endl;
	}
}
