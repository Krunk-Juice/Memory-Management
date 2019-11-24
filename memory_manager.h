#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "process.h"

class Memory_Manager {
    private:
        int memorySize = 0;
        int pageSize = 0;
        int numberOfProcesses = 0;
        int time = 0;
        int old_time = -1;
        std::string fileName;
        std::ifstream infile;

    public:
        void user_input() {
            bool correct = false;

            do {
                printf("Physical Memory Size: ");
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
                    perror("ERROR: Physical Memory Size must be a multiplier of the Page Size.\n");
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
                    printf("ERROR: File %s cannot be found.\n", fileName);
                    continue;
                }
                else 
                    correct = true;             

            } while (!correct);
        }

        void file_scanner(std::vector<Process> processes) {

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

        void processArrival(std::vector<Process> processes, std::vector<Process> input_queue) {
            for (int i = 0; i < processes.size(); i++) {
                if (processes[i].isArrive(time)) {
                    if (old_time == time)
                        printf("\t");
                    else {
                        old_time = time;
                        printf("t = %d: ", time);
                    }
                    printf("Process %d arrives\n", processes[i].getPID);
                    input_queue.push_back(processes[i]);

                    printInputQueue(input_queue);
                }
            }
        }

        void removeFromInputQueue(int pid, std::vector<Process> input_queue) {
            int i = 0;
            while (i < input_queue.size() && input_queue[i].getPID != pid)
                i++;
            if (i < input_queue.size())
                input_queue.erase (input_queue.begin() + i);
        }

        void printInputQueue(std::vector<Process> input_queue) {
            printf("\tInput Queue: [ ");
            if (input_queue.size() != 0) {
                for (int i = 0; i < input_queue.size(); i++)
                    printf("%d", input_queue[i].getPID());
            }
            printf(" ] \n");
        }
        
        void printMemoryMap(int page_entry_size, std::vector<Frame> memory_map) {
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
                    printf("\t\t%d - %d : Free Frame\n", base * page_entry_size, i * page_entry_size - 1);
                }
            }

            if (free_frame)
                printf("\t\t%d - %d : Free Frame\n", base * page_entry_size, memory_map.size() * page_entry_size - 1);
        }
};