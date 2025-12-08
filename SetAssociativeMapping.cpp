#include <iostream>
#include<vector>
using namespace std;

struct CacheLine{
    int blockNumber;
    bool valid;
    int lastUsed; // this is for actually LRU replacement
};

int main () {
    int totallines = 8;        // what we state it as m = k.v
    int ways= 2;               // associativity or what we were calling k way
    int numSets = totallines/ways; //v = m /k 

    vector<int> memoryAccesses = { 64, 128, 64, 128, 64, 129, 64};

    vector<vector<CacheLine>> cache(numSets, vector<CacheLine>(ways, {-1, false, 0}));
    
    int hits =0;
    int misses =0;
    int conflictMisses =0;      // i think this will to illustrate its main advantage over direct mapping
    int timestamp =0;           // since LRU replacement policy needs to know when each block was last accessed

    cout << "2-Ways Set Associativity Cache Simulation\n\n ";

    
}
