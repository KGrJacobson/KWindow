#ifndef FILE_HANDLER
#define FILE_HANDLER
#include <fstream>
#include <string>

class FileHandler
{
public:

private:
	std::string filename_;
	std::fstream filestream_;
	uint8_t dataflag_;
	uint16_t nextbytesize_;
};

#endif //FILE_HANDLER