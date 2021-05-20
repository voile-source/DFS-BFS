/**
Now an emergent task for you is to open a password lock. The password is consisted of four digits. Each digit is numbered from 1 to 9.
Each time, you can add or minus 1 to any digit. When add 1 to '9', the digit will change to be '1' and when minus 1 to '1', the digit will change to be '9'. You can also exchange the digit with its neighbor. Each action will take one step.

Now your task is to use minimal steps to open the lock.

Note: The leftmost digit is not the neighbor of the rightmost digit.
Input
The input file begins with an integer T, indicating the number of test cases.

Each test case begins with a four digit N, indicating the initial state of the password lock. Then followed a line with anotther four dight M, indicating the password which can open the lock. There is one blank line after each test case.
Output
For each test case, print the minimal steps in one line.
Sample Input
2
1234
2144

1111
9999
Sample Output
2
4

题目大意:对于一个四位数的密码锁，给出三种操作，+1，-1，交换。问最少交换几次能够变成目标状态。

解题思路：bfs对四位数枚举三种操作。判断是否超出边界，交换操作只对前三个数进行操作。
**/

#include<iostream>
#include<queue>
#include<algorithm>
#include<cstring> 
using namespace std;

struct node{
	int num[4];
	int step;
}s,e;
int book[10][10][10][10];

int bfs(node x)
{
	queue<node> Q;
	x.step=0;
	Q.push(x);
	while(!Q.empty()){
		node m=Q.front();
		Q.pop();
		int i;
		for(i=0;i<4;i++){
			if(m.num[i]!=e.num[i])break;
		}
		if(i==4)return m.step;
		for(i=0;i<4;i++){
			for(int j=1;j<=3;j++){
				node p=m;
				if(j==1){
					if(p.num[i]+1!=10)p.num[i]+=1;
					else p.num[i]=1;
				}else if(j==2){
					if(p.num[i]-1!=0)p.num[i]-=1;
					else p.num[i]=9;
				}else{
					if(i!=3)swap(p.num[i],p.num[i+1]);
				}
				int a=p.num[0],b=p.num[1],c=p.num[2],d=p.num[3];
				if(book[a][b][c][d])continue;
				book[a][b][c][d]=1;
				p.step=m.step+1;
				Q.push(p);
			}
		}
	}
}

int main()
{
	int t;
	cin>>t;
	while(t--){
		for(int i=0;i<8;i++){
			char c;
			cin>>c;
			if(i<4)s.num[i]=c-'0';
			else e.num[i-4]=c-'0';
		}
		memset(book,0,sizeof book);
		cout<<bfs(s)<<endl;
	}
}
