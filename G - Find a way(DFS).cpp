/**
伊菲的家在乡下，而梅基的家在市中心。于是，伊菲和梅基安排在KFC见面。西安有很多KFC，他们想选择一个花费总时间最短的KFC见面。
现在给你一张西安的地图，伊菲和梅基都可以上、下、左、右移动到相邻的地点，每移动一个位置花费11分钟。

Input
输入包含多个测试用例。
每个测试用例包括前两个整数n，m.（2<=n，m<=200）。
接下来的n行，每行包含m个字符。
“Y”表示伊菲的初始位置。
“M”表示梅基初始位置。
“#”死路；
'.'可走的路。
“@” KCF

Output
对于每个测试用例，输出伊菲和梅基花费的最短总时间。总有一家KFC可以让他们见面。

Sample Input
4 4
Y.#@
….
.#..
@..M
4 4
Y.#@
….
.#..
@#.M
5 5
Y..@.
.#…
.#…
@..M.
#…#

Sample Output
66
88
66

题目大意：有两个人都要从自身所在地去往同一个地方（有多个），问去哪个地方能使总计花费时间最少。、

解题思路：两次bfs，把两个人所消耗的时间加起来，然后求值最小的KFC点，最后答案*11。
**/

#include<iostream>
#include<cstring>
#include<string>
#include<queue>
using namespace std;

struct node{
	int x,y,step;
};

string e[210];
int book[210][210];
int v[210][210];
int nx[4][2]={{0,1},{1,0},{0,-1},{-1,0}}; 
int n,m;

void bfs(node a)
{
	a.step=0;
	queue<node> Q;
	Q.push(a);
	node p,q;
	while(!Q.empty()){
		p=Q.front();
		Q.pop();
		q.step=p.step+1;
		for(int i=0;i<4;i++){
			q.x=p.x+nx[i][0];
			q.y=p.y+nx[i][1];
			if(q.x<0||q.y<0||q.x>=n||q.y>=m)continue;
			if(e[q.x][q.y]=='#'||book[q.x][q.y])continue;
			book[q.x][q.y]=1;
			v[q.x][q.y]+=q.step;
			Q.push(q); 
		}
	}
}

int main()
{
	while(cin>>n>>m){
		memset(v,0,sizeof v); 
		for(int i=0;i<n;i++)cin>>e[i];
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				if(e[i][j]=='Y'||e[i][j]=='M'){
					memset(book,0,sizeof book);
					node s;
					s.x=i;
					s.y=j;
					bfs(s); 
				}
			}
		}
		int ans=99999;
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				if(e[i][j]=='@'&&v[i][j]<ans&&v[i][j]){
					ans=v[i][j];
				}
			}
		}
		cout<<ans*11<<endl;
	}
}
