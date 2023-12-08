#include "headers/random_generator.hpp"

RandomNumberGenerator::RandomNumberGenerator(int start, int end) {
    srand(static_cast<unsigned int>(time(nullptr)));
    this->startRange = start;
    this->endRange = end;
}

int RandomNumberGenerator::generateRandomNumber() const {
    return rand() % (this->endRange - this->startRange + 1) + this->startRange;
}
