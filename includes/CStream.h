#ifndef CSTREAM_H
#define CSTREAM_H

class CStream {
public:
	// Proportions - how much of this stream's mass is
	// concentrate vs tail
	double value;
	double waste;

	CStream();

	~CStream();

	// Operator overloads to help calculations later
	CStream operator+(CStream &rhs);
	CStream &operator+=(CStream &rhs);
};


#endif // !CSTREAM_H
