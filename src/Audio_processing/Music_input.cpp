// Audio processing implementation files 

#include <iostream>
#include <portaudio.h>
#include <vector>

using namespace std;

int Audio_input() {
    
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
    
    // Define constants for sample rate ,frames per buffer and recording duration
    const int Sample_rate = 44100; // standard CD quality sample rate
    const int Frames_per_buffer = 256; // small buffer size for low latency
    const int Recording_duration_seconds = 5; // record for 60 seconds

    //declare a buffer to hold the recorded audio data
    std::vector<float> Sampleblock(Frames_per_buffer * inputParameters.channelCount); 


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
    err = Pa_StartStream(stream);
    // Check if stream started successfully
    if (err != paNoError) {
        std::cout << "Failed to start the stream!\n";
        Pa_CloseStream(stream);
        Pa_Terminate();
        return 1;
    }
    else {
        std::cout << "Stream started successfully! Recording...\n"<< std::endl;
    }


    // Main audio processing loop

    for (int i=0; i < (Recording_duration_seconds * Sample_rate) / Frames_per_buffer; ++i)
     {
        err=Pa_ReadStream(stream, Sampleblock.data(), Frames_per_buffer);
        // Check if read was successful
        if (err != paNoError) {
            std::cout << "Failed to read from the stream!\n";
            break;
        }

    }



    // Stop the stream
    err = Pa_StopStream(stream);
    // Check if stream stopped successfully
    if (err != paNoError) {
        std::cout << "Failed to stop the stream!\n";
    }


    // Close the stream
    err = Pa_CloseStream(stream);
    // Check if stream closed successfully
    if (err != paNoError) {
        std::cout << "Failed to close the stream!\n";
    }
    else {
        std::cout << "Stream closed successfully!\n";
    }

    // Terminate PortAudio
    Pa_Terminate();

    // Return success
    return 0;
}