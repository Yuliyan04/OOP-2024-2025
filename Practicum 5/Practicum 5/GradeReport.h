#pragma once
#include <cstring>

class GradeReport
{
	unsigned* grades;
	unsigned gradesCount;
	char* reportName;

public:

	GradeReport(const unsigned* grades, unsigned gradesCount, const char* name);

	GradeReport();
	GradeReport(const GradeReport& other);
	GradeReport& operator=(const GradeReport& other);
	~GradeReport();

	void setReportName(const char* name);
	void setGrades(const unsigned* grades, unsigned gradesCount);

	unsigned getGradesCount() const;
	const char* getReportName() const;
	double getAverageResult() const; 

private:

	void copyFrom(const GradeReport& other);
	void free();
};

