#include "sandpile.h"

int main(int argc, char* argv[]) {
    Config options = ParseCommands(argc, argv);
    Points info_array_points = GetArrayOfPoints(options);
    Field field = Field(info_array_points);

    ProcessIterations(options, field);
}
