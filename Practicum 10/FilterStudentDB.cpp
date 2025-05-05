#include "FilterStudentDB.h"


FilterStudentDB::FilterStudentDB(bool (*filter)(const Student*))
{
	for (size_t i = 0; i < capacity; i++)
	{
		if (filter(students[i]))
		{
			delete students[i];
			students[i] = nullptr;
			size--;
		}
	}
}

FilterStudentDB::FilterStudentDB(size_t N)
{
	int limit = N;

	if (N > size)
	{
		throw std::logic_error("N is more than the students. Non will be removed");
	}

	for (size_t i = 0; i < capacity; i++)
	{
		if (students[i])
		{
			if (N > 0)
			{
				N--;
				continue;
			}

			delete students[i];
			students[i] = nullptr;
		}
	}

	size = N;
}