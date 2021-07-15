/**
在魔方风靡全球之后不久，Rubik先生发明了它的简化版——魔板。魔板由8个同样大小的方块组成，每个方块颜色均不相同，可用数字1-8分别表示。任一时刻魔板的状态可用方块的颜色序列表示：从魔板的左上角开始，按顺时针方向依次写下各方块的颜色代号，所得到的数字序列即可表示此时魔板的状态。例如，序列(1,2,3,4,5,6,7,8)表示魔板状态为：

1 2 3 4
8 7 6 5

对于魔板，可施加三种不同的操作，具体操作方法如下：

A: 上下两行互换,如上图可变换为状态87654321
B: 每行同时循环右移一格,如上图可变换为41236785
C: 中间4个方块顺时针旋转一格,如上图可变换为17245368

给你魔板的初始状态与目标状态，请给出由初态到目态变换数最少的变换步骤，若有多种变换方案则取字典序最小的那种。
Input
每组测试数据包括两行，分别代表魔板的初态与目态。
Output
对每组测试数据输出满足题意的变换步骤。
Sample Input
12345678
17245368
12345678
82754631
Sample Output
C
AC

解题思路：利用康托展开值去重，然后预处理12345678的所有变换情况的操作数列，然后使用映射的方法，将所有的初态映射成12345678的样子，
之后输出答案即可。

**/

#include<iostream>
#include<string>
#include<cstring>
#include<queue>
#include<map>
#include<algorithm>
using namespace std;
const int max_n=1e5+10;

struct node{
	string s;
	string op;
};


int vis[max_n];
map<int,string> path;
int  fac[] = {1,1,2,6,24,120,720,5040,40320,362880};

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

void bfs()
{
	queue<node> Q;
	node a;
	a.s="12345678";
	a.op="";
	vis[contor(a.s)]=1;
	Q.push(a); 
	node p,q;
	while(!Q.empty()){
		p=Q.front();
		Q.pop();
		for(int i=0;i<3;i++){
			q=p;
			int n=q.s.size();
			if(i==0){
				q.op+='A';
				for(int i=0;i<n/2;i++){
					swap(q.s[i],q.s[n-i-1]);
				}
			}else if(i==1){
				q.op+='B';
				char t=q.s[3];
				for(int i=3;i;i--){
					q.s[i]=q.s[i-1];
				}
				q.s[0]=t;
				t=q.s[4];
				for(int i=4;i<7;i++){
					q.s[i]=q.s[i+1];
				}
				q.s[7]=t;
			}else {
				q.op+='C';
				char t=q.s[6];
				q.s[6]=q.s[5];
				q.s[5]=q.s[2];
				q.s[2]=q.s[1];
				q.s[1]=t;
			} 
			if(vis[contor(q.s)])continue;
			path[contor(q.s)]=q.op;
			vis[contor(q.s)]=1;
			Q.push(q);
		}
	}
}

int main()
{
	bfs();
	string a,b;
	while(cin>>a>>b){
		string c="00000000";
		for(int i=0;i<a.size();i++){
			for(int j=0;j<b.size();j++){
				if(b[j]==a[i]){
					c[j]=i+'1';
					break;
				}
			}
		}
		cout<<path[contor(c)]<<endl;
	}	
} 
