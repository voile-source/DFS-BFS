/**
可怜的fish在一次次被魔王掳走一次次被勇者们救回来之后，而今，不幸的他再一次面临生命的考验。魔王已经发出消息说将在T时刻吃掉fish，因为他听信谣言说吃fish的肉也能长生不老。年迈的国王正是心急如焚，告招天下勇者来拯救fish。不过fish早已习以为常，他深信智勇的勇者肯定能将他救出。
现据密探所报，fish被关在一个两层的迷宫里，迷宫的入口是S（0，0，0），fish的位置用P表示，时空传输机用# 表示，墙用*表示，平地用.表示。勇者们一进入时空传输机就会被转到另一层的相对位置，但如果被转到的位置是墙的话，那勇者们就会被撞死。勇者们在一层中只能前后左右移动，每移动一格花1时刻。层间的移动只能通过时空传输机，且不需要任何时间。
Input
输入的第一行C表示共有C个测试数据，每个测试数据的前一行有三个整数N，M，T。 N，M迷宫的大小N* M（1 <= N,M <=10) 。T如上所意。接下去的前N* M表示迷宫的第一层的布置情况，后N* M表示迷宫第二层的布置情况。
Output
如果勇者们能够在T时刻能找到fish就输出“YES”，否则输出“NO”。
Sample Input
1
5 5 14
S*#*.
.#...
.....
****.
...#.

..*.P
#.*..
***..
...*.
*.#..
Sample Output
YES

题目大意：走迷宫的升级版，加了一个传送阵的操作，问能否在限定时间内走到目标处。

解题思路：预处理数据，当不同层的同一位置同时为‘#’时，就会不断反复横跳，所以要避免这种情况，将该位置改为‘*’。然后就是bfs搜索，判断能否在限定时间内搜索到目标。
**/

#include<iostream>
#include<cstring>
#include<string>
#include<queue>
using namespace std;

struct node{
	int r,x,y;
	int step;
}e;

int book[2][15][15];
int nx[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
string mp[2][15];
int n,m,time;

int dfs(node x)
{
	queue<node> Q;
	Q.push(x);
	book[x.r][x.x][x.y]=1;
	while(!Q.empty()){
		node p=Q.front();
		Q.pop();
		if(p.step>time)continue;
		if(p.r==e.r&&p.x==e.x&&p.y==e.y){
			//cout<<p.step<<endl;
		return 1;}
		for(int i=0;i<4;i++){
			node d=p;
			d.x+=nx[i][0];
			d.y+=nx[i][1];
			if(d.x<0||d.y<0||d.x>=n||d.y>=m)continue;
			if(book[d.r][d.x][d.y]||mp[d.r][d.x][d.y]=='*')continue;
			if(mp[d.r][d.x][d.y]=='#'){
				if(mp[d.r^1][d.x][d.y]=='*')continue;
					d.r^=1;
					d.step=p.step+1;
					Q.push(d);
			}else{
				d.step=p.step+1;
				book[d.r][d.x][d.y]=1;
				Q.push(d);
			}
		}
	}	
	return 0;
}

int main()
{
	int t;
	cin>>t;
	while(t--){
		cin>>n>>m>>time;
		for(int i=0;i<2;i++){
			for(int j=0;j<n;j++){
				cin>>mp[i][j];
			}
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				if(mp[0][i][j]=='P'){
					e=(node){0,i,j,0};
				}
				if(mp[1][i][j]=='P'){
					e=(node){1,i,j,0};
				}
				if(mp[0][i][j]==mp[1][i][j]&&mp[0][i][j]=='#'){
					mp[0][i][j]=mp[1][i][j]='*';
				}
			}
		}
		memset(book,0,sizeof book);
		if(dfs((node){0,0,0,0}))cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
}
