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
 
    std::cout << "PortAudio initialized beautifully!\n";

    int numDevices = Pa_GetDeviceCount();
    std::cout << "Number of audio devices: " << numDevices << "\n";

    Pa_Terminate();
}