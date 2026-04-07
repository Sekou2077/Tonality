// Author : Sekou Traore
// Experimental project for music input and processing using graphs : Tonality

#include <iostream>
#include "Audio_processing/Music_input.h"
#include "Audio_processing/Dsp.h"
#include "Audio_processing/Onset_detection_timestamps.h"
#include "Audio_processing/Chroma_vector.h"
#include "Audio_processing/Graph.h"
#include <vector>
#include <stdexcept>


std::vector<float> Recording; // Create a vector to hold the recorded audio data



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
                std::cout << "Recording size: " << Recording.size() << "\n";
                // (test) Print the first few samples of the recorded audio data for verification
                for (int i = 0; i < 10; ++i)
                {
                    std::cout << "sample[" << i << "] = " << Recording[i] << "\n";
                }
                break;
            case '2':
                try
                {
                    if (Recording.empty()) {
                        throw std::runtime_error("No audio data to process. Please record audio first.");
                    }

                    int frame_size = 1024; // Define the size of each frame (number of samples per frame)
                    int hop_size = 512; // Define the hop size (number of samples to move for the next frame, 50% overlap in this case)
                    int sample_rate = 44100; // Define the sample rate of the audio data (samples per second)

                    auto frames = Create_frames(Recording, frame_size, hop_size); // Create frames from the recorded audio data
                    std::vector<std::vector<float>> magnitude_frames; // Create a vector to hold the magnitude of each frame for DSP processing
                    for ( auto frame : frames) {
                        magnitude_frames.push_back(Dsp(frame)); // Process each frame with the Dsp function and store the magnitude results
                    }

                    std::cout<<"Size of magnitude frames: "<<magnitude_frames.size()<<std::endl; //(test)Print the size of the magnitude frames vector to verify that processing was done

                    // might create a separate function later to unclutter the main function, but for now I'll keep it here for testing purposes
                    std::vector<float>flux; // Create a vector to hold the spectral flux values for each frame
                    for (size_t i = 1; i < magnitude_frames.size(); ++i) {
                        float flux_value = 0.0f; // Initialize the spectral flux value for the current frame
                        for (size_t j = 0; j < magnitude_frames[i].size(); ++j) {
                            float diff = magnitude_frames[i][j] - magnitude_frames[i - 1][j]; // Calculate the difference in magnitude between the current frame and the previous frame
                            if (diff > 0) {
                                flux_value += diff; // Accumulate only positive differences to calculate the spectral flux for onset detection
                            }
                        }
                        flux.push_back(flux_value); // Store the accumulated spectral flux value for the current frame
                    }
                    std::cout<<"Size of spectral flux vector: "<<flux.size()<<std::endl; //(test)Print the size of the spectral flux vector to verify that it was calculated correctly

                    //(test) Print the first few spectral flux values for verification
                    for (size_t i = 0; i < std::min(flux.size(), size_t(10)); ++i)
                    {
                        std::cout << "flux[" << i << "] = " << flux[i] << "\n";
                    }
                 // (test) Print the maximum sample value in the original recording for reference
                 float max_sample = *std::max_element(Recording.begin(), Recording.end());
                 std::cout << "Max sample value: " << max_sample << "\n";

                 auto onsets = Onset_detection(flux); // Call the onset detection function with the calculated spectral flux values to identify onsets in the audio signal
                 // (test) Print the detected onsets for verification
                 std::cout << "Detected onsets at frame indices: ";
                 for (int onset : onsets) {
                     std::cout << onset << " ";
                 }
                 std::cout << "\n";


                auto timestamps = timestamp_to_seconds(onsets, sample_rate, hop_size, frame_size); // Convert the detected onset frame indices to timestamps in seconds using the sample rate, hop size, and frame size
               // (test) Print the detected onsets as timestamps in seconds for verification
                std::cout << "Detected onsets at timestamps (seconds): ";
                for (float timestamp : timestamps) {
                    std::cout << timestamp << " ";
                }
                std::cout << "\n";

                std::vector<std::vector<float>> chroma_vectors; // Create a vector to hold the chroma vectors for each frame
                for(int onset : onsets) {
                    chroma_vectors.push_back(compute_chroma(magnitude_frames[onset], sample_rate, frame_size)); // Calculate the chroma vector for each detected onset frame and store it in the chroma_vectors vector
                }

                // (test) Print the first few chroma vectors for verification
                for (size_t i = 0; i < std::min(chroma_vectors.size(), size_t(5)); ++i) {
                    std::cout << "Chroma vector for onset " << i << ": ";
                    for (float value : chroma_vectors[i]) {
                        std::cout << value << " ";
                    }
                    std::cout << "\n";
                }

                std::vector<Node> graph_nodes; // Create a vector to hold the nodes of the graph
                for (size_t i = 0; i < timestamps.size(); ++i) {
                    Node node; // Create a new node for each detected onset
                    node.timestamp = timestamps[i]; // Set the timestamp of the node to the corresponding onset timestamp
                    node.chroma_vector = chroma_vectors[i]; // Set the chroma vector of the node to the corresponding chroma vector calculated for that onset
                    graph_nodes.push_back(node); // Add the node to the graph_nodes vector
                }

                // (test) Print the graph nodes with their timestamps and chroma vectors for verification
                for (size_t i = 0; i < std::min(graph_nodes.size(), size_t(5)); ++i) {
                    std::cout << "Node " << i << ": Timestamp = " << graph_nodes[i].timestamp << " seconds, Chroma vector = ";
                    for (float value : graph_nodes[i].chroma_vector) {
                        std::cout << value << " ";
                    }
                    std::cout << "\n";
                }

                std::vector<Edge> graph_edges; // Create a vector to hold the edges of the graph
                for (size_t i = 0; i < graph_nodes.size(); ++i)
                {


                }


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
