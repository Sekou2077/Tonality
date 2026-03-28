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
                try
                {
                    if (Recording.empty()) {
                        throw std::runtime_error("No audio data to process. Please record music first.");
                    }

                    std::vector<std::vector<float>>Create_frames(std::vector<float>& Recording, int frame_size, int hop_size); // Create frames from the recorded audio data using the specified frame size and hop size
                {
                    int frame_size = 1024; // Define the size of each frame (number of samples per frame)
                    int hop_size = 512; // Define the hop size (number of samples to move for the next frame, 50% overlap in this case)

                    // Create frames from the recorded audio data
                    std::vector<std::vector<float>> frames;

                    for (size_t i = 0; i + frame_size <= Recording.size(); i += hop_size) {
                        frames.emplace_back(Recording.begin() + i, Recording.begin() + i + frame_size);
                    }

                }


                }
                catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                    break; // Exit the case if there's an error
                }

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
