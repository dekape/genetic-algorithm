class CStream {
public:


  // Proportions - how much of this stream's mass is
  // concentrate vs tail
	double conc = 0;
  double tail = 0;


  // Operator overloads to help calculations later
	CStream operator+(CStream &rhs);
	CStream &operator+=(CStream &rhs);


};




public:
    CUnit();
    
    CUnit(int curr_id, int conc, int tail);
      
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


  // Streams for the total input (old and new)
  // and the two outputs (concentrate and tail)
  CStream curr_in_feed, old_in_feed, 
          conc_out, tail_out;


  /*

    ...other member functions and variables of CUnit

  */


};

