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

    for(int block : memoryAccesses){
        int setIndex =  block % numSets;  // here basically it inherits the technique of direct mapping
        timestamp++;

        cout << " Accessing Block: " << block
            << " ->Set: "<<setIndex << " ";

        bool hit = false;
        int  emptyWay = -1;
        int lruWay =0;
        int minUsed = cache[setIndex][0].lastUsed;

        for (int w =0; w<ways;w++){
            if (cache[setIndex][w].valid && cache[setIndex][w].blockNumber==block){
                // if the tag matches , i mean hit
                hit = true;
                hits++;
                cache[setIndex][w].lastUsed = timestamp;
                cout << "(HIT in way " << w <<" )\n";
                break;
            }
            if (!cache[setIndex][w].valid){
                emptyWay =w;

            } if (cache[setIndex][w].lastUsed<minUsed){
                minUsed = cache[setIndex][w].lastUsed;
                lruWay = w;
            }
        }


        if (!hit){
            misses ++;
            if (emptyWay != -1){
                cout << "(MISS - Empty Way) \n";
                cache[setIndex][emptyWay] = {block, true, timestamp};

            } else {
                conflictMisses++;
                cout << "(CONFLICT MISS - Evict Block "
                    << cache[setIndex][lruWay].blockNumber
                    <<" from way " << lruWay << ")\n";

                cache[setIndex][lruWay] ={block, true, timestamp};
        
            }
        }

    }

    cout << "\n Results \n";
    cout << "Hits: "<< hits<< endl;
    cout << "Misses: "<< misses<< endl;
    cout << "Conflict Misses: "<< conflictMisses<< endl; // can see here the reduction of this
    return 0;
}
