#include "includes.h"
#include "cache.h"
#include "interface.h"


std::vector<Cache*> Bus::caches;
std::mutex Bus::busMutex;

int main() {
    ProtocolType selectedProtocol;
    char choice;
    std::cout << "Select protocol (M for MESI, S for MSI): ";
    std::cin >> choice;

    if (choice == 'M' || choice == 'm') {
        selectedProtocol = ProtocolType::MESI;
    } else {
        selectedProtocol = ProtocolType::MSI;
    }

    Cache core0(0, selectedProtocol), core1(1, selectedProtocol), core2(2, selectedProtocol);
    Bus::addCache(&core0);
    Bus::addCache(&core1);
    Bus::addCache(&core2);

    // Simulation of some operations
    core0.write(100);  // Core 0 writes to address 100
    core1.read(100);   // Core 1 reads address 100
    core2.read(100);   // Core 2 reads address 100
    core1.write(100);  // Core 1 writes to address 100

    return 0;
}
