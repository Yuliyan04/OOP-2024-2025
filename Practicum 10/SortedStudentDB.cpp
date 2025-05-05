#include "SortedStudentDB.h"


SortedStudentDB::SortedStudentDB() {}

SortedStudentDB::SortedStudentDB(bool (*criteria)(const Student*, const Student*))
{
	for (size_t i = 0; i < capacity; i++)
	{
		size_t minElInd = i;
		for (size_t j = i + 1; j < capacity; j++)
		{
			if (criteria(students[j], students[minElInd]))
			{
				minElInd = j;
			}
		}

		if (minElInd != i)
		{
			std::swap(students[i], students[minElInd]);
		}
	}
}
