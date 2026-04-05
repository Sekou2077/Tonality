// Chroma vector creation function header file
#ifndef CHROMA_VECTOR_H
#define CHROMA_VECTOR_H
#include <vector>

// Function declaration for computing the chroma vector from a given magnitude spectrum, sample rate, and frame size
std::vector<float> compute_chroma(const std::vector<float>& magnitude, int sample_rate,int frame_size);

#endif // CHROMA_VECTOR_H

