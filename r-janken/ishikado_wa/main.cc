#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <cstdio>
using namespace std;
 
int a[1001][1001];
void solve(){
  int N;
  cin>>N;
  for(int i=0;i<N;i++)
    for(int j=0;j<N;j++)
      cin>>a[i][j];
  int maxExp=-1;
  int pos=-1;
  for(int i=0;i<N;i++){
    int exp=0;
    for(int j=0;j<N;j++){
      if(a[i][j]=='o')exp+=3;
      else if(a[i][j]=='-')exp+=1;
    }
    if(maxExp<exp){
      maxExp=exp;
      pos=i;
    }
  }
  int judge_ai_hand;
  for(int i=0;i<1000;i++){
    printf("%d\n",pos+1); fflush(stdout);
    scanf("%d", &judge_ai_hand);
  }
}
int main(){
  solve();
  return 0;
}
