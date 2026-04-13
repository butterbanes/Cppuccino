#ifndef INTEGER_H
#define INTEGER_H

#include <any>
#include <cstddef>
#include <iostream>
#include <memory>

class Integer {
   private:
    int integerValue;

   public:
    static const int BYTES = 4;
    static const int MAX_VALUE = 2147483647;
    static const int MIN_VALUE = -2147483647;
    static const int SIZE = 32;

    Integer(int);
    Integer(std::string);

    static int bitCount(int i);
    std::byte byteValue();

    static int compare(int x, int y);
    int compareTo(Integer anotherInteger);
    static int compareUnsigned(int x, int y);

    static Integer decode(std::string nm);
    static int divideUnsigned(int dividend, int divisor);

    double doubleValue();

    bool equals(std::any someObject);

    float floatValue();

    static Integer getInteger(std::string nm);
    static Integer getInteger(std::string nm, int val);
    static Integer getInteger(std::string nm, Integer val);

    static int hashCode(int val);
    int hashCode();

    static int highestOneBit(int i);

    int intValue();

    long longValue();

    static int lowestOneBit(int i);

    static int max(int a, int b);
    static int min(int a, int b);

    static int numberOfLeadingZeroes(int i);
    static int numberOfTrailingZeroes(int i);

    static int parseInt(std::string str_val);
    static int parseInt(
        std::string str_val,
        int radix);  // radix --> number base (i.e. 42 has base 10, 00100101 has base 2, etc..)

    static int parseUnsignedInt(std::string str_val);
    static int parseUnsignedInt(
        std::string str_val,
        int radix);  // radix --> number base (i.e. 42 has base 10, 00100101 has base 2, etc..)

    static int remainderUnsigned(int dividend, int divisor);

    static int reverse(int i);
    static int reverseBytes(int i);

    static int rotateLeft(int i, int distance);
    static int rotateRight(int i, int distance);

    short shortValue();

    static int sigNum(int i);

    static int sum(int a, int b);

    static std::string toBinaryString(int i);
    static std::string toHexString(int i);
    static std::string toOctalString(int i);

    std::string toString();
    static std::string toString(int i);
    static std::string toString(
        int i,
        int radix);  // radix --> number base (i.e. 42 has base 10, 00100101 has base 2, etc..)

    static long toUnsignedLong(int x);

    static long toUnsignedString(int i);
    static long toUnsignedString(
        int i,
        int radix);  // radix --> number base (i.e. 42 has base 10, 00100101 has base 2, etc..)

    static Integer valueOf(int i);
    static Integer valueOf(std::string str_val);
    static Integer valueOf(
        std::string str_val,
        int radix);  // radix --> number base (i.e. 42 has base 10, 00100101 has base 2, etc..)
};

#endif  // INTEGER_H
