#include "parser.h"

bool IsNumeric(const char* number) {
    while (*number != '\0') {
        if (!std::isdigit(*number)) {
            return false;
        }
        ++number;
    }

    return true;
}

void RaiseError(const char* message) {
    std::cerr << message;
    exit(EXIT_FAILURE);
}

const char* ParseInputFile(const char* input_file) {
    std::ifstream file(input_file);
    if (!file.is_open() || strcmp(&input_file[strlen(input_file) - kFileExtensionTSV], ".tsv")) {
        RaiseError("Invalid input file.");
    }

    return input_file;
}

const char* ParseOutputDir(const char* directory) {
    if (!std::filesystem::is_directory(directory)) {
        RaiseError("Invalid directory.");
    }

    return directory;
}

size_t ParseNumberArgs(const char* number_arg) {
    if (!IsNumeric(number_arg) || !strlen(number_arg)) {
        RaiseError("Invalid freq or iterations parameter.");
    }

    return std::stoll(number_arg);
}

Config ParseCommands(int argc, char* argv[]) {
    bool waiting_file = false;
    bool waiting_dir = false;
    bool waiting_iterations = false;
    bool waiting_freq = false;
    Config options;

    for (int i = 1; i < argc; ++i) {
        if (waiting_file) {
            options.input_file = ParseInputFile(argv[i]);
            waiting_file = false;
        } else if (waiting_dir) {
            options.output_dir = ParseOutputDir(argv[i]);
            waiting_dir = false;
        } else if (waiting_iterations) {
            options.maximum_iterations = ParseNumberArgs(argv[i]);
            waiting_iterations = false;
        } else if (waiting_freq) {
            options.freq = ParseNumberArgs(argv[i]);
            waiting_freq = false;
        } else if (!strncmp(argv[i], "--input=", kMinimalLengthInputFile)) {
            options.input_file = ParseInputFile(&argv[i][kMinimalLengthInputFile]);
        } else if (!strncmp(argv[i], "--output=", kMinimalLengthOutputDir)) {
            options.output_dir = ParseOutputDir(&argv[i][kMinimalLengthOutputDir]);
        } else if (!strncmp(argv[i], "--max-iter=", kMinimalLengthIterations)) {
            options.maximum_iterations = ParseNumberArgs(&argv[i][kMinimalLengthIterations]);
        } else if (!strncmp(argv[i], "--freq=", kMinimalLengthFreq)) {
            options.freq = ParseNumberArgs(&argv[i][kMinimalLengthFreq]);
        } else if (!strcmp(argv[i], "-i")) {
            waiting_file = true;
        } else if (!strcmp(argv[i], "-o")) {
            waiting_dir = true;
        } else if (!strcmp(argv[i], "-m")) {
            waiting_iterations = true;
        } else if (!strcmp(argv[i], "-f")) {
            waiting_freq = true;
        } else {
            RaiseError("Invalid options.");
        }
    }

    if (waiting_file || waiting_dir || waiting_iterations || waiting_freq ||
        options.input_file.empty() || options.output_dir.empty()) {
        RaiseError("Invalid parameters.");
    }

    return options;
}
