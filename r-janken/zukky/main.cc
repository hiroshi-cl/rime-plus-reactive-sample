#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
 
const int MAX_N = 12;
int N;
char G[MAX_N][MAX_N];
int bound[MAX_N];
 
 
int select() {
  return lower_bound(bound+1,bound+1+N,1+rand()%bound[N]) - bound;
}
 
int winHand(int tekihand) {
  int res = select();
  for(int i = 1; i <= N; ++i) {
    if(G[i][tekihand] == 'o') {
      return i;
    } else if(G[i][tekihand] == '-') {
      res = i;
    }
  }
  return res;
}
 
int main() {
  cin >> N;
  bound[0] = 0;
  for(int i = 1; i <= N; ++i) {
    bound[i] = bound[i-1];
    for(int j = 1; j <= N; ++j) {
      cin >> G[i][j];
      if(G[i][j] == 'o') {
  bound[i] += 3;
      } else if(G[i][j] == '-') {
  bound[i] += 1;
      }
    }
  }
 
  int prehand = -1;
  int cnt = 0;
  for(int tc = 0; tc < 1000; ++tc) {
    int judge_ai_hand;
    int hand;
    if(cnt > 5) {
      hand = winHand(prehand);
    } else {
      hand = select();
    }
    printf("%d\n", hand); fflush(stdout);
    scanf("%d", &judge_ai_hand);
    if(prehand != judge_ai_hand) {
      prehand = judge_ai_hand;
      cnt = 1;
    } else {
      ++cnt;
    }
  }
  return 0;
}
