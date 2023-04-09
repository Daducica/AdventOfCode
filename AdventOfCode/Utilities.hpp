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
	void GenerateNewForestFile (const std::string& fileName, size_t height, size_t width);

	void PrintFileNotFoundMessage (const std::string& fileName);
	void PrintBadLineLengthMessage (size_t lineNumber, const std::string& fileName);
	void PrintIndexOutOfBondsMessage (size_t i, size_t j, size_t height, size_t width);
	void PrintNonDigitCharMessage (char c);

	class MicroSecTimer {
		using Time = std::chrono::time_point<std::chrono::high_resolution_clock>;
		Time startTime;
	public:
		void StartTimer ();
		long long  StopTimer (const std::optional<std::string>& message = std::nullopt);
	};
}

#endif