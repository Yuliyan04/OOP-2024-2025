#include "GradeReport.h"

void GradeReport::copyFrom(const GradeReport& other)
{
	gradesCount = other.gradesCount;
	grades = new unsigned[gradesCount];

	for (size_t i = 0; i < gradesCount; i++)
	{
		grades[i] = other.grades[i];
	}

	reportName = new char[strlen(other.reportName) + 1];
	strcpy(reportName, other.reportName);
}

void GradeReport::free()
{
	delete[] grades;
	delete[] reportName;

	gradesCount = 0;
	grades = nullptr;
	reportName = nullptr;
}

void GradeReport::setGrades(const unsigned* grades, unsigned gradesCount)
{
	if (!grades || gradesCount == 0)
	{
		return;
	}

	delete[] this->grades;
	this->grades = new unsigned[gradesCount];
	for (size_t i = 0; i < gradesCount; i++)
	{
		this->grades[i] = grades[i];
	}

	this->gradesCount = gradesCount;
}

void GradeReport::setReportName(const char* name)
{
	if (!name)
	{
		return;
	}

	delete[] reportName;
	reportName = new char[strlen(name) + 1];
	strcpy(reportName, name);
}


GradeReport::GradeReport() :grades(nullptr), gradesCount(0), reportName(nullptr) {}

GradeReport::GradeReport(const unsigned* grades, unsigned gradesCount, const char* name)
{
	setReportName(name);
	setGrades(grades, gradesCount);
}

GradeReport::GradeReport(const GradeReport& other)
{
	copyFrom(other);
}

GradeReport& GradeReport::operator=(const GradeReport& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

GradeReport::~GradeReport()
{
	free();
}

unsigned GradeReport::getGradesCount() const
{
	return gradesCount;
}

const char* GradeReport::getReportName() const
{
	return reportName;
}

double GradeReport::getAverageResult() const
{
	double res = 0;

	for (size_t i = 0; i < gradesCount; i++)
	{
		res += grades[i];
	}

	return res /= gradesCount;
}