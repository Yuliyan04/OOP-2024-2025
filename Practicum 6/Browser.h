#pragma once
#include "WebPage.h"

const size_t WEB_PAGES_MAX = 30;


class Browser
{
	WebPage openedPages[WEB_PAGES_MAX];
	size_t count = 0;

public:

	void addPage(const WebPage& other);
	void removePage(const WebPage& other);

	Browser& operator+=(const WebPage& other);
	Browser& operator-=(const WebPage& other);

	void printWebPages() const;
};


