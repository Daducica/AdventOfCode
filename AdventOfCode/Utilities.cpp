#include "Utilities.hpp"

#include <cassert>
#include <fstream>
#include <iostream>
#include <random>

namespace Utilities
{
    std::vector<std::vector<short>> ReadForest (const std::string& fileName)
    {
        std::vector<std::vector<short>> forest;
        std::ifstream fileStream (fileName);
        if (!fileStream.good ()) {
            PrintFileNotFoundMessage (fileName);
            return forest;
        }

        std::string line;
        std::getline (fileStream, line);
        const unsigned int width = line.size ();
        do {
            if (line.size () != width) {
                PrintBadLineLengthMessage (forest.size () + 1, fileName);
                return forest;
            }
            std::vector<short> row (width);
            for (unsigned int i = 0; i < width; i++) {
                row[i] = CharDigitToShort (line[i]);
            }
            forest.emplace_back (row);
        } while (std::getline (fileStream, line));
        return forest;
    }


    short CharDigitToShort (char c)
    {
        const short digit = c - '0';
        if (digit > 9 || digit < 0) {
            PrintNonDigitCharMessage (c);
            return 0;
        }

        return digit;
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


    void PrintFileNotFoundMessage (const std::string& fileName)
    {
        std::cout << "File \"" << fileName << "\" not found" << std::endl;
    }


    void PrintBadLineLengthMessage (short lineNumber, const std::string& fileName)
    {
        std::cout << "Length of line " << lineNumber
            << " differs from that of the earlier lines. (File name = " << fileName << ")" << std::endl;
    }


    void PrintIndexOutOfBondsMessage (int i, int j, int height, int width)
    {
        std::cout << "Index out of bonds error: trying to reach index (" << i << ", " << j << ")"
            << " while dimensions are (" << height << ", " << width << ")" << std::endl;
    }


    void PrintNonDigitCharMessage (char c)
    {
        std::cout << "Trying to convert char " << c << " to a one-digit-number failed." << std::endl;
    }


    void MicroSecTimer::StartTimer ()
    {
        startTime = std::chrono::high_resolution_clock::now ();
    }


    long long MicroSecTimer::StopTimer (const std::optional<std::string>& message /*= std::nullopt*/)
    {
        const Time stopTime = std::chrono::high_resolution_clock::now ();
        const long long duration = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime).count ();
        if (message.has_value ())
            std::cout << message.value () << duration << "microsec" << std::endl;
        return duration;
    }


}