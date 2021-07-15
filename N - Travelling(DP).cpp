/**
After coding so many days,Mr Acmer wants to have a good rest.So travelling is the best choice!He has decided to visit n cities(he insists on seeing all the cities!And he does not mind which city being his start station because superman can bring him to any city at first but only once.), and of course there are m roads here,following a fee as usual.But Mr Acmer gets bored so easily that he doesn't want to visit a city more than twice!And he is so mean that he wants to minimize the total fee!He is lazy you see.So he turns to you for help.
题意：给你一个图，从一个点到另一个点有路，需要花费。起点是任意的，要求每个点最多走两次，把所有的点遍历完一遍，费用最小
Input
There are several test cases,the first line is two intergers n(1<=n<=10) and m,which means he needs to visit n cities and there are m roads he can choose,then m lines follow,each line will include three intergers a,b and c(1<=a,b<=n),means there is a road between a and b and the cost is of course c.Input to the End Of File.
Output
Output the minimum fee that he should pay,or -1 if he can't find such a route.
Sample Input
2 1
1 2 100
3 2
1 2 40
2 3 50
3 3
1 2 3
1 3 4
2 3 10
Sample Output
100
90
7 

解题思路：由于每个点可以走两次，那么就可以使用三进制的方式，表示每个点的状态，首先预处理出每种状态的三进制数，然后dp求出最小花费。
**/
#include<iostream>
#include<cstring>
using namespace std;
const int INF=999999999;
const int max_n=600001;

int three[15];
int digit[max_n][15];
int dp[max_n][15];
int e[15][15];
int n,m;

void init()
{
	three[0]=1;
	for(int i=1;i<=10;i++){
		three[i]=three[i-1]*3;
	} 
	for(int i=0;i<three[10];i++){
		int temp=i;
		for(int j=0;j<10;j++){
			digit[i][j]=temp%3;
			temp/=3;
		}
	}
}

int main()
{
	init(); 
	while(cin>>n>>m){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				e[i][j]=INF;
			}
		}
		for(int i=0;i<three[n];i++){
			for(int j=0;j<n;j++){
				dp[i][j]=INF;
			}
		}
		for(int i=1;i<=m;i++){
			int a,b,c;
			cin>>a>>b>>c;
			if(c<e[a-1][b-1])e[a-1][b-1]=e[b-1][a-1]=c;
		}
		for(int i=0;i<n;i++){
			dp[three[i]][i]=0;
		}
		int ans=INF;
		for(int j=0;j<three[n];j++){
			int flag=1;
			for(int i=0;i<n;i++){
				if(digit[j][i]==0)flag=0;
				if(dp[j][i]!=INF){
					for(int k=0;k<n;k++){
						if(e[i][k]!=INF&&digit[j][k]!=2){
							dp[j+three[k]][k]=min(dp[j][i]+e[i][k],dp[j+three[k]][k]);
						}
					}
				}
			}
			if(flag){
				for(int i=0;i<n;i++){
					ans=min(ans,dp[j][i]);
				}
			}
		}
		//cout<<ans<<endl;
		if(ans>=INF)cout<<-1<<endl;
		else cout<<ans<<endl;
	}	
} 
