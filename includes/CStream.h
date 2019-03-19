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

