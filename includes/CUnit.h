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



class CUnit {
  public:


  // Indexes to which this unit's output streams are connected 
  int conc_num;
  int tails_num;
  // Mark unit as seen or not seen
  bool mark;


  // Streams for the total input (old and new)
  // and the two outputs (concentrate and tail)
  CStream curr_in_feed, old_in_feed, 
          conc_out, tail_out;


  /*

    ...other member functions and variables of CUnit

  */


};

