/**
Ignatius再次被魔王抓走了(搞不懂他咋这么讨魔王喜欢)……

这次魔王汲取了上次的教训，把Ignatius关在一个n*m的地牢里，并在地牢的某些地方安装了带锁的门，钥匙藏在地牢另外的某些地方。刚开始Ignatius被关在(sx,sy)的位置，离开地牢的门在(ex,ey)的位置。Ignatius每分钟只能从一个坐标走到相邻四个坐标中的其中一个。魔王每t分钟回地牢视察一次，若发现Ignatius不在原位置便把他拎回去。经过若干次的尝试，Ignatius已画出整个地牢的地图。现在请你帮他计算能否再次成功逃亡。只要在魔王下次视察之前走到出口就算离开地牢，如果魔王回来的时候刚好走到出口或还未到出口都算逃亡失败。
Input
每组测试数据的第一行有三个整数n,m,t(2<=n,m<=20,t>0)。接下来的n行m列为地牢的地图，其中包括:

. 代表路
* 代表墙
@ 代表Ignatius的起始位置
^ 代表地牢的出口
A-J 代表带锁的门,对应的钥匙分别为a-j
a-j 代表钥匙，对应的门分别为A-J

每组测试数据之间有一个空行。
Output
针对每组测试数据，如果可以成功逃亡，请输出需要多少分钟才能离开，如果不能则输出-1。
Sample Input
4 5 17
@A.B.
a*.*.
*..*^
c..b*

4 5 16
@A.B.
a*.*.
*..*^
c..b*
Sample Output
16
-1

解题思路：这题和传统搜索题目的区别就在于有了门和钥匙的设定，那么可以利用二进制的特点，有0和1表示有钥匙和没钥匙的情况，然后根据身上钥匙的情况去判断是否能
通过当前的们，然后就是普通的bfs搜索了。
**/

#include<iostream>
#include<cstring>
#include<queue>
using namespace std;
const int max_n=25;

struct node{
	int x,y;
	int step;
	int key;
}a;

int ne[4][2]={0,1,1,0,0,-1,-1,0};
int vis[1<<11][max_n][max_n];
char mp[max_n][max_n]; 
int n,m,t;

int bfs(node a)
{
	queue<node> Q;
	Q.push(a);
	node p,q;
	while(!Q.empty()){
		p=Q.front();
		Q.pop();
		for(int i=0;i<4;i++){
			q=p;
			q.x+=ne[i][0];
			q.y+=ne[i][1];
			if(q.x<0||q.x>=n||q.y<0||q.y>=m)continue;
			if(mp[q.x][q.y]=='*')continue;
			if(q.step>=t)return -1;
			if(mp[q.x][q.y]>='a'&&mp[q.x][q.y]<='j') {
				q.key|=(1<<(mp[q.x][q.y]-'a'));
			}
			if(mp[q.x][q.y]>='A'&&mp[q.x][q.y]<='J') {
				if(!(q.key&(1<<(mp[q.x][q.y]-'A'))))continue;
			}
			if(vis[q.key][q.x][q.y])continue;
			vis[q.key][q.x][q.y]=1;
			q.step++;
			if(mp[q.x][q.y]=='^'){
				if(q.step>=t)return -1;
				return q.step;
			} 
			Q.push(q);
		}
	}
	return -1;
}

int main()
{
	while(cin>>n>>m>>t){
		memset(vis,0,sizeof vis);
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				cin>>mp[i][j];
				if(mp[i][j]=='@'){
					a.x=i;
					a.y=j;
					a.step=0;
					a.key=0;
				}
			}
		}
		cout<<bfs(a)<<endl;
	}	
}
