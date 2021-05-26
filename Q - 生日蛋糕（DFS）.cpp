/**
7月17日是Mr.W的生日，ACM-THU为此要制作一个体积为Nπ的M层生日蛋糕，每层都是一个圆柱体。
设从下往上数第i(1 <= i <= M)层蛋糕是半径为Ri, 高度为Hi的圆柱。当i < M时，要求Ri > Ri+1且Hi > Hi+1。
由于要在蛋糕上抹奶油，为尽可能节约经费，我们希望蛋糕外表面（最下一层的下底面除外）的面积Q最小。
令Q = Sπ
请编程对给出的N和M，找出蛋糕的制作方案（适当的Ri和Hi的值），使S最小。
（除Q外，以上所有数据皆为正整数）
Input
有两行，第一行为N（N <= 10000），表示待制作的蛋糕的体积为Nπ；第二行为M(M <= 20)，表示蛋糕的层数为M。
Output
仅一行，是一个正整数S（若无解则S = 0）。
Sample Input
100
2
Sample Output
68
Hint
圆柱公式
体积V = πR2H
侧面积A' = 2πRH
底面积A = πR2

题目大意：搭一个最多20层的从下往上高度和半径递减的圆柱群，问能取得的总体积最小底面圆的面积+每一层的侧面积的最小值

解题思路：DFS枚举状态+剪枝，由于蛋糕的排列满足从下往上严格递减，所以上层面积我们只需要求最底下的圆的面积，然后枚举半径和高。本题的难点主要在于剪枝，直接爆搜会超时。
减去体积》n，面积》ans，剩下的层数的最大体积《n，不满足严格递减序列的状态

**/

#include<iostream>
#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;

long long n,m,ans=2e9;

void dfs(long long r,long long h,long long s,long long v,long long step){

    if(v+(m-step+1)*(r-1)*(r-1)*h<n||v>n||s>ans)return ; 
    if(r<m-step+1||h<m-step+1)return ; 
    if(step==m){
    	if(v==n)ans=min(ans,s);
    	return ;
	}
	for(long long i=r-1;i>0;i--){
		for(long long j=h-1;j>0;j--){
			long long ds=0;
			if(step==0)ds=i*i;
			dfs(i,j,ds+s+2*i*j,v+i*i*j,step+1);
		}
	}
}

long long main(){
    cin>>n>>m;
    dfs(101,10001,0,0,0);
    if(ans==2e9)cout<<-1;
    else cout<<ans;
}

