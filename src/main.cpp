// Author : Sekou Traore
// Experimental project for music input and processing using graphs : Tonality

#include <iostream>
#include "Audio_processing/Music_input.h"
#include "Audio_processing/Dsp.h"


std::vector<float> Recording; // Create a vector to hold the recorded audio data

int main() {

    std::cout << "Welcome to Tonality test!" << std::endl;
    char choice;
    do {
        std::cout << "Please start a recording first and then process it :\n";
        std::cout << "1. Record music\n";
        std::cout << "2. Process music (DSP)\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case '1':
                Recording.clear(); // Clear the Recording vector before recording new audio data
                Audio_input(Recording); // Call the audio input function to fill the Recording vector with audio data
                break;
            case '2':
                std::vector<float> magnitude = Dsp(Recording); // Call the DSP function to process the recorded audio data and get the magnitude of the FFT results



                break;
            case '3':
                std::cout << "Exiting Tonality. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != '3');



    return 0;
}
