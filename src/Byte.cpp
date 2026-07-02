#include "../include/Cppuccino/Byte.h"

///////////ByteCache///////////
std::array<Byte, 256> Byte::ByteCache::cache;
bool Byte::ByteCache::initialized = false;

void Byte::ByteCache::initialize() {
    if (initialized) return;

    int8_t value = -128;
    for (int16_t i = 0; i < 256; ++i) {
        cache[i] = Byte{value++};
    }
    initialized = true;
}
///////////////////////////////

Byte::Byte(const std::string& s) {
    this->bValue = parseByte(s, 10);
}

Byte::Byte(const char* s) {
    this->bValue = parseByte(std::string{s}, 10);
}


/**
 *  @brief Creates a memory-safe Byte object using smart pointers.
 *         The goal of this function is to mimic overloading the *new* operator
 *         since no such actual overload is possible since the original *new*
 *         operator requires a direct return of a raw void* (which isn't
 *         considered safe ofc). Think of this as just another constructor.
 *
 *  @param value The int8_t byte value to use when allocating the Byte obj
 *  @returns A std::unique_ptr smart pointer, many prefer using the *auto*
 *           keyword to ease the initialization of a variable of such type
 *           ```cpp
 *           auto myByte = Byte::create(0b00001111);
 *           ```
 */
std::unique_ptr<Byte> Byte::create(int8_t value) {
    return std::make_unique<Byte>(value);
}

/**
 *  @brief Returns the value of *this* Byte's value as an int8_t
 * 
 *  @return the value of *this* Byte as an int8_t
 */
int8_t Byte::byteValue() const {
    return this->bValue;
}

/**
 * Compares two int8_t byte values numerically.
 * The value returned is identical to what would be returned by:
 *    Byte::valueOf(x).compareTo(Byte::valueOf(y))
 * 
 *
 * @param  x the first int8_t byte to compare
 * @param  y the second int8_t byte to compare
 * @return the value 0 if x == y;
 *         a value less than 0 if x < y; and
 *         a value greater than 0 if x > y
 */
int16_t Byte::compare(int8_t x, int8_t y) {
    return x - y;
}

/**
 *  @brief Compares two Byte objects numerically
 * 
 *  @param anotherByte the Byte to be compared
 *  @return 0 if *this* Byte == anotherByte;
 *          <0 if *this* Byte is numerically < anotherByte;
 *          >0 if *this* Byte is numerically > anotherByte;
 *          (signed comparison)
 */
int16_t Byte::compareTo(const Byte& anotherByte) const {
    return Byte::compare(this->bValue, anotherByte.byteValue());
}

/**
 *  @brief Compares two int8_t byte values numerically treating
 *         the values as unsigned 
 * 
 *  @param x the first int8_t byte value to compare
 *  @param y the second int8_t byte value to compare
 *  
 *  @returns 0 if x == y;
 *           <0 if x < y (as unsigned values);
 *           >0 if x > y (as unsigned values);
 * 
 *  @note This function isn't in the Oracle documentation but it does
 *        exist in the java.lang.Byte.java source code so I decided to
 *        add it.
 */
int16_t Byte::compareUnsigned(int8_t x, int8_t y) {
    return Byte::toUnsignedInt(x) - Byte::toUnsignedInt(y);
}

/**
 * @brief Decodes a std::string into an int8_t.
 *
 * Accepts decimal, hexadecimal, and octal numbers given by
 * the following grammar:
 *
 * @par DecodableString:
 * - Sign_opt DecimalNumeral
 * - Sign_opt 0x HexDigits
 * - Sign_opt 0X HexDigits
 * - Sign_opt # HexDigits
 * - Sign_opt 0 OctalDigits
 *
 * @par Sign:
 * - -
 * - +
 *
 * DecimalNumeral, HexDigits, and OctalDigits
 * are as defined in section 3.10.1 of
 * The Java Language Specification,
 * except that underscores are not accepted between digits.
 *
 *  @note The sequence of characters following an optional
 *        sign and/or radix specifier ("0x", "0X",
 *        "#", or leading zero) is parsed using the indicated radix (10, 16, or 8).
 *        This sequence of characters must represent a positive value.
 *        The result is negated if the first character of the specified 
 *        std::string is the minus sign. No whitespace characters 
 *        are permitted in the std::string.
 *
 *  @param nm the std::string to decode.
 *  @returns an int8_t value represented by nm.
 */
Byte Byte::decode(const std::string& nm) {
    try{
        int32_t i = Integer::decode(nm).intValue();
        if (i < MIN_VALUE || i > MAX_VALUE) {
            throw std::out_of_range(std::format("ERR: Passed value must be between {} and {}", Byte::MIN_VALUE, Byte::MAX_VALUE));
        }
        return Byte::valueOf(static_cast<int8_t>(i));
    } catch(const std::out_of_range& eOOR) {
        std::cerr << eOOR.what() << '\n';
    }
}

/**
 *  @brief Returns the value of *this* Byte object as a double 
 * 
 *  @returns *this* Byte value as a double type
 */
double Byte::doubleValue() const {
    return static_cast<double>(this->bValue);
}

/**
 *  @brief Compares *this* object to the specified object. The result
 *         is true iff the arg is not null and is a Byte object that
 *         contains the same bValue as *this* object
 * 
 *  @param someObject The object to compare to
 *  @return true or false dependent on if the object is of type Byte
 *          AND it's inner bValue is the same as *this* Byte's bValue
 */
bool Byte::equals(const std::any& someObject) const {
    if (!someObject.has_value()) {
        return false;
    }

    if (someObject.type() == typeid(Byte)) {
        return this->bValue == std::any_cast<Byte>(someObject).byteValue();
    }

    return false;
}

/**
 *  @brief Returns *this* Byte's bValue as a floating point type
 * 
 *  @return *this* Byte's bValue as a float type
 */
float Byte::floatValue() const {
    return static_cast<float>(this->bValue);
}

/**
 *  @brief Returns a hash code for *this* Byte, 
 *         equal to the result of calling intValue()
 * 
 *  @returns a hash code value for *this* Byte
 */
int32_t Byte::hashCode() const {
    return Byte::hashCode(this->bValue);
}

/**
 *  @brief Returns a hash code for a int8_t byte value, 
 *         equal to the result of calling intValue()
 * 
 *  @returns a hash code value for a int8_t byte value
 */
int32_t Byte::hashCode(int8_t value) {
    return static_cast<int32_t>(value);
}

/**
 *  @brief Returns *this* Byte's bValue as an int32_t
 * 
 *  @returns *this* Byte's bValue as an int32_t
 */
int32_t Byte::intValue() const {
    return static_cast<int32_t>(this->bValue);
}

/**
 *  @brief Returns *this* Byte's bValue as an int64_t (long)
 * 
 *  @returns *this* Byte's bValue as an int64_t (long)
 */
int64_t Byte::longValue() const {
    return static_cast<int64_t>(this->bValue);
}

/**
 * @brief Parses the string argument as a signed decimal int8_t. 
 *        The characters in the string must all be decimal digits,
 *        except that the first character may be an ASCII minus sign
 *        '-' ('\u005Cu002D') to indicate a negative value or an ASCII 
 *        plus sign '+' ('\u005Cu002B') to indicate a positive value. The
 *        resulting int8_t value is returned, exactly as if the argument 
 *        and the radix 10 were given as arguments to the (std::string, int8_t) 
 *        method.
 *
 * @param s a std::string containing the
 *          int8_t representation to be parsed
 * @return the int8_t value represented by the
 *         argument in decimal
 */
int8_t Byte::parseByte(const std::string& s) {
    return Byte::parseByte(s, 10);
}

/**
 * @brief Parses the string argument as a signed int8_t in the
 * radix specified by the second argument. The characters in the
 * string must all be digits, of the specified radix (as
 * determined by whether Character::digit(char,int) returns a 
 * nonnegative value) except that the first
 * character may be an ASCII minus sign '-'
 * ('\u005Cu002D') to indicate a negative value or an
 * ASCII plus sign '+' ('\u005Cu002B') to
 * indicate a positive value.  The resulting int8_t value is
 * returned.
 *
 * @param s the std::string containing the
 *          int8_t representation to be parsed
 * @param radix the radix to be used while parsing {@code s}
 * @return the int8_t value represented by the string
 *         argument in the specified radix
 */
int8_t Byte::parseByte(const std::string& s, int8_t radix) {
    try {
        int32_t i = Integer::parseInt(s, radix);
        if (i < Byte::MIN_VALUE || i > Byte::MAX_VALUE) {
            throw std::out_of_range(std::format("ERR: Passed value must be between {} and {}", Byte::MIN_VALUE, Byte::MAX_VALUE));
        }
        return static_cast<int8_t>(i);
    } catch (const std::out_of_range& eOOR) {
        std::cerr << eOOR.what() << '\n';
    }
}

/**
 *  @brief Returns *this* Byte's bValue as an int16_t (short)
 * 
 *  @return *this* Byte's bValue as an int16_t (short)
 */
int16_t Byte::shortValue() const {
    return static_cast<int16_t>(this->bValue);
}

/**
 *  @brief Returns a std::string representing *this* Byte's value.
 *         The value is converted to signed decimal representation
 *         and returned as a string, exactly as if the int8_t byte
 *         value were given as an arg to the Byte::toString(int8_t)
 *         method. 
 * 
 *  @return a string representation of the value of *this* Byte object
 *         in base 10
 */
std::string Byte::toString() const {
    return Byte::toString(this->bValue);
}


/**
 *  @brief Returns a std::string representing the passed int8_t byte 
 *         value. The value is converted to signed decimal 
 *         representation and returned as a string, exactly as if 
 *         the int8_t byte value were given as an arg to the 
 *         Byte::toString(int8_t) method. 
 * 
 *  @param b The int8_t byte value to be converted to its respective
 *          std::string representation
 * 
 *  @return a string representation of the value of the passed int8_t 
 *         byte value in base 10
 */
std::string Byte::toString(int8_t b) {
    return Integer::toString(b);
}

/**
 *  @brief Converts the argument to an uint32_t by an unsigned
 *         conversion.
 * 
 * @param b the value to convert to an uint32_t
 * @return the argument converted to uint32_t by an unsigned
 *         conversion
 */
uint32_t Byte::toUnsignedInt(int8_t b) {
    return static_cast<uint32_t>(static_cast<uint8_t>(b));
}

/**
 *  @brief Converts the argument to an uint364_t (long) by an unsigned
 *         conversion.
 * 
 * @param b the value to convert to an uint64_t (long)
 * @return the argument converted to uint64_t by an unsigned
 *         conversion
 */
uint64_t Byte::toUnsignedLong(int8_t b) {
    return static_cast<uint64_t>(static_cast<uint8_t>(b));
}

/**
 *  @brief Returns a Byte instance representing the specified int8_t 
 *         byte value. If a new Byte instance is not required, this
 *         method shoulkd generally be used in preference to the
 *         constructor Byte(int8_t), as this method is, supposedly,
 *         likely to yield significantly better space and time performance
 *         since all int8_t byte values are cached.
 * 
 *  @param b A int8_t byte value
 *  
 *  @returns a Byte instance representing b
 */
Byte Byte::valueOf(int8_t b) {
    const uint8_t offset = 128;
    if (!ByteCache::initialized) {
        ByteCache::initialize();
    }

    return ByteCache::cache[static_cast<uint8_t>(b+128)];
}

/**
 *  @brief Returns a Byte object holding the value given by the specified
 *         std::string. The arg is interpreted as representing as signed
 *         decimal int8_t byte, exactly as if the arg was given to the
 *         Byte::parseByte(std::string) method. The result is a Byte object
 *         that represents the int8_t byte value specified by the std::string.
 * 
 *         In other words. this method returns a Byte object equal to:
 *         ```cpp
 *         Byte::valueOf(Byte::parseByte(s)); 
 *         ```
 * 
 *  @param s The std::string to be parsed
 *  @returns a Byte object holding the value represented by the std::string arg
 */
Byte Byte::valueOf(const std::string& s) {
    return Byte::valueOf(s, 10);
}

/**
 *  @brief Returns a Byte object holding the value given by the specified
 *         std::string. The arg is interpreted as representing as signed
 *         decimal int8_t byte, exactly as if the arg was given to the
 *         Byte::parseByte(std::string) method. The result is a Byte object
 *         that represents the int8_t byte value specified by the std::string.
 * 
 *         In other words. this method returns a Byte object equal to:
 *         ```cpp
 *         Byte::valueOf(Byte::parseByte(s, radix)); 
 *         ```
 * 
 *  @param s The std::string to be parsed
 *  @param radix The radix to be used in interpreting a Byte object holding 
 *               the value represented by the std::string arg in the 
 *               specified radix
 *  @returns a Byte object holding the value represented by the std::string arg
 *           in the specified radix
 */
Byte Byte::valueOf(const std::string& s, int8_t radix) {
    return Byte::valueOf(Byte::parseByte(s, radix));
}

/**
 *  @brief Overloads the insertion operator << for printing
 * 
 *  @returns A modified out stream altered to include information about
 *           the passed Byte object
 */
std::ostream& operator<<(std::ostream& out, const Byte& obj) {
    out << static_cast<int>(obj.byteValue());
    return out;
}