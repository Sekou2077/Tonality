// Author : Sekou Traore
// Experimental project for music input and processing using graphs : Tonality

#include <iostream>
#include "Audio_processing/Music_input.h"
#include "Audio_processing/Dsp.h"
#include <vector>
#include <stdexcept>


std::vector<float> Recording; // Create a vector to hold the recorded audio data



std::vector<std::vector<float>>Create_frames(const std::vector<float>& recording, int frame_size, int hop_size)// Create frames from the recorded audio data using the specified frame size and hop size
                {
                    // Create frames from the recorded audio data
                    std::vector<std::vector<float>> frames;

                    for (size_t i = 0; i + frame_size <= recording.size(); i += hop_size) {
                        frames.emplace_back(recording.begin() + i, recording.begin() + i + frame_size);
                    }

                    return frames; // Return the vector of frames
                }



int main() {

    std::cout << "Welcome to Tonality test!" << std::endl;
    char choice;
    do {
        std::cout << "Please start a recording first and then process it :\n";
        std::cout << "1. Record audio or (re-record)\n";
        std::cout << "2. Process audio data (DSP)\n";
        std::cout << "3. Exit\n";
        std::cout << "What would you like to do?\n";
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
                        throw std::runtime_error("No audio data to process. Please record audio first.");
                    }

                    int frame_size = 1024; // Define the size of each frame (number of samples per frame)
                    int hop_size = 512; // Define the hop size (number of samples to move for the next frame, 50% overlap in this case)


                    auto frames = Create_frames(Recording, frame_size, hop_size); // Create frames from the recorded audio data
                    std::vector<std::vector<float>> magnitude_frames; // Create a vector to hold the magnitude of each frame for DSP processing
                    for ( auto frame : frames) {
                        magnitude_frames.push_back(Dsp(frame)); // Process each frame with the Dsp function and store the magnitude results
                    }

                    std::cout<<"Size of magnitude frames: "<<magnitude_frames.size()<<std::endl; //(test)Print the size of the magnitude frames vector to verify that processing was done
                }
                catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                    break;
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
