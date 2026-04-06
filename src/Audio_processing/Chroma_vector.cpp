//Chroma vector creation function implementation file
#include <vector>
#include <cmath>


// Function to compute the chroma vector for a given magnitude spectrum
std::vector<float> compute_chroma(const std::vector<float>& magnitude, int sample_rate, int frame_size)
{
    std::vector<float> chroma(12, 0.0f);// Initialize a vector of size 12 to hold the chroma values for each pitch class (C, C#, D, D#, E, F, F#, G, G#, A, A#, B)

    for (int k = 1; k < magnitude.size(); ++k) {
        float frequency = static_cast<float>(k * sample_rate) / frame_size;// Calculate the frequency corresponding to the k-th bin of the FFT

        if (frequency < 27.5f || frequency > 4186.0f) {continue;}// Ignore frequencies outside piano range (A0 27.5 Hz to C8 4186.0 Hz)

        float midi = 69 + 12 * log2(frequency / 440.0f);// Convert the frequency to a MIDI note number using the formula: MIDI = 69 + 12 * log2(frequency / 440), where 440 Hz corresponds to A4 (MIDI note 69)
        int note = static_cast<int>(std::round(midi)) % 12;// Calculate the pitch class by taking the MIDI note number modulo 12
        if (note < 0) {note += 12;}// Ensure note index is non-negative

        chroma[note] += magnitude[k];
    }

  //normalize the chroma vector by dividing each value by the sum of all values to ensure that the chroma values represent relative intensities rather than absolute magnitudes
  float sum = 0.f;
  for (float v : chroma) {sum += v;}
  if (sum > 0.f){
    for (float& v : chroma) {v /= sum;}
  }


    return chroma;
}



