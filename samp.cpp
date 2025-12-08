#include <iostream>
#include <vector>
using namespace std;

struct CacheLine {
    int blockNumber;
    bool valid;
};

int main() {
    int cacheSize = 8; // 8 cache lines for example
    vector<int> memoryAccesses = {64, 128, 64, 128, 64, 129, 64};

    vector<CacheLine> cache(cacheSize, {-1, false});
    
    int hits = 0, misses = 0, conflictMisses = 0;

    cout << "Direct Mapped Cache Simulation\n\n";

    for (int block : memoryAccesses) {
        int index = block % cacheSize;

        cout << "Accessing Block: " << block 
            << " -> Cache Line: " << index << " ";

        if (cache[index].valid && cache[index].blockNumber == block) {
            hits++;
            cout << "(HIT)\n";
        } else {
            if (cache[index].valid) {
                conflictMisses++;
                cout << "(CONFLICT MISS - Evict Block " 
                    << cache[index].blockNumber << ")\n";
            } else {
                cout << "(MISS - Empty Line)\n";
            }
            cache[index].blockNumber = block;
            cache[index].valid = true;
            misses++;
        }
    }

    cout << "\nResults:\n";
    cout << "Hits: " << hits << endl;
    cout << "Misses: " << misses << endl;
    cout << "Conflict Misses: " << conflictMisses << endl;

    return 0;
}
