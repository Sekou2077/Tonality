// DSP file to handle digital signal processing tasks such as FFT, magnitude , frequency bin calculation, etc.

#include <fftw3.h>
#include "Music_input.h"
#include <vector>
#include <iostream>
#include <stdexcept>
#include <cmath>


// Function to apply a Hann window to the recorded audio data before
// performing the FFT. This helps to reduce spectral leakage in the FFT results.
// use f version of cos and PI for better performance with float recording data
void hann_window(std::vector<float>& Recording) {
    int N = Recording.size();
    constexpr float PI = 3.14159265358979323846f;
    for (int n = 0; n < N; ++n) {
        Recording[n] *= 0.5f * (1.0f - cosf(2.0f * PI * n / (N - 1)));
    }
}



std::vector<float> Dsp(std::vector<float>& Recording)
{


//Declare a plan for the FFT
fftwf_plan plan = nullptr;

//Declare magnitude vector to hold the magnitude of the FFT results
std::vector<float> magnitude;

int N = Recording.size(); // Get the size of the recorded audio data

if (N == 0) {
        throw std::runtime_error("Cannot proceed, no audio data available.");
    }

// Apply the Hann window to the recorded audio data(in-place)
hann_window(Recording);

// Allocate memory for the FFT output
fftwf_complex* fft_result = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * (N / 2 + 1));

// Check if memory allocation was successful
if (fft_result== nullptr) {
        throw std::runtime_error("Failed to allocate memory for FFT output.");
    }

// Create a plan for the FFT(real(audio samples) to complex(FFT output))
plan = fftwf_plan_dft_r2c_1d(N, Recording.data(), fft_result, FFTW_ESTIMATE);


// Execute the FFT
fftwf_execute(plan);


// Calculate the magnitude of the FFT results
int num_bins = N / 2 + 1; // Number of frequency bins for real-to-complex FFT
magnitude.resize(num_bins);
for (int i = 0; i < num_bins; ++i) {
        float real_part = fft_result[i][0]; // Real part of the FFT output
        float imag_part = fft_result[i][1]; // Imaginary part of the FFT output
        magnitude[i] = sqrtf(real_part * real_part + imag_part * imag_part); // Magnitude calculation(sqrt(re^2 + im^2))
    }


// Clean up the FFT plan
fftwf_destroy_plan(plan);

// Free the FFT output memory
fftwf_free(fft_result);

 return magnitude; // Return the magnitude vector containing the FFT results

}







