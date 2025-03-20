#include "NavyHtmlTableGenerator.h"


void NavyHtmlTableGenerator::setNavy(const Navy& navy)
{
	this->navy = navy;
}

void NavyHtmlTableGenerator::setFilename(const char* filename)
{
	size_t len = strlen(filename);
	if (len > 128 || !filename)
	{
		return;
	}

	strcpy(this->filename, filename);
}

NavyHtmlTableGenerator::NavyHtmlTableGenerator(const Navy& navy, const char* filename)
{
	setNavy(navy);
	setFilename(filename);
}

void NavyHtmlTableGenerator::saveNavyToFile() const
{
	std::ofstream file(filename);
	if (file.is_open())
	{
		return;
	}

	file << "<table>" << std::endl;
	file << "  <tr>" << std::endl;
	file << "    <th>Name</th>" << std::endl;
	file << "    <th>Launch Year</th>" << std::endl;
	file << "    <th>Class</th>" << std::endl;
	file << "    <th>NumGuns</th>" << std::endl;
	file << "  </tr>" << std::endl;

	for (size_t i = 0; i < navy.getShipsCount(); i++)
	{
		file << "  <tr>" << std::endl;
		file << "    <td>Ship " << i << " " << navy.at(i).getShipName() << "</td>" << std::endl;
		file << "    <td>Ship " << i << " " << navy.at(i).getLaunchYear() << "</td>" << std::endl;
		file << "    <td>Ship " << i << " " << (int)navy.at(i).getShipClass() << "</td>" << std::endl;
		file << "    <td>Ship " << i << " " << navy.at(i).getGunsCount() << "</td>" << std::endl;
	}

	file << "</table>" << std::endl;

	file.close();
}