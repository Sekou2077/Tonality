// Function to perform onset detection using spectral flux
//onsets are detected when the spectral flux exceeds a specified threshold, indicating a significant change in the audio signal that may correspond to a musical event such as a note onset or beat.
// Time-stamping the detected onsets allows us to know exactly when these events occur in the audio signal

#include <vector>



// Perform onset detection using spectral flux
std::vector<int> Onset_detection(const std::vector<float>& flux, float multiplier = 1.5f) {
    std::vector<int> onsets;

    float mean = 0.f;
    for (float v : flux) mean += v;
    mean /= flux.size();
    float threshold = mean * multiplier;// Set the threshold for onset detection based on the mean spectral flux multiplied by a user-defined multiplier

    // Detect onsets where the spectral flux exceeds the threshold and is a local maximum
    // Threshold alone would trigger on any sustained loud passage, so we also check for local maxima to ensure that we are detecting actual onsets
    for (size_t i = 1; i < flux.size() - 1; ++i) {
        if (flux[i] > threshold &&
            flux[i] > flux[i - 1] &&
            flux[i] > flux[i + 1]) {
            onsets.push_back(i);
        }
    }

    return onsets;
}


// Convert frame index to timestamp in seconds
std::vector <float> timestamp_to_seconds(const std::vector<int>& frame_indices, int sample_rate, int hop_size, int frame_size) {
    std::vector<float> timestamps;
    for (int frame_index : frame_indices) {
        timestamps.push_back((frame_index * hop_size + frame_size / 2) / static_cast<float>(sample_rate));
    }
    return timestamps;
}

