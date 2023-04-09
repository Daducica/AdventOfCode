#ifndef UTILITIES
#define UTILITIES

#include <string>
#include <vector>
#include <chrono>
#include <optional>

namespace Utilities
{
	std::vector<std::vector<short>> ReadForest (const std::string& fileName);
	short CharDigitToShort (char c);
	void GenerateNewForestFile (const std::string& fileName, int height, int width);

	void PrintFileNotFoundMessage (const std::string& fileName);
	void PrintBadLineLengthMessage (short lineNumber, const std::string& fileName);
	void PrintIndexOutOfBondsMessage (int i, int j, int height, int width);
	void PrintNonDigitCharMessage (char c);

	class MilliSecTimer {
		using Time = std::chrono::time_point<std::chrono::high_resolution_clock>;
		Time startTime;
	public:
		void StartTimer ();
		int  StopTimer (const std::optional<std::string>& message = std::nullopt);
	};
}

#endif