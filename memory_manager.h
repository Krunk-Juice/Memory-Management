#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "process.h"
#include "frame.h"

class Memory_Manager {
    private:
        int memorySize = 0;
        int pageSize = 0;
        int numberOfProcesses = 0;
        int time = 0;
        int old_time = -1;
        std::string fileName;
        std::ifstream infile;
        std::vector<Process> input_queue;
        std::vector<Process> processes;
        std::vector<Frame> memory_map;

    public:

        /* Accepts user inputs. */
        void user_input() {
            bool correct = false;

            do {
                printf("Physical(Main) Memory Size: ");
                std::cin >> memorySize;

                if (memorySize <= 0) {
                    perror("ERROR: Memory size must be greater than 0.\n");
                    continue;
                }

                printf("Page Size (1: 100, 2: 200, 3: 400): ");
                std::cin >> pageSize;

                if (pageSize < 1 || pageSize > 3) {
                    perror("ERROR: Input must be 1, 2, or 3.\n");
                    continue;
                }

                switch(pageSize) {
                    case 1: 
                        pageSize = 100; 
                        break;
                    case 2:
                        pageSize = 200;
                        break;
                    case 3:
                        pageSize = 400;
                        break;
                }

                if (memorySize % pageSize != 0) {
                    perror("ERROR: Physical(Main) Memory Size must be a multiplie of the Page Size.\n");
                    continue;
                }
                else
                    correct = true;
                
            } while (!correct);

            do {
                correct = false;

                std::cin.ignore();  
                printf("Enter input file: ");
                std::getline(std::cin, fileName);
                infile.open(fileName.c_str());

                if (infile.fail()) {
                    perror("ERROR: File not found.\n");
                    continue;
                }
                else 
                    correct = true;             

            } while (!correct);
        }

        /* Read user's input file and add the "processes" to the list. */
        void addProcesses() {

            int PID;
            int memoryRequest;
            int sumMemoryRequest;
            int processLife;
            int arrivalTime;
            int dummy;

            infile >> numberOfProcesses;

            for (int i = 0; i < numberOfProcesses; i++) {
                infile >> PID;
                infile >> arrivalTime;
                infile >> processLife;
                infile >> memoryRequest;

                sumMemoryRequest = 0;

                for(int j = 0; j < memoryRequest; j++) {
                    infile >> dummy;
                    sumMemoryRequest += dummy;
                }

                Process process(PID, arrivalTime, processLife, sumMemoryRequest);
                processes.push_back(process);
            }
        }

        /* Arrival of process and add process to input_queue. */
        void processArrival() {
            for (int i = 0; i < processes.size(); i++) {
                if (processes[i].isArrive(time)) {
                    if (old_time == time)
                        printf("\t");
                    else {
                        old_time = time;
                        printf("Time = %d : ", time);
                    }
                    printf("Process %d arrives\n", processes[i].getPID());
                    input_queue.push_back(processes[i]);

                    printInputQueue();
                }
            }
        }

        /* Print process queue waiting to added to physical(main) memory. */
        void printInputQueue() {
            printf("\tInput Queue: [ ");
            if (input_queue.size() != 0) {
                for (int i = 0; i < input_queue.size(); i++)
                    printf("%d ", input_queue[i].getPID());
            }
            printf("] \n");
        }
        
        /* Print the physical(main) memory or memory map. */
        void printMemoryMap() {
            printf("\tMemory Map: \n");
            bool free_frame = false;
            int base;
            
            for (int i = 0; i < memory_map.size(); i++) {
                if (!free_frame && !memory_map[i].isAssign()) {
                    free_frame = true;
                    base = i;
                }
                else if (free_frame && memory_map[i].isAssign()) {
                    free_frame = false;
                    printf("\t\t%d - %d : Free Frame\n", base * pageSize, i * pageSize - 1);
                }

                if (memory_map[i].isAssign())
                    printf("\t\t%d - %d : Process %d, Page %d\n", 
                        memory_map[i].getBase(),
                        memory_map[i].getLimit(),
                        memory_map[i].getPID(),
                        memory_map[i].getPNumber()
                    );
            }

            if (free_frame)
                printf("\t\t%d - %d : Free Frame\n", base * pageSize, (int)memory_map.size() * pageSize - 1);
        }

        /* Create the physical(main) memory or memory map. */
        void initMemoryMap() {
            int base_register = 0;
            int limit_register = pageSize - 1;
            int frame_count = memorySize / pageSize;
            for (int i = 0; i < frame_count; i++) {
                Frame frame(base_register, limit_register);
                memory_map.push_back(frame);
                base_register += pageSize;
                limit_register += pageSize;
            }
        }

        /* Add process to physical(main) memory or memory map. */
        void add2MemoryMap() {
            int size = input_queue.size();
            for (int i = 0; i < size; i++) {
                if(isFrameAvailable(input_queue[i])) {
                    int page_number = 1;
                    int page_limit = input_queue[i].getMReq();

                    printf("\tMemory Manager move Process %d to main memory.\n", input_queue[i].getPID());

                    for (int j = 0; j < memory_map.size(); j++) {
                        if (!memory_map[j].isAssign() && page_limit > 0) {
                            memory_map[j].setAssign();
                            memory_map[j].setPageNumber(page_number);
                            memory_map[j].setPID(input_queue[i].getPID());
                            page_number++;
                            page_limit -= pageSize;
                        }
                    }
                    int pid = input_queue[i].getPID();
                    removeFromInputQueue(input_queue[i].getPID());
                    updateProcessTime(pid);
                    printInputQueue();
                    printMemoryMap();
                }
            }
        }

        /* Display the changing/updating memory map and remove processes that have completed. */
        void updateMemoryMap() {
            for (int i = 0; i < processes.size(); i++) {
                if (processes[i].processComplete(time)) {
                    if (old_time == time)
                        printf("\t");
                    else {
                        old_time = time;
                        printf("Time = %d : ", time);
                    }
                    printf("Process %d completed.\n", processes[i].getPID());
                    for (int j = 0; j < memory_map.size(); j++) {
                        if (memory_map[j].getPID() == processes[i].getPID())
                            memory_map[j].remove();
                    }
                    printMemoryMap();
                }
            }
        }

        /* Check to see if the frame in physical(main) memory is free for allocation. */
        bool isFrameAvailable(Process process) {
            int free_frames = 0;
            for (int i = 0; i < memory_map.size(); i++) {
                if (!memory_map[i].isAssign())
                    free_frames++;
            }
            return (free_frames * pageSize) >= process.getMReq();
        }

        /* Remove process from input_queue signalling that it has been added to physical(main) memory or memory map. */
        void removeFromInputQueue(int pid) {
            int i = 0;
            while (i < input_queue.size() && input_queue[i].getPID() != pid)
                i++;
            if (i < input_queue.size())
                input_queue.erase (input_queue.begin() + i);
        }

        /* Update and keep track of the time the process is executing.
        Once process is complete it will be removed from physical(main) memory
        or memory map. */
        void updateProcessTime(int pid) {
            bool found = false;
            for (int i = 0; i < processes.size() && !found; i++) {
                if (processes[i].getPID() == pid) {
                    processes[i].setTime2Mem(time);
                    found = true;
                }
            }
        }

        /* Calculates average turnaround time. */
        void averageTurnAround() {
            double sum = 0;
            for (int i = 0; i < processes.size(); i++) {
                sum += processes[i].getTurnAround();
                printf("Process %d Turnaround Time = %d\n",
                    processes[i].getPID(),
                    processes[i].getTurnAround()
                );
            }
            printf("Average Turnaround Time = %.2lf\n", sum / processes.size());
        }

        int getTime() {
            return time;
        }

        int getIQSize() {
            return input_queue.size();
        }

        void incTime() {
            time++;
        }
};