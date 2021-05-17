/**
在第一次植物僵尸世界大战中，植物国的黑玫瑰王子使用了植物国的超超超超级无敌禁术-----”BUG”,开启了异次元的大门，在一位超超超超...级**的指挥官”辅助器”带领下，打败了僵尸王国，但是也因此植物国大伤元气，无法再得到异次元的帮助。 过了10000年后，僵尸国王子为了国家的荣誉和发扬祖先的”诺克萨斯”精神，打算采取”闪电战”战术，一举歼灭植物国的战略要塞，吹起第二次植物僵尸世界大战的号角，但是僵尸王子需要知道植物国现在有几个战略要塞，才能采取进一步措施，于是开始研究植物国的军事图。
因为僵尸国卫星技术先进，该军事图十分清楚明了，是一个二维的电子网格图，图中只有黑色和白色，只要图中的白色方块外一圈的八个方块中有白色方块，说明它们属于同一个战略要塞。
Input
多组输入（m = 0结束输入）。
军事图是m*n的二维图，图中”@”表示白色，”*”表示黑色。

第一行包含m,n（1<=n,m<=100）,
接下来m行，每行n个字符。

Output
对于每组输入，输出植物国的战略要塞数量。
Sample Input
1 1
*
3 5
*@*@*
**@**
*@*@*
1 8
@@****@*
5 5
****@
*@@*@
*@**@
@@@*@
@@**@
0 0 
Sample Output
0
1
2
2

解题思路：BFS广搜八个方向，找到一个放入队列中，并把它变成‘*’,最后统计次数;
**/

#include<iostream>
#include<string>
#include<cstring>
#include<queue>
using namespace std;

char s[110][110];
int nx[8]={0,1,1,1,0,-1,-1,-1};
int ny[8]={1,1,0,-1,-1,-1,0,1};
int n,m;
int ans;

struct node{
	char a,b;
};
queue<node> Q;

void bfs(int x,int y)
{
	ans++;
	s[x][y]='*'; 
	Q.push(node{x,y});
	while(!Q.empty()){
		node p=Q.front();
		Q.pop();
		for(int i=0;i<8;i++){
			node d={nx[i]+p.a,ny[i]+p.b};
			int l=d.a,r=d.b;
			if(l<0||r<0||l>=n||r>=m)continue;
			if(s[l][r]=='@')Q.push(d),s[d.a][d.b]='*';
		} 
	}
}

int main()
{
	while(cin>>n>>m&&n&&m){
		ans=0;
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++)cin>>s[i][j];
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				if(s[i][j]=='@')bfs(i,j);
			}
		}
		cout<<ans<<endl;
	}
 } 
