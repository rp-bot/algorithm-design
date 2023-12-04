#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector<int> readTXTfile() {
    ifstream file("peak.txt");

    vector<int> numbers;
    int value;

    while (file >> value) {
        numbers.push_back(value);
    }

    file.close();

    return numbers;
}


int findPeak(const vector<int>& nums) {
    int low = 0, high = nums.size() - 1;

    while (low < high) {
        int mid = low + (high - low) / 2; // handle integer overflow

        if (nums[mid] < nums[mid + 1]) {
            // The peak is on the right
            low = mid + 1; // low = peak at some point. breaking the loop. because high = mid in the previous iteration
        }
        else {
            // The peak is on the left half, or mid is the peak
            high = mid;
        }
    }

    return low; // low is the index of the peak
}

int main() {
    
    vector<int> nums = readTXTfile();  
    int peakIndex = findPeak(nums);
    cout << "Peak Element Index: " << peakIndex << endl;
    cout << "Peak Element: " << nums[peakIndex] << endl;
    return 0;
}
