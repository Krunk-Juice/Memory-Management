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

        bool isArrive(int time) {
            return _arrivalTime == time;
        }

        int getPID() {
            return _processID;
        }

        int getMReq() {
            return _memoryRequest;
        }

        int getTime2Mem() {
            return _time2Memory;
        }

        int getTurnAround() {
            return _turnAroundTime;
        }

        int getLife() {
            return _processLife;
        }

        void setTurnAround(int time) {
            _turnAroundTime = time;
        }

        void setTime2Mem(int time) {
            _time2Memory = time;
        }
};