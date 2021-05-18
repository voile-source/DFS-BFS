/**
还记得2020年招新赛中“编织字符串”这一道题吗？
tls在ac完以后想出了一个更有趣的问题，具体是这样的：
给定两个长度均为len的字符串s1、s2和一个长度为len*2的字符串s，
每一次我们按照编织字符串的操作将s1和s2拼接起来（注意这里s2先拼接，具体请看样例），得到长度为len*2的字符串s'
然后令s1为s'的前一半，s2为s'的后一半，反复以上操作。
若在某一次中s'和s相等则结束循环。
假设有s1="JNU",s2="ACM",s="NAMJUC"
第一次操作后得到s'="AJCNMU"，与s不相等。
令s1="AJC",s2="NMU"
第二次操作后得到s'="NAMJUC"，与s相等，结束循环。
输出操作次数为2
Input
第一行一个整数T(1≤T≤1000)，代表测试数据组个数。
对于每组数据，第一行为len(1≤len≤100)，第二行为字符串s1，第三行为字符串s2，第四行为字符串s。
输入保证s1和s2长度均为len，s长度为len*2
Output
对每一组数据，输出数据组编号和答案。
如果无论经过多少次操作也无法结束循环，答案输出-1
Sample Input
2
3
JNU
ACM
NAMJUC
3
JNU
ACM
ACMJNU
Sample Output
1 2
2 -1

题目大意：假设字符串为一副扑克牌，问把扑克牌对半洗牌多少次后能够还原为最初组合

解题思路：map存储已经出现过的排列，然后每次将字符串对叉，如果叉出来的字符串已经存在，即不可达。否则，则搜出答案。
/**

#include<iostream>
#include<string>
#include<map>
using namespace std;

int main()
{
	int t;
	cin>>t;
	for(int k=1;k<=t;k++){
		map<string,int> Q;
		int n;
		cin>>n; 
		string a,b,s;
		cin>>b>>a>>s;
		int flag=0,ans=1;
		while(1){
			string s1;
			for(int i=0;i<n;i++){
				s1+=a[i];
				s1+=b[i]; 
			}
			if(s1==s){
				flag=1;
				break;
			}
			if(Q.find(s1)!=Q.end())break;
			else Q[s1]=0;
			for(int i=0;i<n;i++)b[i]=s1[i],a[i]=s1[i+n];
			ans++;
		}
		cout<<k<<' ';
		if(flag)cout<<ans<<endl;
		else cout<<-1<<endl;
	}
}
