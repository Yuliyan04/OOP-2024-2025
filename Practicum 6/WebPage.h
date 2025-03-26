#pragma once
#include <iostream>
#include <istream>

union IPadress
{
	uint8_t octets[4];
	uint32_t adress;

	IPadress(uint32_t adress) : adress(adress) {};
	IPadress() : adress(0) {};
};

class WebPage
{
	char* adress;
	IPadress ipAdress;

public:

	WebPage();
	WebPage(const WebPage& other);
	WebPage& operator=(const WebPage& other);
	~WebPage();

	friend std::ostream& operator<<(std::ostream& os, const WebPage& other);
	friend std::istream& operator>>(std::istream& is, WebPage& other);

	const char* getAdress() const;

private:

	void copyFrom(const WebPage& other);
	void free();
};

