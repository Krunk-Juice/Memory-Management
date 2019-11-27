#include "memory_manager.h"

int main() {

    Memory_Manager M;

    M.user_input();
    M.addProcesses();
    M.initMemoryMap();

    do {
        M.processArrival();
        M.updateMemoryMap();
        M.add2MemoryMap();
        M.incTime();
    } while (!(M.getTime() > 10000 && M.getIQSize() == 0));

    M.averageTurnAround();

    return 0;
}