#include "Utility.h"

bool isi5i7(const Computer& comp)
{
	const char* processor = comp.getProcessor();
	while (*processor)
	{
		if (*processor == 'i')
		{
			if (*(processor + 1))
			{
				if (*(processor + 1) == '5' || *(processor + 1) == '7')
				{
					return true;;
				}
			}
		}
	}
	return false;
}

bool Utility::isGoodForGamng(const Computer& comp)
{
	if (isi5i7(comp) && comp.getVideo() >= 3060 && comp.getHD() >= 512)
	{
		return true;
	}
	return false;
}

bool Utility::isGoodForTravel(const Computer& other)
{
	if (other.getWeight() <= 3 && other.getBatteryLife() >= 6)
	{
		return true;
	}
	return false;
}