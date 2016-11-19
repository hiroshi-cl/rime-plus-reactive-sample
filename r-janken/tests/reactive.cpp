
#include <cstring>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>
#include "reactive.hpp"
#include "testlib.h"

using namespace std;

#define FOR(it, c) for (__typeof((c).begin())it = (c).begin(); it != (c).end(); it++)

const int gameNum = 1000;
const int threshold = 350;

int n;
vector<string> table;

class baseAI {
public: 
  virtual int hand() = 0;
};

// If you want to change the AI,
// you'll write an AI code, which must inherit from baseAI.
class AI : public baseAI {
private:
  int type;
  int index;
  int cnt;
  int times;
  vector<int> killStrongest;
  vector<int> strongest;
  const static int seed = 10000;
  int randHand() { return rnd.next(seed) % n + 1; }

  int rotateSelect(vector<int> v) { 
    if( v.size() == 0 )
      return randHand();
    
    return v[index++ % v.size()] + 1; 
  }

  int rotateHand() { return (index++ % n) + 1; }
  int rotate3Hand() { 
         if(times % cnt == cnt -1)
	   index++;
	 return index % n + 1; 
      }
  int killStrongestHand() { return rotateSelect(killStrongest); }
  int strongestHand() { return rotateSelect(strongest); }
  AI () { }

public:

  AI (int _type, int offset = 0) : type(_type) {
    index = offset;
    cnt = 1000/n;
    times = 0;

    int d[n];
    memset(d,0,sizeof(d));


    for (int i = 0; i < table.size(); i++) {
      for(int j = i + 1; j < table.size(); j++) {
	if( table[i][j] == 'o' )
	  d[i]++;
	else
	  d[j]++;
      }
    }
    
    int maxd = *max_element(d,d+n);
    for (int i = 0; i < n; i++) {
      if ( d[i] == maxd )
	strongest.push_back(i);
    }


      for (int i = 0; i < n; i++) {
	bool win = true;
	FOR (it,strongest) {
	  if ( table[i][*it] != 'o' )
	    win = false;
	}
	if( win )
	  killStrongest.push_back(i);
      }

  }

  int hand() { 
    times++;
    int thisHand = 0;
    if (type == 0 ) {
      thisHand = strongestHand();
    } else if (type == 1) {
      thisHand = killStrongestHand();
    } else if (type == 2) {
      thisHand = rotateHand();
    } else if (type == 3) {
      thisHand = rotate3Hand();
    }
    return thisHand;
  }
};


void strip(string& s) {
    while(s.size() > 0 && s[s.size()-1] == '\n' || s[s.size()-1] == '\r')
        s = s.substr(0, s.size()-1);
}

bool isIn(int tmp){
  return 1 <= tmp && tmp <= n;
}

string interaction(baseAI* ai) {
  
  int gain = 0;
  for(int i = 0; i < gameNum; i++){

    // get rivalHand
    string str = reactive_read();
    strip(str);
    if( str.empty() )
      return "Wrong Answer: query is empty.";
    int rivalHand = atoi(str.c_str());
    if( !isIn(rivalHand) )
      return "Wrong Answer: query does not belong to [1,n]. ";

    // get myHand
    int myHand = ai->hand();    
    assert( isIn(myHand) );

    // calc points
    char thisResult = table[rivalHand-1][myHand-1];


    if ( thisResult == 'o' ) {
      gain += 3;
    }
    else if (thisResult == '-' ) {
      gain++;
    }

    // send myHand
    reactive_write( vtos(myHand) + "\n");



  }
  
  if( gain < threshold )
    return  "Wrong Answer:The point you got is less than 350.";

  return "AC";
}

int main(int argc, char** argv){

  reactive_start(argv[1]);

  // get input
  int type,offset;
  scanf("%d %d\n",&type,&offset);
  scanf("%d\n",&n);
  table.resize(n);
  for (int i = 0; i < n; i++) {
    getline(cin,table[i]);
  }

  // send input
  reactive_write( vtos(n) + "\n");
  for (int i = 0; i < n; i++) {
    reactive_write(table[i] + "\n");
  }

  // If you want to change AI, you'll have to change this code.
  baseAI* ai = new AI(type,offset);
  cout << interaction(ai) << endl;
  delete ai;

  reactive_end();
}
