#ifndef BYTE_H
#define BYTE_H

#include "./Integer.h" // decode(), parseInt(), toString()
#include "./Character.h" // MIN_RADIX, MAX_RADIX

#include <iostream>
#include <cstdint>
#include <any>
#include <memory>
#include <charconv>
#include <format>
#include <array>

class Byte {
    private:
        int8_t bValue;

        class ByteCache {
            private:
                ByteCache() {};
            
            public:
                static std::array<Byte, 256> cache;
                static bool initialized;

                static void initialize();
        };
    public:
        static constexpr uint8_t SIZE = 8; 
        static constexpr uint8_t BYTES = SIZE / Byte::SIZE;
        static constexpr int8_t MAX_VALUE = INT8_MAX;
        static constexpr int8_t MIN_VALUE = INT8_MIN;

        explicit Byte() : bValue(0) {};
        explicit Byte(int8_t value) : bValue(value) {};
        explicit Byte(const std::string& s);
        explicit Byte(const char* s);
        
        static std::unique_ptr<Byte> create(int8_t value);

        int8_t byteValue() const;

        static int16_t compare(int8_t x, int8_t y);
        int16_t compareTo(const Byte& anotherByte) const;
        static int16_t compareUnsigned(int8_t x, int8_t y);

        static Byte decode(const std::string& nm);

        double doubleValue() const;

        bool equals(const std::any& someObject) const;

        float floatValue() const;

        int32_t hashCode() const;
        static int32_t hashCode(int8_t value);

        int32_t intValue() const;

        int64_t longValue() const;

        static int8_t parseByte(const std::string& s);
        static int8_t parseByte(const std::string& s, int8_t radix);

        int16_t shortValue() const;

        std::string toString() const;

        static std::string toString(int8_t b);
        
        static uint32_t toUnsignedInt(int8_t b);
        
        static uint64_t toUnsignedLong(int8_t b);

        static Byte valueOf(int8_t b);

        static Byte valueOf(const std::string& s);

        static Byte valueOf(const std::string& s, int8_t radix);

        /** OVERLOADED **/
        auto operator<=>(const Byte& rhs) const = default;
        friend std::ostream& operator<<(std::ostream& out, const Byte& obj);
};

#endif // BYTE_H