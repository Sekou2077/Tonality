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


void Dsp(std::vector<float>& Recording)
{


//Declare a plan for the FFT
fftwf_plan plan = nullptr; 

int N = Recording.size(); // Get the size of the recorded audio data

try
{

    if (N == 0) {
        throw std::runtime_error("No audio data to process.");
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

    // Clean up the FFT plan
    fftwf_destroy_plan(plan);

    // Free the FFT output memory
    fftwf_free(fft_result);


}


catch (const std::exception& e) {
    std::cout << "Error in DSP processing: " << e.what() << std::endl;
    if (plan) {
        fftwf_destroy_plan(plan);
    }
    return;
  }



}