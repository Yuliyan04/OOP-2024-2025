#pragma once
#include "StudentDB.h"


class SortedStudentDB : public StudentDB
{
public:

	SortedStudentDB();
	SortedStudentDB(bool (*criterie)(const Student*, const Student*));
};