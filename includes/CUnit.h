#ifndef CUNIT_H
#define CUNIT_H

#include "CStream.h"

class CUnit
{
public:
	CUnit();
	~CUnit();

	CUnit(int id, int conc_num, int tail_num);

	//index of the unit to which this unit�s concentrate stream is connected 
	int conc_num = -1;
	//index of the unit to which this unit�s concentrate stream is connected 
	int tail_num = -1;
	//A Boolean that is changed to true if the unit has been seen 
	bool mark = false;

	// Unit id number
	int id = -1;

	// Streams for the total input (old and new)
	// and the two outputs (concentrate and tail)
	CStream curr_in_feed, old_in_feed,
			conc, tail;


	CUnit &operator=(CUnit &other)
	{
		if (this != &other)
		{
			conc_num = other.conc_num;
			tail_num = other.tail_num;
			mark = other.mark;
			id = other.id;
			curr_in_feed = other.curr_in_feed;
			old_in_feed = other.old_in_feed;
			conc = other.conc;
		}

		return *this;
	}

};
#endif // !CUNIT_H