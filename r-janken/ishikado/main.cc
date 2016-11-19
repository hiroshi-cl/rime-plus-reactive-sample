#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <cstdio>
using namespace std;
 
typedef long long ll;
 
ll make_rand(){
  static ll x=123456789;
  static ll y=362436069;
  static ll z=521288629;
  static ll w=88675123;
  ll t;
  t=x^(x<<11);
  x=y;y=z;z=w;
  return w=(w^(w>>19))^(t^(t>>8));
}
 
char a[1001][1001];
void solve(){
  int N;
  cin>>N;
  for(int i=0;i<N;i++)
    for(int j=0;j<N;j++)
      cin>>a[i][j];
  int maxExp=-1;
  int pos=-1;
  int allone=-1;
  vector<int> poss;
  for(int i=0;i<N;i++){
    int exp=0;
    int one=0;
    for(int j=0;j<N;j++){
      if(a[i][j]=='o')exp+=3;
      else if(a[i][j]=='-'){
        one++;
        exp+=1;
      }
    }
    if(maxExp<exp){
      maxExp=exp;
      pos=i;
      poss.clear();
      poss.push_back(i+1);
    }
    else if(maxExp==exp)
      poss.push_back(i+1);
     if(N==one)allone=i+1;
  }
  pos++;
  int judge_ai_hand;
  int sum=0;
  // もっとも期待値が高いものに対してもっとも勝てそうなものを選ぶ
  vector<int> ophands;
  int maxexp=-1;
  for(int i=0;i<N;i++){
    int exp=0;
    for(int j=0;j<poss.size();j++){
      if(a[i][poss[j]-1]=='o')exp+=3;
      else if(a[i][poss[j]-1]=='-')exp+=1;
    }
    if(maxexp<exp){
      maxexp=exp;
      ophands.clear();
      ophands.push_back(i+1);
    }
    else if(maxexp==exp)
      ophands.push_back(i+1);
  }
  for(int i=0;i<1000;i++){
    //int hand=pos;
    //int hand=poss[make_rand()%(int)poss.size()];
    int hand=ophands[make_rand()%(int)ophands.size()];
    if(make_rand()%2)
      hand=poss[make_rand()%(int)poss.size()];
    //if(allone!=-1&&(1000-i)+sum>=350)
    //  hand=allone;
    printf("%d\n",hand); fflush(stdout);
    scanf("%d", &judge_ai_hand);
    if(a[pos-1][judge_ai_hand-1]=='o')sum+=3;
    else if(a[pos-1][judge_ai_hand-1]=='-')sum+=1;
  }
}
int main(){
  solve();
  return 0;
}
