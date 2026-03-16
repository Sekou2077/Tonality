// DSP file to handle digital signal processing tasks such as FFT, magnitude , frequency bin calculation, etc.

#include <fftw3.h>
#include "Audio_processing/Music_input.h"

void Dsp()
{
//Declare a plan for the FFT
fftw_plan plan;


int N = Recording.size(); // Get the size of the recorded audio data

try
{

    if (N == 0) {
        throw std::runtime_error("No audio data to process.");
    }


    // Allocate memory for the FFT output
    fftw_complex* fft_result = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * (N / 2 + 1));

    // Create a plan for the FFT(real(audio samples) to complex)
    plan = fftw_plan_dft_r2c_1d(N, Recording.data(), fft_result, FFTW_ESTIMATE);

    // Execute the FFT
    fftw_execute(plan);

    // Clean up the FFT plan
    fftw_destroy_plan(plan);

}


catch (const std::exception& e) {
    std::cout << "Error in DSP processing: " << e.what() << std::endl;
    if (plan) {
        fftw_destroy_plan(plan);
    }
    return;
  }



}