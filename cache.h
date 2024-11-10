#include "includes.h"
#include "coherence.h"

// Structure for a cache line
struct CacheLine {
    int tag;  // Address tag
    CacheState state;
    CacheLine(int t, CacheState s) : tag(t), state(s) {}
};

// Cache states
enum class CacheState {Modified, Shared, Invalid, Exclusive};

class Cache {
public:
    Cache(int id, ProtocolType protocol) : coreID(id), protocol(protocol) {}

    CacheState getLineState(int tag);

    void read(int tag);

    void write(int tag);

    void handleBusResponse(int tag, const std::string& response); 

    int getCoreID();

private:
    int coreID;
    ProtocolType protocol;
    std::unordered_map<int, CacheLine> cacheLines;

    void requestBus(int tag, const std::string& operation);
    void invalidateLine(int tag);
    void updateLineState(int tag, CacheState newState);
};