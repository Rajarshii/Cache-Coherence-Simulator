#include "includes.h"
#include "cache.h"
#include "coherence.h"
#include "bus.h"

// Cache class for each core

CacheState Cache::getLineState(int tag) {
    if (cacheLines.find(tag) != cacheLines.end()) {
        return cacheLines[tag].state;
    }
    return CacheState::Invalid;
}

void Cache::read(int tag) {
    CacheState state = getLineState(tag);
    if (state == CacheState::Invalid) {
        requestBus(tag, "READ");
    } else if (state == CacheState::Modified || state == CacheState::Shared || state == CacheState::Exclusive) {
        std::cout << "Core " << coreID << " reads from cache, state: " << (int)state << "\n";
    }
}

void Cache::write(int tag) {
    CacheState state = getLineState(tag);
    if (state == CacheState::Modified) {
        std::cout << "Core " << coreID << " writes to cache, state: Modified\n";
    } else {
        requestBus(tag, "WRITE");
    }
}

void Cache::handleBusResponse(int tag, const std::string& response) {
    if (response == "INVALIDATE") {
        invalidateLine(tag);
    } else if (response == "SHARED") {
        updateLineState(tag, CacheState::Shared);
    } else if (response == "EXCLUSIVE") {
        if (protocol == ProtocolType::MESI) {
            updateLineState(tag, CacheState::Exclusive);
        } else {
            updateLineState(tag, CacheState::Shared);
        }
    } else if (response == "MODIFIED") {
        updateLineState(tag, CacheState::Modified);
    }
}

void Cache::invalidateLine(int tag) {
    if (cacheLines.find(tag) != cacheLines.end()) {
        cacheLines[tag].state = CacheState::Invalid;
    }
}

void Cache::updateLineState(int tag, CacheState newState) {
    if (cacheLines.find(tag) != cacheLines.end()) {
        cacheLines[tag].state = newState;
    } else {
        cacheLines[tag] = CacheLine(tag, newState);
    }
}

void Cache::requestBus(int tag, const std::string& operation) {
    std::cout << "Core " << coreID << " requests " << operation << " for tag " << tag << " on bus.\n";
    Bus::sendRequest(coreID, tag, operation, protocol);
}

int Cache::getCoreID() {
    return coreID;
}
