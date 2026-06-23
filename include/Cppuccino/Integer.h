#ifndef INTEGER_H
#define INTEGER_H

#include "../include/Character.h" //needed for Character class consts

#include <any>
#include <cstddef>
#include <charconv>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <cstring>
#include <climits>
#include <algorithm>
#include <cstdint>
#include <bit>
#include <bitset>
#include <vector>
#include <cmath>

class Integer {
   private:
    int32_t integerValue;
    
    static std::vector<Integer> cache;
    
    static constexpr int32_t LOW = -128;
    static constexpr int32_t HIGH = 127;

   public:
    static constexpr int32_t BYTES = 4;
    static constexpr int32_t MAX_VALUE = 2147483647;
    static constexpr int32_t MIN_VALUE = -2147483648;
    static constexpr int32_t SIZE = 32;

    Integer(const int32_t& i);
    Integer(const std::string& str_val);
    Integer(const Integer& obj_Integer);

    static std::unique_ptr<Integer> create(const int32_t&);

    static int32_t bitCount(int32_t i);
    std::byte byteValue();

    static int32_t compare(const int32_t& x, const int32_t& y);
    int32_t compareTo(const Integer& anotherInteger) const;
    static int32_t compareUnsigned(int32_t x, int32_t y);

    static Integer decode(const std::string& nm);
    static int32_t divideUnsigned(int32_t dividend, int32_t divisor);

    double doubleValue();

    bool equals(const std::any& someObject) const;

    float floatValue();

    static Integer getInteger(const std::string& nm);
    static Integer getInteger(const std::string& nm, const int32_t& val);
    static Integer getInteger(const std::string& nm, const Integer& val);

    int32_t hashCode();
    static int32_t hashCode(const int32_t& val);
    static int32_t hashCode(const Integer& val);

    static int32_t highestOneBit(int32_t i);

    int32_t intValue();

    long longValue();

    static int32_t lowestOneBit(int32_t i);

    static int32_t max(const int32_t& a, const int32_t& b);
    static int32_t min(const int32_t& a, const int32_t& b);

    static int32_t numberOfLeadingZeroes(int32_t i);
    static int32_t numberOfTrailingZeroes(int32_t i);

    static int32_t parseInt(const std::string& str_val);
    static int32_t parseInt(
        const std::string& str_val,
        int32_t radix);  // radix --> number base (i.e. 42 has base 10, 00100101 has base 2, etc..)

    static int32_t parseUnsignedInt(const std::string& str_val);
    static int32_t parseUnsignedInt(
        const std::string& str_val,
        int32_t radix);  // radix --> number base (i.e. 42 has base 10, 00100101 has base 2, etc..)

    static int32_t remainderUnsigned(int32_t dividend, int32_t divisor);

    static int32_t reverse(int32_t i);
    static int32_t reverseBytes(int32_t i);

    static int32_t rotateLeft(uint32_t i, int32_t distance);
    static int32_t rotateRight(uint32_t i, int32_t distance);

    short shortValue();

    static int32_t sigNum(const int32_t& i);

    static int64_t sum(const int32_t& a, const int32_t& b);

    static std::string toBinaryString(const int32_t& i);
    static std::string toHexString(const int32_t& i);
    static std::string toOctalString(const int32_t& i);

    std::string toString();
    static std::string toString(const int32_t& i);
    static std::string toString(
        int32_t i,
        int32_t radix);  // radix --> number base (i.e. 42 has base 10, 00100101 has base 2, etc..)

    static uint64_t toUnsignedLong(int32_t x);

    static std::string toUnsignedString(int32_t i);
    static std::string toUnsignedString(
        int32_t i,
        int32_t radix);  // radix --> number base (i.e. 42 has base 10, 00100101 has base 2, etc..)

    static Integer valueOf(const int32_t& i);
    static Integer valueOf(const std::string& str_val);
    static Integer valueOf(
        const std::string& str_val,
        int32_t radix);  // radix --> number base (i.e. 42 has base 10, 00100101 has base 2, etc..)

    /** OVERLOADED **/
    bool operator==(const std::any& rhs) const;
    bool operator!=(const std::any& rhs) const;
    
    friend std::ostream& operator<<(std::ostream& os, const Integer& obj);

    /** EXTRA NON-JAVA HELPERS **/
    static void toUpperCase(std::string& str);
};

#endif  // INTEGER_H
