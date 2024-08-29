#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

namespace cli{
//Command-line interface

    class UI{
        public:
            UI(int goal);
            void addRacer(int id, std::string asciiFilename);
            void initPrint();
            void printText(std::string text);
            void update(std::vector<int>);
        private:
            void initTrack(int trackHeight, int airHeight);

            struct Racer{
                int id;
                int width;
                int yPos;
                int xPos;
                std::vector<std::string> asciiTextLines;
                std::vector<int> asciiOffset;
            };
            std::vector<std::string> _track;
            std::vector<Racer> _racers;

            int _goal;

            int _trackHeight;
            int _printWidth;
            int _startWidth;
            int _goalWidth;
            int _raceWidth;
            std::string _goalText;
    };
}

