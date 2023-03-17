#include "Utilities.hpp"

#include <fstream>
#include <iostream>
#include <cassert>

namespace Utilities
{
    std::vector<std::vector<short>> ReadForest (const std::string& fileName)
    {
        std::ifstream fileStream (fileName);
        std::string line;
        std::vector<std::vector<short>> forest;
        std::getline (fileStream, line);
        const unsigned int width = line.size ();
        do {
            std::vector<short> row (width);
            for (unsigned int i = 0; i < width; i++) {
                row[i] = CharToShort (line[i] - '0');
            }
            forest.push_back (row);
        } while (std::getline (fileStream, line));
        return forest;
    }


    short CharToShort (char c)
    {
        return c - '0';
    }


    void Timer::StartTimer ()
    {
        startTime = std::chrono::high_resolution_clock::now ();
    }


    int Timer::StopTimer (const std::optional<std::string>& message /*= std::nullopt*/,
                           const std::optional<int>& maxDuration /*= std::nullopt*/)
    {
        Time stopTime = std::chrono::high_resolution_clock::now ();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stopTime - startTime).count ();
        if (message.has_value ())
            std::cout << message.value ();
        std::cout << duration << "ms" << std::endl;
        if (maxDuration.has_value ())
            assert (duration < maxDuration);
        return static_cast <int> (duration);
    }


}