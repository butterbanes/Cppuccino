#ifndef DOUBLE_H
#define DOUBLE_H

#include <iostream>
#include <cstdint>
#include <limits>
#include <cmath>
#include <bit>
#include <string>
#include <sstream>
#include <iomanip>
#include <system_error>
#include <charconv>
#include <string_view>
#include <compare>

#include "./Byte.h"

template<typename T>
using nlim = std::numeric_limits<T>;

class Double
{

    private:
        double dValue;
    public:
        static constexpr int8_t SIZE = 64;
        static constexpr int8_t BYTES = SIZE / Byte::SIZE;
        static constexpr int8_t PRECISION = 53;
        static constexpr int16_t MAX_EXPONENT = nlim<double>::max_exponent;
        static constexpr int16_t MIN_EXPONENT = nlim<double>::min_exponent;
        static constexpr double MAX_VALUE = nlim<double>::max();
        static constexpr double MIN_VALUE = nlim<double>::denorm_min();
        static constexpr double MIN_NORMAL = nlim<double>::min();
        static constexpr double NaN = nlim<double>::signaling_NaN(); // we want to throw
        static constexpr double NEGATIVE_INFINITY = -nlim<double>::infinity();
        static constexpr double POSITIVE_INFINITY = nlim<double>::infinity();

        Double(double value) : dValue(static_cast<double>(value)) {};
        Double(const std::string& s);

        int8_t byteValue() const;

        static int8_t compare(double d1, double d2);
        int8_t compareTo(const Double& anotherDouble) const;

        static int64_t doubleToLongBits(double value);
        static int64_t doubleToRawLongBits(double value);

        double doubleValue() const;

        bool equals(const std::any& obj) const;

        float floatValue() const;

        int32_t hashCode() const;
        static int32_t hashCode(double value);

        int32_t intValue() const;

        static bool isFinite(double d);
        
        bool isInfinite() const;
        static bool isInfinite(double v);

        bool isNaN() const;
        static bool isNaN(double v);

        static double longBitsToDouble(int64_t bits);

        int64_t longValue() const;

        static double max(double a, double b);
        static double min(double a, double b);

        static double parseDouble(const std::string& s);

        int16_t shortValue() const;

        static double sum(double a, double b);

        static std::string toHexString(double d);

        std::string toString() const;
        static std::string toString(double d);
        static Double valueOf(double d);
        static Double valueOf(const std::string& s);

        /* OVERLOADS */
        bool operator==(const Double& rhs) const;
        std::strong_ordering operator<=>(const Double& rhs) const;
        friend std::ostream& operator<<(std::ostream& out, const Double& rhs);

};
#endif //DOUBLE_H