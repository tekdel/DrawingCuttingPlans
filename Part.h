#include <string>

class Part
{
public:
	int x0, y0, width, height;
	std::string comment;
	Part();
	Part(int x0, int y0, int width, int height, std::string comment);
	~Part();
};

