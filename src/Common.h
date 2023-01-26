#pragma once
#include <string>
#include <cmath>
#include <vector>

namespace Common
{
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
        AGRESSIVE
    };

    const std::string TITLE = "Cavern";

    constexpr int WIDTH = 800;
    constexpr int HEIGHT = 480;

    constexpr int NUM_ROWS = 18;
    constexpr int NUM_COLUMNS = 28;
    constexpr int LEVEL_X_OFFSET = 50;
    constexpr int GRID_BLOCK_SIZE = 25;
    //const Anchor ANCHOR_CENTRE = { "center", "center" };
    //const Anchor ANCHOR_CENTRE_BOTTOM = { "center", "bottom" };
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