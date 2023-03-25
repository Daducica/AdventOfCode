#include "Utilities.hpp"

#include <cassert>
#include <fstream>
#include <iostream>
#include <random>

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
                row[i] = CharToShort (line[i]);
            }
            forest.push_back (row);
        } while (std::getline (fileStream, line));
        fileStream.close ();
        return forest;
    }


    short CharToShort (char c)
    {
        return c - '0';
    }


    void GenerateNewForestFile (const std::string& fileName, int height, int width)
    {
        std::ofstream file;
        file.open (fileName);

        std::random_device randomDevice;
        std::mt19937 generator (randomDevice ());
        std::uniform_int_distribution<> distribution (0, 9);

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                file << distribution (generator);
            }
            file << "\n";
        }

        file.close ();
    }


    void MilliSecTimer::StartTimer ()
    {
        startTime = std::chrono::high_resolution_clock::now ();
    }


    int MilliSecTimer::StopTimer (const std::optional<std::string>& message /*= std::nullopt*/)
    {
        Time stopTime = std::chrono::high_resolution_clock::now ();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stopTime - startTime).count ();
        if (message.has_value ())
            std::cout << message.value () << duration << "ms" << std::endl;
        return static_cast <int> (duration);
    }


}