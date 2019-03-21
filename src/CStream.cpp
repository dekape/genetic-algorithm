#include "CStream.h"

CStream::CStream()
{
	value = 0; waste = 0;
}

CStream::~CStream() {}

// Addition operator override
CStream CStream::operator+(CStream &rhs) {

    // Create new stream
	CStream out_stream;

    // Add old streams into new stream
	out_stream.value = value + out_stream.value;
    out_stream.waste = waste + out_stream.waste;

	return out_stream;
}


// In-place addition operator override
CStream &CStream::operator+=(CStream &rhs) {

    // Append the values and wastes
	value += rhs.value;
    waste += rhs.waste;

    // return the reference to this modified stream
	return *this;
}

CStream &CStream::operator=(CStream &rhs)
{
	if (this != &rhs)
	{
		value = rhs.value;
		waste = rhs.waste;
	}

	return *this;
}

// Equals operator overload
CStream &CStream::operator=(CStream &rhs)
{
	if (this != &rhs)
	{
		value = rhs.value;
		waste = rhs.waste;
	}

	return *this;

}
