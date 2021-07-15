/**
The students of the HEU are maneuvering for their military training.
The red army and the blue army are at war today. The blue army finds that Little A is the spy of the red army, so Little A has to escape from the headquarters of the blue army to that of the red army. The battle field is a rectangle of size m*n, and the headquarters of the blue army and the red army are placed at (0, 0) and (m, n), respectively, which means that Little A will go from (0, 0) to (m, n). The picture below denotes the shape of the battle field and the notation of directions that we will use later.




The blue army is eager to revenge, so it tries its best to kill Little A during his escape. The blue army places many castles, which will shoot to a fixed direction periodically. It costs Little A one unit of energy per second, whether he moves or not. If he uses up all his energy or gets shot at sometime, then he fails. Little A can move north, south, east or west, one unit per second. Note he may stay at times in order not to be shot.
To simplify the problem, let’s assume that Little A cannot stop in the middle of a second. He will neither get shot nor block the bullet during his move, which means that a bullet can only kill Little A at positions with integer coordinates. Consider the example below. The bullet moves from (0, 3) to (0, 0) at the speed of 3 units per second, and Little A moves from (0, 0) to (0, 1) at the speed of 1 unit per second. Then Little A is not killed. But if the bullet moves 2 units per second in the above example, Little A will be killed at (0, 1).
Now, please tell Little A whether he can escape.
Input
For every test case, the first line has four integers, m, n, k and d (2<=m, n<=100, 0<=k<=100, m+ n<=d<=1000). m and n are the size of the battle ground, k is the number of castles and d is the units of energy Little A initially has. The next k lines describe the castles each. Each line contains a character c and four integers, t, v, x and y. Here c is ‘N’, ‘S’, ‘E’ or ‘W’ giving the direction to which the castle shoots, t is the period, v is the velocity of the bullets shot (i.e. units passed per second), and (x, y) is the location of the castle. Here we suppose that if a castle is shot by other castles, it will block others’ shots but will NOT be destroyed. And two bullets will pass each other without affecting their directions and velocities.
All castles begin to shoot when Little A starts to escape.
Proceed to the end of file.
Output
If Little A can escape, print the minimum time required in seconds on a single line. Otherwise print “Bad luck!” without quotes.
Sample Input
4 4 3 10
N 1 1 1 1
W 1 1 3 2
W 2 1 2 4
4 4 3 10
N 1 1 1 1
W 1 1 3 2
W 1 1 2 4
Sample Output
9
Bad luck!

题目大意:一张M*N的地图上有k座城堡，每座城堡都会向固定的方向以一定的频率和速度发射子弹，当子弹碰到另一座城堡时，子弹会被挡掉（子弹不会摧毁城堡），现在有个人
从（0，0）处出发，只能上下左右移动加上不动，问他能否在d时间内不死走到（m,n）处，求出最短的时间t；

解题思路：首先将某一时候，在什么位置是会被子弹击中的情况和城堡的位置预处理出来，然后我们bfs搜四个方向+原地不动，使用一个三维vis数组标记某一时间的点是否有走过，
最后判断是否有超过时间就行了。

/**
#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;

struct node{
	char dir;
	int t,v;
	int x,y;
	int step;
}w[110];

bool e[110][110];
bool vis[1010][110][110];
bool bot[1010][110][110];
int ne[5][2]={0,1,1,0,0,-1,-1,0,0,0};
int n,m,k,d;

void init()
{
	for(int i=1;i<=k;i++){
		int nx=w[i].x;
		int ny=w[i].y;
		for(int j=0;j<=d;j+=w[i].t){
			for(int k=1;;k++){
				int x=nx;
				int y=ny;
				if(w[i].dir=='E')y+=k;
				else if(w[i].dir=='S')x+=k;
				else if(w[i].dir=='W')y-=k;
				else x-=k;
				if(x<0||y<0||x>n||y>m||e[x][y])break;
				if(k%w[i].v==0)bot[j+k/w[i].v][x][y]=1;	
			}
		}
	}
}

int bfs(node a)
{
	queue<node> Q;
	Q.push(a);
	vis[0][0][0]=1;
	node p,q;	
	while(!Q.empty()){
		p=Q.front();
		Q.pop();
		if(p.step>d)return -1;
		if(p.x==n&&p.y==m)return p.step;
		for(int i=0;i<5;i++){
			q=p;
			q.x+=ne[i][0];
			q.y+=ne[i][1];
			q.step++;
			if(q.x<0||q.y<0||q.x>n||q.y>m||e[q.x][q.y]||vis[q.step][q.x][q.y]||bot[q.step][q.x][q.y])continue; 
			//cout<<q.step<<' '<<q.x<<' '<<q.y<<endl;
			vis[q.step][q.x][q.y]=1;
			Q.push(q);
		}
	}
	return -1; 
}

int main()
{
	while(cin>>n>>m>>k>>d){
		memset(e,0,sizeof e);
		memset(vis,0,sizeof vis);
		memset(bot,0,sizeof bot);
		for(int i=1;i<=k;i++){
			char c;
			int a,b,x,y;
			cin>>c>>a>>b>>x>>y;
			w[i]=(node){c,a,b,x,y,0};
			e[x][y]=1;
		}
		init();
		int t=bfs((node){0,0,0,0,0,0});
		if(t==-1)cout<<"Bad luck!"<<endl;
		else cout<<t<<endl;
	}	
} 



