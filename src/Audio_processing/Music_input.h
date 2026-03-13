// Music input header file

#ifndef TONALITY_MUSIC_INPUT_H // If not defined, define it to prevent multiple inclusions
#define TONALITY_MUSIC_INPUT_H //   Define the header guard
#include <vector>



int Audio_input(std::vector<float>& Recording); // Makes the audio data available to other parts of the program by passing a reference to a vector that will hold the recorded audio data

#endif // TONALITY_MUSIC_INPUT_H