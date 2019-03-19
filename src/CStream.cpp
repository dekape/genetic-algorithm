#include "CStream.h"

CStream::CStream()
{
	conc = 0; tail = 0;
}

CStream::~CStream() {}

// Addition operator override
CStream CStream::operator+(CStream &rhs) {

    // Create new stream 
	CStream out_stream;

	
    // Add old streams into new stream
	out_stream.conc = conc + out_stream.conc;
    out_stream.tail = tail + out_stream.tail;


	return out_stream;
}


// In-place addition operator override
CStream &CStream::operator+=(CStream &rhs) {
	
    // Append the concentrates and tails
	conc += rhs.conc;
    tail += rhs.tail;
    
    // return the reference to this modified stream
	return *this;
}
