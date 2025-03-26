#include "WebPage.h"


void WebPage::copyFrom(const WebPage& other)
{
	adress = new char[strlen(other.adress) + 1];
	strcpy(adress, other.adress);

	ipAdress = other.ipAdress.adress;
}

void WebPage::free()
{
	delete[] adress;
	ipAdress.adress = 0;
}

WebPage::WebPage() : adress(nullptr), ipAdress(0) {}

WebPage::WebPage(const WebPage& other) : WebPage()
{
	copyFrom(other);
}

WebPage& WebPage::operator=(const WebPage& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

WebPage::~WebPage()
{
	free();
}


std::ostream& operator<<(std::ostream& os, const WebPage& other)
{
	return	os << other.adress << std::endl 
			  << other.ipAdress.octets[0] << "." 
			  << other.ipAdress.octets[1] << "." 
			  << other.ipAdress.octets[2] << "." 
			  << other.ipAdress.octets[3] << std::endl;
}

std::istream& operator>>(std::istream& is, WebPage& other)
{
	return is >> other.adress >> other.ipAdress.adress;
}

const char* WebPage::getAdress() const
{
	return adress;
}