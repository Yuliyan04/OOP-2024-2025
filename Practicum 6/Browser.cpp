#include "Browser.h"

void Browser::addPage(const WebPage& other)
{
	if (count >= WEB_PAGES_MAX)
	{
		return;
	}

	openedPages[count] = other;
	count++;
}

void Browser::removePage(const WebPage& other)
{
	int ind = 0;
	for (size_t i = 0; i < count; i++)
	{
		if (strcmp(openedPages[i].getAdress(), other.getAdress()) == 0)
		{
			ind = i;
			break;
		}
	}

	if (ind == count - 1)
	{
		return;
	}

	for (size_t i = ind; i < count - 1; i++)
	{
		openedPages[i] = openedPages[i + 1];
	}
}

Browser& Browser::operator+=(const WebPage& other)
{
	if (count < WEB_PAGES_MAX)
	{
		openedPages[count] = other;
		count++;
	}
	return *this;
}

Browser& Browser::operator-=(const WebPage& other)
{
	int ind = 0;
	for (size_t i = 0; i < count; i++)
	{
		if (strcmp(openedPages[i].getAdress(), other.getAdress()) == 0)
		{
			ind = i;
			break;
		}
	}

	if (ind == count - 1)
	{
		return *this;
	}

	for (size_t i = ind; i < count - 1; i++)
	{
		openedPages[i] = openedPages[i + 1];
	}

	return *this;
}

void Browser::printWebPages() const
{
	if (count == 0)
	{
		std::cout << "The aren't any opened webpages left";
		return;
	}

	for (size_t i = 0; i < count; i++)
	{
		std::cout << openedPages[i] << std::endl;
	}
}