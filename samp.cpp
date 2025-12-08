#include <iostream>
#include <vector>
using namespace std;

struct CacheLine {
    int blockNumber;
    bool valid;
    int lastUsed; // for LRU replacement
};

int main() {
    int totalLines = 8;
    int ways = 2;          // 2-way set associative
    int numSets = totalLines / ways;

    vector<int> memoryAccesses = {64, 128, 64, 128, 64, 129, 64};

    vector<vector<CacheLine>> cache(numSets, vector<CacheLine>(ways, {-1, false, 0}));

    int hits = 0, misses = 0, conflictMisses = 0;
    int timeStamp = 0;

    cout << "2-Way Set Associative Cache Simulation\n\n";

    for (int block : memoryAccesses) {
        int setIndex = block % numSets;
        timeStamp++;

        cout << "Accessing Block: " << block
             << " -> Set: " << setIndex << "  ";

        bool hit = false;
        int emptyWay = -1;
        int lruWay = 0;
        int minUsed = cache[setIndex][0].lastUsed;

        for (int w = 0; w < ways; w++) {
            if (cache[setIndex][w].valid && cache[setIndex][w].blockNumber == block) {
                // HIT
                hit = true;
                hits++;
                cache[setIndex][w].lastUsed = timeStamp;
                cout << "(HIT in way " << w << ")\n";
                break;
            }
            if (!cache[setIndex][w].valid)
                emptyWay = w;
            if (cache[setIndex][w].lastUsed < minUsed) {
                minUsed = cache[setIndex][w].lastUsed;
                lruWay = w;
            }
        }

        if (!hit) {
            misses++;
            if (emptyWay != -1) {
                cout << "(MISS - Empty way)\n";
                cache[setIndex][emptyWay] = {block, true, timeStamp};
            } else {
                conflictMisses++;
                cout << "(CONFLICT MISS - Evict Block "
                     << cache[setIndex][lruWay].blockNumber
                     << " from way " << lruWay << ")\n";

                cache[setIndex][lruWay] = {block, true, timeStamp};
            }
        }
    }

    cout << "\nResults:\n";
    cout << "Hits: " << hits << endl;
    cout << "Misses: " << misses << endl;
    cout << "Conflict Misses: " << conflictMisses << endl;

    return 0;
}
