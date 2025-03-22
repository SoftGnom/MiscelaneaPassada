#pragma once
#include "Util.h"
class ClasseCami
{
public:
	static bool nodeCami(XmlElement element)
	{
		int i = 0;
		bool trobat = false;
		bool name = false;

		while (i < element.fills.size())
		{
			if (element.fills[i].first == "tag")
			{
				trobat = true;

				std::pair<std::string, std::string> tag = Util::kvDeTag(element.fills[i].second);

				if (tag.first == "highway" || tag.first == "public_transport" || tag.first == "access" || tag.first == "entrance")
					return true;

				if (tag.first == "name")
					name = true;
			}
			i++;
		}

		if (trobat == false)
			return true;
		if (name == false)
			return true;

		return false;
	}

	static bool highway(XmlElement element)
	{
		int i = 0;

		while (i < element.fills.size())
		{
			if (element.fills[i].first == "tag")
			{
				std::pair<std::string, std::string> tag = Util::kvDeTag(element.fills[i].second);

				if (tag.first == "highway")
				{ 
					return true;
				}
			}
			i++;
		}

		return false;
	}
};