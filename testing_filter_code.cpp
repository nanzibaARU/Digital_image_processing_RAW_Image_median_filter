#include<bits/stdc++.h>
using namespace std;
const int CHANNELS = 3; // Assuming RGB color channels
std::vector<uint8_t> readRawImage(const std::string& filename, int width, int height) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "Failed to open file: " << filename << std::endl;
        return std::vector<uint8_t>();
    }

    std::vector<uint8_t> image(width * height * CHANNELS);
    file.read(reinterpret_cast<char*>(image.data()), width * height * CHANNELS);

    return image;
}

// Function to apply median filter to a color image (RGB)
std::vector<uint8_t> applyMedianFilter(const std::vector<uint8_t>& inputImage, int width, int height, int filterSize, int pos) {
    std::vector<uint8_t> outputImage(width * height * 3); // Assuming RGB channels

    int padding = filterSize / 2;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            for (int channel = 0; channel < 3; channel++) { // Loop over RGB channels
                std::vector<uint8_t> neighborhood;

                // Extract pixels from the neighborhood
                for (int i = -padding; i <= padding; i++) {
                    for (int j = -padding; j <= padding; j++) {
                        int neighborX = std::min(std::max(x + j, 0), width - 1);
                        int neighborY = std::min(std::max(y + i, 0), height - 1);
                        neighborhood.push_back(inputImage[(neighborY * width + neighborX) * 3 + channel]);
                    }
                }

                // Apply median filter to the neighborhood
                std::sort(neighborhood.begin(), neighborhood.end());
                outputImage[(y * width + x) * 3 + channel] = neighborhood[pos];
            }
        }
    }

    return outputImage;
}
void saveRawImage(const std::string& filename, const std::vector<uint8_t>& image, int width, int height) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }

    file.write(reinterpret_cast<const char*>(image.data()), width * height * CHANNELS);
    std::cout << "Image saved to " << filename << std::endl;
}


int main(){

	string inputFileName1 = "D:\\Project_Images\\img_2.raw";  // Replace with your input file name

    // Read the input image with input image height and width
    int width = 1500, height = 800;
    vector<uint8_t> inputImage1 = readRawImage(inputFileName1, width, height);

    if (!inputImage1 .empty()) {

        for( int i = 3; i <= 7; i+=2){
            int sz = i*i;
            for( int j = 0; j <= 100; j+=10){
                int pos = ceil((j*(sz-1)) / 100);

                 vector<uint8_t> filtered = applyMedianFilter(inputImage1, width, height, i, pos);

                // Save the resized image
                saveRawImage(inputFileName1+"_"+to_string(i)+"_"+to_string(j)+".raw",filtered, width, height);
            }
        }
      

    }

}