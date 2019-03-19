#pragma once

class CStream {
public:
	// Proportions - how much of this stream's mass is
	// concentrate vs tail
	double conc;
	double tail;

	CStream();

	~CStream();

	// Operator overloads to help calculations later
	CStream operator+(CStream &rhs);
	CStream &operator+=(CStream &rhs);
};


class CUnit
{
public:
	CUnit();
	CUnit(int id, int tails_num, int);
	~CUnit();

	//index of the unit to which this unit’s concentrate stream is connected 
	int conc_num = -1;
	//index of the unit to which this unit’s concentrate stream is connected 
	int tails_num = -1;
	//A Boolean that is changed to true if the unit has been seen 
	bool mark = false;

	// Unit id number
	int id = -1;

	// Streams for the total input (old and new)
	// and the two outputs (concentrate and tail)
	CStream curr_in_feed, old_in_feed,
		conc_out, tail_out;
};

