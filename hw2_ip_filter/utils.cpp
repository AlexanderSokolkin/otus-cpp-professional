#include "utils.h"
#include "version.h"

#include <filesystem>
#include <cstring>



ArgsSet parseArgs(int argc, char* argv[]) noexcept
{
	switch (argc) {
		case 1:
			return StdIstream;
		case 2:
			if (strcmp(argv[1], "--help") == 0) {
				return Help;
			}
			return File;
		default:
			return InvalidArgs;
	}
}

void printHelp(std::ostream& out)
{
	const char* help = 	"ip_filter reads input data either from a file or from a standard input stream."
						"file: ip_filter <filename>"
						"standard input: echo text | ip_filter or just ip_filter and sequential text "
						"input with a signal to simulate the end of the file (depends on the OS).\n"
						"\tAvailable arguments:\n"
						"\t\t--help - print current help.\n";

	out << help;
}

int version_patch() noexcept
{
	return PROJECT_VERSION_PATCH;
}

bool fileExists(const char* filename) noexcept
{
	try {
		return std::filesystem::exists(filename);
	}
	catch(...) {
		return false;
	}
}
