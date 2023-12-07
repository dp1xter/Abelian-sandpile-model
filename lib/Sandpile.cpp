#include "parser.h"
#include "process_iterations.h"

int main(int argc, char* argv[]) {
    Config options = ParseCommands(argc, argv);
    Points info_array_points = GetArrayOfPoints(options);
    Field field = Field(info_array_points);

    delete[] info_array_points.points_array;

    ProcessIterations(options, field);
}
