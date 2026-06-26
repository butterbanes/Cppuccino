#ifndef BYTE_H
#define BYTE_H

#include <iostream>
#include <cstdint>
#include <any>
#include <memory>

class Byte {
    private:
        uint8_t byteValue;
    public:
        static constexpr int8_t SIZE = 8; 
        static constexpr int8_t BYTES = SIZE / Byte::SIZE;
        static constexpr int8_t MAX_VALUE = INT8_MAX;
        static constexpr int8_t MIN_VALUE = INT8_MIN;

        Byte(uint8_t value) : byteValue(value) {};
        Byte(const std::string& s);
        Byte(const char* s);
        
        std::unique_ptr<Byte> create(uint8_t value);

        uint8_t byteValue() const;

        static int compare(uint8_t a, uint8_t b);
        int compareTo(const Byte& anotherByte) const;

        static Byte decode(const std::string& nm);

        double doubleValue() const;

        bool equals(const std::any& obj);

        float floatValue() const;

        int hashCode() const;
        static int hashCode(uint8_t value);

        int intValue() const;

        long longValue() const;

        static uint8_t parseByte(const std::string& s);
        static uint8_t parseByte(const std::string& s, uint8_t radix);

        short shortValue() const;

        static std::string toString(uint8_t b);
        
        static int8_t toUnsignedInt(uint8_t b);
        
        static long toUnsignedLong(uint8_t b);

        static Byte valueOf(uint8_t b);

        static Byte valueOf(const std::string& s, uint8_t radix);
};

#endif // BYTE_H