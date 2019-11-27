class Frame {
    private:
        int _baseRegister;
        int _limitRegister;
        int _processID;
        int _pageNumber;
        bool _isAssigned;

    public:
        Frame(int start_register, int end_register) {
            _baseRegister = start_register;
            _limitRegister = end_register;
            _processID = 0;
            _pageNumber = 0;
            _isAssigned = false;
        }

        int getPID() {
            return _processID;
        }

        int getBase() {
            return _baseRegister;
        }

        int getLimit() {
            return _limitRegister;
        }

        int getPNumber() {
            return _pageNumber;
        }

        bool isAssign() {
            return _isAssigned;
        }

        void setAssign() {
            _isAssigned = true;
        }

        void setPageNumber(int page) {
            _pageNumber = page;
        }

        void setPID(int id) {
            _processID = id;
        }

        void remove() {
            _processID = 0;
            _pageNumber = 0;
            _isAssigned = false;
        }
};