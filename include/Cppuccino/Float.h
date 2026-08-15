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
        static constexpr int16_t MAX_EXPONENT = nlim<float>::max_exponent;
        static constexpr int16_t MIN_EXPONENT = nlim<float>::min_exponent;
        static constexpr float MAX_VALUE = nlim<float>::max();
        static constexpr float MIN_VALUE = nlim<float>::denorm_min();
        static constexpr float MIN_NORMAL = nlim<float>::min();
        static constexpr float NaN = nlim<float>::signaling_NaN(); // want to throw
        static constexpr float NEGATIVE_INFINITY = -nlim<float>::infinity();
        static constexpr float POSITIVE_INFINITY = nlim<float>::infinity();

        Float(double value) : fValue(static_cast<float>(value)) {};
        Float(float value) : fValue(static_cast<float>(value)) {};
        Float(const std::string& s);

        int8_t byteValue() const;

        static int8_t compare(float f1, float f2);
        int8_t compareTo(const Float& anotherFloat) const;

        double doubleValue() const;

        bool equals(const std::any& obj) const;
        
        static int32_t floatToIntBits(float value);
        static int32_t floatToRawIntBits(float value);

        float floatValue() const;

        int32_t hashCode() const;
        static int32_t hashCode(float value);

        static float intBitsToFloat(int32_t bits);

        int32_t intValue() const;

        static bool isFinite(float f);
        
        bool isInfinite() const;
        static bool isInfinite(float f);

        bool isNaN() const;
        static bool isNaN(float f);

        int64_t longValue() const;

        static float max(float a, float b);
        static float min(float a, float b);

        static float parseFloat(const std::string& s);

        int16_t shortValue() const;

        static float sum(float a, float b);

        static std::string toHexString(float f);

        std::string toString() const;
        static std::string toString(float f);
        static Float valueOf(float f);
        static Float valueOf(const std::string& s);

        /* OVERLOADS */
        bool operator==(const Float& rhs) const;
        std::strong_ordering operator<=>(const Float& rhs) const;
        friend std::ostream& operator<<(std::ostream& out, const Float& rhs);

};

#endif //FLOAT_H