class CUnit {
public:
    //index of the unit to which this unit’s concentrate stream is connected
    int conc_num; //remove = 1
    //index of the unit to which this unit’s concentrate stream is connected
    int tails_num;

    int id;
    //A Boolean that is changed to true if the unit has been seen
    bool mark;

    /*

    ...other member functions and variables of CUnit

    */
    
    CUnit(){
        conc_num = -1;
        tails_num = -1;
        id = -1;
        mark = false;
    }
    
    CUnit(int curr_id, int conc, int tail){
        id = curr_id;
        conc_num = conc;
        tails_num = tail;
        mark = false;
    }
};

