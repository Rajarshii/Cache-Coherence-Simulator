#include <vector>

class SimObj {
public:
    SimObj() {
        registerObject();
    }

    void registerObject() {

    }

    int getObjID() {
        return ObjID;
    }

    virtual void run() = 0;

    //virtual ~SimObj() = 0;
private:
    int ObjID;
    static std::vector<std::pair<int,SimObj>> regdObj;
};