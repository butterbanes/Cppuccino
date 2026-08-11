#ifndef FLOAT_H
#define FLOAT_H

#include <climits>
#include <cstdint>
#include <limits>

#include "./Byte.h"


template<typename T>
using nlim = std::numeric_limits<T>;

class Float {
    private:
        float fValue;
    public:
        static constexpr int8_t SIZE = 32;
        static constexpr int8_t BYTES = SIZE / Byte::SIZE;
        static constexpr int8_t PRECISION = 24;
        static constexpr int8_t MAX_EXPONENT = nlim<float>::max_exponent;
        static constexpr int8_t MIN_EXPONENT = nlim<float>::min_exponent;
        static constexpr float MAX_VALUE = nlim<float>::max();
        static constexpr float MIN_VALUE = nlim<float>::denorm_min();
        static constexpr float MIN_NORMAL = nlim<float>::min();
        static constexpr float NaN = nlim<float>::signaling_NaN(); // want to throw
        static constexpr float NEGATIVE_INFINITY = -nlim<float>::infinity();
        static constexpr float POSITIVE_INFINITY = nlim<float>::infinity();
};

#endif //FLOAT_H