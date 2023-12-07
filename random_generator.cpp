#include "headers/random_generator.hpp"

RandomNumberGenerator::RandomNumberGenerator(int start, int end) {
    srand(static_cast<unsigned int>(time(0)));
    this->startRange = start;
    this->endRange = end;
}

int  RandomNumberGenerator::generateRandomNumber() {
    return rand() % (this->endRange - this->startRange + 1) + this->startRange;
}
