#include "Utilities.hpp"

#include <cassert>
#include <fstream>
#include <iostream>
#include <random>

namespace Utilities
{
    ForestMatrix ReadForest (const std::string& fileName)
    {
        ForestMatrix forest;
        std::ifstream fileStream (fileName);
        if (!fileStream.good ()) {
            PrintFileNotFoundMessage (fileName);
            return forest;
        }

        std::string line;
        std::getline (fileStream, line);
        const size_t width = line.size ();
        do {
            if (line.size () != width) {
                PrintBadLineLengthMessage (forest.size () + 1, fileName);
                return forest;
            }
            ForestRow row (width);
            for (size_t rowIndex = 0; rowIndex < width; rowIndex++) {
                row[rowIndex] = CharDigitToTreeHeight (line[rowIndex]);
            }
            forest.emplace_back (row);
        } while (std::getline (fileStream, line));
        return forest;
    }


    TreeHeight CharDigitToTreeHeight (char c)
    {
        const TreeHeight digit = c - '0';
        if (digit > 9 || digit < 0) {
            PrintNonDigitCharMessage (c);
            return 0;
        }

        return digit;
    }


    void GenerateNewForestFile (const std::string& fileName, size_t height, size_t width)
    {
        std::ofstream file;
        file.open (fileName);

        std::random_device randomDevice;
        std::mt19937 generator (randomDevice ());
        std::uniform_int_distribution<> distribution (0, 9);

        for (size_t row = 0; row < height; row++) {
            for (size_t col = 0; col < width; col++) {
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


    void PrintBadLineLengthMessage (size_t lineNumber, const std::string& fileName)
    {
        std::cout << "Length of line " << lineNumber
            << " differs from that of the earlier lines. (File name = " << fileName << ")" << std::endl;
    }


    void PrintIndexOutOfBondsMessage (size_t i, size_t j, size_t height, size_t width)
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