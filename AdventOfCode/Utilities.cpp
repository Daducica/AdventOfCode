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


    void GenerateNewForestFile (const std::string& fileName)
    {
        std::ofstream myfile;
        myfile.open (fileName);

        std::random_device rd;
        std::mt19937 gen (rd ());
        std::uniform_int_distribution<> distr (0, 9);

        for (int i = 0; i < 1000; i++) {
            for (int j = 0; j < 1000; j++) {
                myfile << distr (gen);
            }
            myfile << "\n";
        }

        myfile.close ();
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