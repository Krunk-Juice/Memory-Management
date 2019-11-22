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
};