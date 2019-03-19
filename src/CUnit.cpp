#include "CUnit.h"


// Addition operator override
CStream CStream::operator+(CStream &rhs) {


    // Create new stream 
	CStream out_stream;

	
    // Add old streams into new stream
	out_stream.concentrate = concentrate + out_stream.concentrate;
    out_stream.tail = tail + out_stream.tail;


	return out_stream;


}


// In-place addition operator override
CStream &CStream::operator+=(CStream &rhs) {
	

    // Append the concentrates and tails
    concentrate += rhs.concentrate;
    tail += rhs.tail;
    

    // return the reference to this modified stream
	return *this;


}