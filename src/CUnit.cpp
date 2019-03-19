#include "CUnit.h"

CUnit::CUnit()
{
	this->id = -1;
	this->conc_num = -1;
	this->tail_num = -1;
}

CUnit::CUnit(int id, int conc_num, int tails_num)
{
	this->id = id;
	this->conc_num = conc_num;
	this->tail_num = tails_num;
}

CUnit::~CUnit()
{
}


