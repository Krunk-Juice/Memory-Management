#include <iostream>
#include <string>
#include <fstream>

class Memory_Manager {
    private:
        int memorySize = 0;
        int pageSize = 0;
        int processNumber = 0;
        int time = 0;

    public:
        void input() {
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

            std::string fileName;
            std::ifstream infile;

            do {
                correct = false;

                std::cin.ignore();  
                printf("Enter input file: ");
                std::getline(std::cin, fileName); 

                if (infile.fail()) {
                    printf("ERROR: File %s cannot be found.\n", fileName);
                    continue;
                }
                else 
                    correct = true;             

            } while (!correct);
        }
};