#ifndef CSTREAM_H
#define CSTREAM_H

class CStream {
public:
	CStream();
	~CStream();

	// Proportions - how much of this stream's mass is
	// concentrate vs tail
	double value;
	double waste;

	// Operator overloads to help calculations later
	CStream operator+(CStream &rhs);
	CStream &operator+=(CStream &rhs);
	CStream &operator=(CStream &rhs);
};


#endif // !CSTREAM_H
