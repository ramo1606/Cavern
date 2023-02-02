#pragma once
#include <string>
#include <cmath>
#include <vector>

namespace Common
{
    //ENUMS
    enum class FRUIT_TYPE : std::uint8_t
    {
        APPLE,
        RASPBERRY,
        LEMON,
        EXTRA_HEALTH,
        EXTRA_LIFE
    };

    enum class ROBOT_TYPE : std::uint8_t
    {
        NORMAL,
        AGRESSIVE,
        NONE
    };

    enum class POP_TYPE : std::uint8_t
    {
        FRUIT,
        ENEMY
    };

    //CONSTANTS
    const std::string TITLE = "Cavern";

    constexpr int WIDTH = 800;
    constexpr int HEIGHT = 480;

    constexpr int NUM_ROWS = 18;
    constexpr int NUM_COLUMNS = 28;

    constexpr int LEVEL_X_OFFSET = 50;
    constexpr int GRID_BLOCK_SIZE = 25;

    // Widths of the letters A to Z in the font images
    const char CHAR_WIDTH[] = { 27, 26, 25, 26, 25, 25, 26, 25, 12, 26, 26, 25, 33, 25, 26,
                                25, 27, 26, 26, 25, 26, 26, 38, 25, 25, 25 };

    //LEVELS
    const std::vector<std::vector<std::string>> LEVELS = { {"XXXXX     XXXXXXXX     XXXXX",
                                                            "", "", "", "",
                                                            "   XXXXXXX        XXXXXXX   ",
                                                            "", "", "",
                                                            "   XXXXXXXXXXXXXXXXXXXXXX   ",
                                                            "", "", "",
                                                            "XXXXXXXXX          XXXXXXXXX",
                                                            "", "", ""},

                                                            {"XXXX    XXXXXXXXXXXX    XXXX",
                                                            "", "", "", "",
                                                            "    XXXXXXXXXXXXXXXXXXXX    ",
                                                            "", "", "",
                                                            "XXXXXX                XXXXXX",
                                                            "      X              X      ",
                                                            "       X            X       ",
                                                            "        X          X        ",
                                                            "         X        X         ",
                                                            "", "", ""},

                                                            {"XXXX    XXXX    XXXX    XXXX",
                                                            "", "", "", "",
                                                            "  XXXXXXXX        XXXXXXXX  ",
                                                            "", "", "",
                                                            "XXXX      XXXXXXXX      XXXX",
                                                            "", "", "",
                                                            "    XXXXXX        XXXXXX    ",
                                                            "", "", ""} };
}