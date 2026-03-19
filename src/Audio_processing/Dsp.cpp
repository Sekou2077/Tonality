// DSP file to handle digital signal processing tasks such as FFT, magnitude , frequency bin calculation, etc.

#include <fftw3.h>
#include "Music_input.h"
#include <vector>
#include <iostream>
#include <stdexcept>

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


    // Allocate memory for the FFT output
    fftwf_complex* fft_result = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex) * (N / 2 + 1));

    // Create a plan for the FFT(real(audio samples) to complex(FFT output))
    plan = fftwf_plan_dft_r2c_1d(N, Recording.data(), fft_result, FFTW_ESTIMATE);

    // Execute the FFT
    fftwf_execute(plan);

    // Clean up the FFT plan
    fftwf_destroy_plan(plan);

}


catch (const std::exception& e) {
    std::cout << "Error in DSP processing: " << e.what() << std::endl;
    if (plan) {
        fftwf_destroy_plan(plan);
    }
    return;
  }



}