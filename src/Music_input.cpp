// Author : Sekou Traore
// Experimental project for music input and processing(just wild ideas for now)

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
    
    // Define constants for sample rate and frames per buffer
    const int Sample_rate = 44100; // standard CD quality sample rate
    const int Frames_per_buffer = 256; // small buffer size for low latency


    // Declare a stream pointer
    PaStream* stream;

    //set up the stream
    err = Pa_OpenStream(
        &stream, // stream pointer
        &inputParameters, // input parameters
        NULL, // no output parameters since we're only recording
        Sample_rate, // sample rate
        Frames_per_buffer, // frames per buffer
        paNoFlag, // no special flags
        NULL, // no callback, use blocking I/O
        NULL // no stream callback user data
    );

    // Check if stream opened successfully
    if (err != paNoError) {
        std::cout << "Failed to open the stream!\n";
        Pa_Terminate();
        return 1;
    }

// Start the stream



    // Terminate PortAudio
    Pa_Terminate();

    // Return success
    return 0;
}