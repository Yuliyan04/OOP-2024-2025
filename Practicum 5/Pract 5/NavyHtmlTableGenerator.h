#pragma once
#include "Navy.h"
#include <fstream>

const size_t FILENAME_MAX_SIZE = 128;

class NavyHtmlTableGenerator
{
	char filename[FILENAME_MAX_SIZE + 1];
	Navy navy;

public:

	NavyHtmlTableGenerator(const Navy& flot, const char* filename);
	void saveNavyToFile() const;

private:

	void setNavy(const Navy& navy);
	void setFilename(const char* filename);
};

