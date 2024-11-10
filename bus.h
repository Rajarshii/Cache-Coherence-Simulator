#include "includes.h"
#include "coherence.h"
#include "simobj.h"

// A Bus Endpoint: Caches should be 
class BusEndPoint : public SimObj {

};

class Bus {
public:
    void sendRequest(int requestingCore, int tag, const std::string& operation, ProtocolType protocol);
    void addEndPoint(BusEndPoint* ep);

private:
    std::vector<BusEndPoint*> endPoints;
    std::mutex busMutex;
};