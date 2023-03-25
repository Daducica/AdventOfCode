#ifndef UTILITIES
#define UTILITIES

#include <string>
#include <vector>
#include <chrono>
#include <optional>

namespace Utilities
{
	std::vector<std::vector<short>> ReadForest (const std::string& fileName);
	inline short CharToShort (char c);
	void GenerateNewForestFile (const std::string& fileName, int height, int width);

	class MilliSecTimer {
		using Time = std::chrono::time_point<std::chrono::high_resolution_clock>;
		Time startTime;
	public:
		void StartTimer ();
		int  StopTimer (const std::optional<std::string>& message = std::nullopt);
	};
}

#endif