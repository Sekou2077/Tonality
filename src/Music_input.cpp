// Author : Sekou Traore
// Experimental project for music input and processing

#include <iostream>
#include <portaudio.h>


using namespace std;

int main() {
    
     // Initialize PortAudio
     PaError err = Pa_Initialize();
     // Return an error code if initialization fails
    if (err != paNoError) {
        std::cout << "PortAudio init failed!\n";
        return 1;
    }
 
    // set up input parameters
    PaStreamParameters inputParameters;
    inputParameters.device = Pa_GetDefaultInputDevice(); // default input device
    inputParameters.channelCount = 2; // stereo input
    inputParameters.sampleFormat = paFloat32; // 32 bit floating point compatible with most audio APIs
    inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;// use default low latency settings
    inputParameters.hostApiSpecificStreamInfo = NULL; // no specific stream info
    


    // Terminate PortAudio
    Pa_Terminate();
}