#ifndef BOMBER_MAN_RANDOM_GENERATOR_HPP
#define BOMBER_MAN_RANDOM_GENERATOR_HPP

#include <cstdlib>
#include <ctime>


class RandomNumberGenerator {
private:
    int startRange;
    int endRange;

public:
    RandomNumberGenerator(int start, int end);

    int generateRandomNumber();
};

#endif
