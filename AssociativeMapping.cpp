#include <iostream>
#include <vector>
using namespace std;

struct CacheLine {
    int blockNumber;
    bool valid;
};

int findBlock(vector<CacheLine> &cache, int block){
    for (int i =0; i < cache.size(); i++){
        if (cache[i].valid && cache[i].blockNumber == block)
            return i;
    }
    return -1;
}

int main() {
    int mainCacheSize =4; //main cache lines
    int victimCacheSize =2; //victim cache lines , to reduce conflict misses
    vector<int> memoryAccesses = { 64, 128, 64, 128, 64, 129, 64};

    vector<CacheLine> mainCache(mainCacheSize, {-1, false});
    vector<CacheLine> victimCache(victimCacheSize, {-1, false});

    int hits=0;
    int misses=0;
    int victimHits=0;

    for (int block : memoryAccesses) {
        int idx = findBlock(mainCache, block);
        if (idx != -1 ) { // hit in main cache
            hits++;
            cout << "Block " << block << ": HIT in Main Cache\n";
        } else{ // miss in main cache
            

        }
    }

    return 0;
}