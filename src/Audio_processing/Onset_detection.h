// Onset_detection header file

#ifndef TONALITY_ONSET_DETECTION_H // If not defined, define it to prevent multiple inclusions
#define TONALITY_ONSET_DETECTION_H //   Define the header guard
#include <vector>

std::vector<int> Onset_detection(const std::vector<float>& flux, float multiplier = 1.5f); // Function declaration for the onset detection function

#endif // TONALITY_ONSET_DETECTION_H

