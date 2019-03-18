class CStream {
public:


  // Proportions - how much of this stream's mass is
  // concentrate vs tail
	double concentrate;
  double tail;


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
  CStream current_input_feed, old_input_feed, 
          conc_output, tail_output;


  /*

    ...other member functions and variables of CUnit

  */


};

