/**
小明给你两个容器，分别能装下A升水和B升水，并且可以进行以下操作
FILL(i)        将第i个容器从水龙头里装满(1 ≤ i ≤ 2);
DROP(i)        将第i个容器抽干
POUR(i,j)      将第i个容器里的水倒入第j个容器（这次操作结束后产生两种结果，一是第j个容器倒满并且第i个容器依旧有剩余，二是第i个容器里的水全部倒入j中，第i个容器为空）
现在要求你写一个程序，来找出能使其中任何一个容器里的水恰好有C升，找出最少操作数并给出操作过程
Input
有且只有一行，包含3个数A,B,C（1<=A,B<=100,C<=max(A,B)）

Output
第一行包含一个数表示最小操作数K
随后K行每行给出一次具体操作，如果有多种答案符合最小操作数，输出他们中的任意一种操作过程，如果你不能使两个容器中的任意一个满足恰好C升的话，输出“impossible”
Sample Input
3 5 4
Sample Output
6
FILL(2)
POUR(2,1)
DROP(1)
POUR(2,1)
FILL(2)
POUR(2,1)

题目大意：给出3种倒水的操作，和三个容量，问最少经过几次操作后，能够到达目标状态。

解题思路：BFS搜索六种状态，并记录路径。
**/

#include<iostream>
#include<queue>
using namespace std;

struct node{
	int x,y;
	int step;
	int path[1010];
};
int a,b,c;
queue<node> Q;
int book[110][110];

void print(node p)
{
	cout<<p.step<<endl;
	for(int i=1;i<=p.step;i++){
		switch(p.path[i]){
			case 1:cout<<"FILL(1)"<<endl;break;
			case 2:cout<<"FILL(2)"<<endl;break;
			case 3:cout<<"DROP(1)"<<endl;break;
			case 4:cout<<"DROP(2)"<<endl;break;
			case 5:cout<<"POUR(1,2)"<<endl;break;
			default:cout<<"POUR(2,1)"<<endl; 
		}
	}
}

bool dfs()
{
	node e;
	e.x=e.y=e.step=0;
	book[0][0]=1;
	Q.push(e);
	while(!Q.empty()){
		node p=Q.front();
		Q.pop();
		if(p.x==c||p.y==c){
			print(p);
			return 0;
		}
		for(int i=1;i<=6;i++){
			node r=p;
			if(i==1)r.x=a;
			else if(i==2)r.y=b;
			else if(i==3)r.x=0;
			else if(i==4)r.y=0;
			else if(i==5){
				int s=r.x+r.y;
				if(s<=b)r.x=0,r.y=s;
				else r.x=s-b,r.y=b;
			}else{
				int s=r.x+r.y;
				if(s<=a)r.x=s,r.y=0;
				else r.x=a,r.y=s-a;
			}
			if(!book[r.x][r.y]){
				book[r.x][r.y]=1;
				r.step=p.step+1;
				r.path[r.step]=i;
				Q.push(r);
			}
		}
	}
	return 1;
}

int main()
{
	cin>>a>>b>>c;
	int w=dfs();
	if(w)cout<<"impossible";
}


