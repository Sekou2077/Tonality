//DSP header file

#ifndef TONALITY_DSP_H // If not defined, define it to prevent multiple inclusions
#define TONALITY_DSP_H //   Define the header guard

std::vector<float> Dsp(std::vector<float>& Recording); // Function declaration for the DSP processing function
std::vector<std::vector<float>> Create_frames(const std::vector<float>& recording, int frame_size, int hop_size); // Function declaration for creating frames from the recorded audio data

#endif // TONALITY_DSP_H
