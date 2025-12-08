#include<iostream>
#include <vector>
using namespace std;

struct CacheLine{
    int blockNumber;
    bool Valid; // by this flag i will ensure later that
                // the cache only reports a hit if a block has actually been loaded to the cache
};

int main()
{
    int cacheSize = 8; // we have here 8 cache lines as an example
    vector<int> memoryAccesses = { 64, 128, 64, 128, 64, 129, 64};

    vector<CacheLine> cache(cacheSize, {-1, false}); //because the cache is initially empty

    int hits = 0;
    int misses =0;
    int conflictMisses =0;

    cout << "Direct Mapped Cache simulation\n\n"; //form theoretical readings of class resources

    for(int block : memoryAccesses){
        int index = block % cacheSize; // this index represents a cache line number to which a specific block is mapping to

        cout<< "Accessing Bock: " << block
            << " -> Cache Line: " << index << " ";

        if (cache[index].Valid && cache[index].blockNumber == block){
            hits++;
            cout << "(HITS)\n";
        } else {
            if (cache[index].Valid){ // this indicate the trashing case, during direct mapping
                conflictMisses++;
                cout<< "(CONFLICT MISS - Evict Block "
                    << cache[index].blockNumber<< " )\n";
            }else {
                cout << "(MISS - Empty line)\n";
            }
            cache[index].blockNumber = block;
            cache[index].Valid = true;
            misses++;
        }
    }

    cout << "\nResults:\n";
    cout << "Hits: "<< hits<< endl;
    cout << "Misses: "<< misses<< endl;
    cout << "Conflict Misses: " << conflictMisses << endl;
    
    return 0;
}