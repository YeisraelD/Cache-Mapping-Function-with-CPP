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
        if (idx != -1 ) { 
            // hit in main cache
            hits++;
            cout << "Block " << block << ": HIT in Main Cache\n";
        } else{ 
            // miss in main cache
            int victimIdx = findBlock(victimCache, block);

            if (victimIdx != -1) {
                // hit in victim cache , so we can swap it now with main cache
                victimHits++;
                cout << "Block "<< block << ": HIT in Victim Cache (Swap with Main Cache)";

                int mainReplace =-1;
                for (int i =0 ; i < mainCache.size(); i++){
                    if (!mainCache[i].valid) {
                        mainReplace =i;
                        break;
                    }
                }
                if (mainReplace == -1) mainReplace =0; // evict first line

                swap(mainCache[mainReplace].blockNumber, victimCache[victimIdx].blockNumber);
                mainCache[mainReplace].valid = true;
                victimCache[victimIdx].valid = true;

            } else {
                // miss in both caches , i mean like a normal miss in direct mapping
                misses++;
                cout<< "Block: " << block << " : MISS\n";

                // so now new need to evict the line from main cache
                int mainReplace =-1;
                for (int i =0 ; i < mainCache.size(); i++){
                    if (!mainCache[i].valid) {
                        mainReplace =i;
                        break;
                    }
                }
                if (mainReplace == -1) mainReplace =0;

                // then we need to move the evicted block to victim cache
                // here it is , the main add advantage of associative mapping
                if (mainCache[mainReplace].valid) {
                    // we have to find a place in victim cache
                    int vReplace = -1;
                    for (int i =0; i < victimCache.size(); i++){
                        if (!victimCache[i].valid){
                            vReplace = i ;
                            break;
                        }
                    }
                    if (vReplace == -1) vReplace =0; // evict first line of victim cache
                    victimCache[vReplace].blockNumber = mainCache[mainReplace].blockNumber;
                    victimCache[vReplace].valid = true;
                }

                mainCache[mainReplace].blockNumber = block;
                mainCache[mainReplace].valid = true;
            }

        }
    }

    cout << "\n Results \n";
    cout << "Hits in main cache: "<< hits<< endl;
    cout << "Hits in victim cache: "<< victimHits<< endl;
    cout << "Misses: " << misses<< endl;
    
    return 0;
}