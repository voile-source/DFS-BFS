/*
农夫约翰知道，一头知识上满意的母牛是一头快乐的母牛，它将提供更多的牛奶。他为母牛安排了脑力活动，他们在其中操纵M × N 网格（1≤ M ≤15； 1≤ N ≤15）个正方形瓷砖，每个瓷砖的一面都涂成黑色，
另一面则涂成白色。

正如人们所猜测的那样，当翻转单个白色瓷砖时，它会改变变黑翻转单个黑色图块时，它会变为白色。母牛在翻转砖块时会得到奖励，因此每块砖块的白色侧面都朝上。
但是，母牛的蹄子相当大，当他们尝试翻转特定的砖块时，它们也会翻转所有相邻的砖块（与翻转后的砖块共享整个边缘的砖块）。由于翻转很累，奶牛希望尽量减少必须做的翻转次数。

帮助母牛确定所需的最小翻转次数，并确定要达到最小翻转次数的位置。如果有多种方法可以以最少的翻转次数来完成任务，则当将其视为字符串时，以输出中词典顺序最少的方式返回。
如果无法完成任务，请用“ IMPOSSIBLE”一词打印一行。

Input
第1行：两个以空格分隔的整数： M 和 N
第2 .. M +1行：第 i +1行描述了网格中第i行（ N 以空格分隔的整数，黑色为1，白色为0。
Output
第1 .. M 行：每行包含 N 个以空格分隔的整数，每个整数指定翻转该特定位置的次数。
Sample Input
4 4
1 0 0 1
0 1 1 0
0 1 1 0
1 0 0 1
Sample Output
0 0 0 0
1 0 0 1
1 0 0 1
0 0 0 0

题目大意:给出一个只包含0和1的矩形方阵，方阵中的每一个数都可以翻转（例如0变成1,1变成0），当某一个数翻转后，
它周围（上下左右）的数也会随之翻转，题目要我们求出将整个矩阵都变为0的最小翻转次数。

解题思路：因为每翻转一个数都会改变其周围数的状态，所以每一层的状态都是有关联的，所以我们可以从第一层开始，
一层一层的往下推，将前n-1行都变成0，然后判断最后一行是否全为0，如果是的话，那么答案就是本次的翻转次数。然
后，我们就可以采用二进制枚举的方法，从1一直枚举到2^m-1，最后dfs求出答案。

*/
#include<iostream>
#include<cstring>
using namespace std;
const int INF=0x3f3f3f3f;

int mp[20][20];
int temp[20][20];
int an[20][20];
int ne[5][2]={0,1,1,0,0,-1,-1,0,0,0};
int cnt=INF;
int n,m;

int check(int x,int y)
{
	int k=mp[x][y];
	for(int i=0;i<5;i++){
		int nx=x+ne[i][0];
		int ny=y+ne[i][1];
		if(nx<0||nx>n||ny<0||ny>m)continue;
		k+=temp[nx][ny];
	}
	//cout<<k<<endl;
	return k&1;
}

void dfs(int x)
{
	memset(temp,0,sizeof(temp));
	for(int i=0;i<m;i++){
		temp[0][m-i-1]=(x>>i)&1; 
	}
	for(int i=1;i<n;i++){
		for(int j=0;j<m;j++){
			//cout<<check(i-1,j)<<endl;
			if(check(i-1,j))temp[i][j]=1;
		}
	}

	for(int i=0;i<n;i++){
		if(check(n-1,i))return ; 
	}
	int tot=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			tot+=temp[i][j];
		} 
	}
	if(tot<cnt){
		cnt=tot;
		memcpy(an,temp,sizeof(temp));
	}
} 

int main()
{
	cin>>n>>m;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cin>>mp[i][j];
		}
	}
	for(int i=0;i<(1<<m);i++){
		dfs(i);
	}
	if(cnt==INF){
		cout<<"IMPOSSIBLE";
	}else {
		for(int i=0;i<n;i++,cout<<endl){
			for(int j=0;j<m;j++){
				cout<<an[i][j]<<" ";
			}
		}	
	}
