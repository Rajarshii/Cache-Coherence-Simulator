
#include "bus.h"
#include "cache.h"

/*void Bus::sendRequest(int requestingCore, int tag, const std::string& operation, ProtocolType protocol) {
    std::lock_guard<std::mutex> lock(busMutex);
    bool isExclusive = true; // Track if this line is held exclusively by one core

    for (auto& ep : endPoints) {
        if (ep->getObjID() != requestingCore) {
            if (operation == "READ") {
                if (ep->getLineState(tag) != CacheState::Invalid) {
                    isExclusive = false;
                    cache->handleBusResponse(tag, "SHARED");
                }
            } else if (operation == "WRITE") {
                cache->handleBusResponse(tag, "INVALIDATE");
            }
        }
    }

    // Decide response for the requesting core based on protocol and exclusivity
    std::string response = (protocol == ProtocolType::MESI && isExclusive) ? "EXCLUSIVE" : "SHARED";
    if (operation == "WRITE") response = "MODIFIED";

    // Send response to the requesting cache
    [requestingCore]->handleBusResponse(tag, response);
}*/

void Bus::addEndPoint(BusEndPoint* ep) {
    endPoints.push_back(ep);
}
