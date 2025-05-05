#pragma once
#include "StudentDB.h"


class FilterStudentDB : public StudentDB
{
public:

	FilterStudentDB(bool (*filter)(const Student*));
	FilterStudentDB(size_t N);
};