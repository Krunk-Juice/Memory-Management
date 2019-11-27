#include <iostream>
#include <fstream>
#include <string>
#include <vector>
// #include "process.h"
// #include "frame.h"
#include "memory_manager.h"

int main() {
    // std::vector<Process> InputQueue;
    // std::vector<Process> Processes;
    // std::vector<Frame> MainMemory;

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