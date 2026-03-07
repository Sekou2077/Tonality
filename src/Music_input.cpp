// Author : Sekou Traore
// Experimental project for music input and processing

#include <iostream>
#include <portaudio.h>


using namespace std;

int main() {
    
     PaError err = Pa_Initialize();
    if (err != paNoError) {
        std::cout << "PortAudio init failed!\n";
        return 1;
    }

    std::cout << "PortAudio initialized beautifully!\n";

    int numDevices = Pa_GetDeviceCount();
    std::cout << "Number of audio devices: " << numDevices << "\n";

    Pa_Terminate();
}