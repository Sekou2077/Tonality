// Author : Sekou Traore
// Experimental project for music input and processing using graphs : Tonality

#include <iostream>
#include "Audio_processing/Music_input.h"


int main() {

    std::cout << "Welcome to Tonality a!" << std::endl;
    char choice;
    do {
        std::cout << "Please select an option:\n";
        std::cout << "1. Record music\n";
        std::cout << "2. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case '1':
                std::vector<float> Recording; // Create a vector to hold the recorded audio data
                Recording.clear(); // Clear the vector to ensure it's empty before recording
                Audio_input(Recording); // Call the audio input function to fill the Recording vector with audio data
                break;
            case '2':
                std::cout << "Exiting Tonality. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != '2');



    return 0;
}