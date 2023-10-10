#include <iostream>
#include <bitset>

using namespace std;

// Function to calculate the parity bit for a given data word
int calculateParityBit(int data, int parityPositions) {
    int parityBit = 0;
    for (int i = 0; i < parityPositions; i++) {
        if (data & (1 << i)) {
            parityBit ^= 1;
        }
    }
    return parityBit;
}

// Function to encode a 4-bit data word using Hamming(7,4) code
int encodeHamming74(int data) {
    // Calculate the parity bits
    int p1 = calculateParityBit(data, 1);
    int p2 = calculateParityBit(data, 2);
    int p4 = calculateParityBit(data, 4);

    // Create the Hamming code word
    int hammingCode = (p1 << 0) | (p2 << 1) | (data << 2) | (p4 << 6);

    return hammingCode;
}

// Function to decode a received Hamming(7,4) code word
int decodeHamming74(int receivedCode) {
    // Calculate the syndrome bits
    int s1 = calculateParityBit(receivedCode, 1);
    int s2 = calculateParityBit(receivedCode, 2);
    int s4 = calculateParityBit(receivedCode, 4);

    int syndrome = (s1 << 0) | (s2 << 1) | (s4 << 2);

    if (syndrome == 0) {
        return receivedCode >> 2;
    } else {
        // Calculate the position of the error and correct it
        int errorPosition = s1 | (s2 << 1) | (s4 << 2);
        cout << "Error at position " << errorPosition << endl;
        receivedCode ^= (1 << (7 - errorPosition)); // Correct the error
        cout << "Corrected code: " << bitset<7>(receivedCode) << endl;
        return receivedCode >> 2;
    }
}

int main() {
    int data = 7; // 4-bit data to encode

    int encodedData = encodeHamming74(data);
    cout << "Encoded data: " << bitset<7>(encodedData) << endl;

    int receivedData = encodedData; // Simulate received data
    int decodedData = decodeHamming74(receivedData);
    cout << "Decoded data: " << bitset<4>(decodedData) << endl;

    return 0;
}
