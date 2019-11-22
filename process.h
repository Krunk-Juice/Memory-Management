#include <iostream>

class Process {
    private:
        int _processID;
        int _arrivalTime;
        int _processLife;
        int _memoryRequest;
        int _time2Memory;
        int _turnAroundTime;
        bool _isActive;

    public:
        Process(int id, int arrival, int life, int request) {
            _processID = id;
            _arrivalTime = arrival;
            _processLife = life;
            _memoryRequest = request;
            _time2Memory = 0;
            _turnAroundTime = 0;
            _isActive = false;
        }

        
};