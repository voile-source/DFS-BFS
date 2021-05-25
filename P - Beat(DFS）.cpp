/**
Zty is a man that always full of enthusiasm. He wants to solve every kind of difficulty ACM problem in the world. And he has a habit that he does not like to solve
a problem that is easy than problem he had solved. Now yifenfei give him n difficulty problems, and tell him their relative time to solve it after solving the other one.
You should help zty to find a order of solving problems to solve more difficulty problem.
You may sure zty first solve the problem 0 by costing 0 minute. Zty always choose cost more or equal time’s problem to solve.
Input
The input contains multiple test cases.
Each test case include, first one integer n ( 2< n < 15).express the number of problem.
Than n lines, each line include n integer Tij ( 0<=Tij<10), the i’s row and j’s col integer Tij express after solving the problem i, will cost Tij minute to solve the problem j.
Output
For each test case output the maximum number of problem zty can solved.


Sample Input
3
0 0 0
1 0 1
1 0 0
3
0 2 2
1 0 1
1 1 0
5
0 1 2 3 1
0 0 2 3 1
0 0 0 3 1
0 0 0 0 2
0 0 0 0 0
Sample Output
3
2
4

  
Hint
Hint: sample one, as we know zty always solve problem 0 by costing 0 minute. 
So after solving problem 0, he can choose problem 1 and problem 2, because T01 >=0 and T02>=0. 
But if zty chooses to solve problem 1, he can not solve problem 2, because T12 < T01. 
So zty can choose solve the problem 2 second, than solve the problem 1.  

题目大意： e[i][j]代表的是在解决第i道问题后，解决第j道问题所需要的时间，假设当前解决了e[i][j]问题，那么当要解决e[j][k]问题时,e[j][k]必须>=e[i][j];

解题思路：DFS全搜一遍，如果当前做出的题数大于最大题数，更新最大值。（就是一道普通的搜索题，当初题目看错意思了。。。。。）
**/

#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

int e[20][20];
int book[20];
int ans,n;

void dfs(int cnt,int x,int s)
{
	ans=max(ans,cnt);
	book[x]=1;
    for(int i=0;i<n;i++){
    	if(book[i])continue;
    	if(e[x][i]>=s)book[i]=1,dfs(cnt+1,i,e[x][i]);
	}
	book[x]=0;
}

int main()
{
	while(cin>>n){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				cin>>e[i][j];
			}
		}
		memset(book,0,sizeof book);
		ans=1;
		dfs(1,0,0);
		cout<<ans<<endl;
	}
} 
