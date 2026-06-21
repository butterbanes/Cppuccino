#include "../include/Cppuccino/Integer.h"

std::vector<Integer> Integer::cache = []() {
    std::vector<Integer> tempCache;
    // prealloc exact size to avoid realloc overhead
    tempCache.reserve(HIGH - LOW + 1);

    // cache the Integer objects using LOW to HIGH
    for (int32_t i = LOW; i <= HIGH; ++i) {
        tempCache.push_back(Integer(i));
    }
    return tempCache;
}();

Integer::Integer(int32_t i) {
    this->integerValue = i;
}

Integer::Integer(const std::string& str_val) {
    this->integerValue = std::stoi(str_val);
}

Integer::Integer(const Integer& obj_Integer) {
    this->integerValue = obj_Integer.integerValue;
}

/**
 *  @brief Creates a memory-safe Integer objet using smart pointers.
 *         The goal of this function is to mimic overloading the *new* operator
 *         since no such actual overload is possible since the original *new*
 *         operator requires a direct return of a raw void* (which isn't
 *         considered safe ofc). Think of this as just another constructor.
 *
 *  @param val The int32_t value to use when allocating the Integer obj
 *  @returns A std::unique_ptr smart pointer, many prefer using the *auto*
 *           keyword to ease the initialization of a variable of such type
 *           ```cpp
 *           auto myInteger = Integer::create(15);
 *           ```
 */
std::unique_ptr<Integer> Integer::create(const int32_t& val) {
    return std::make_unique<Integer>(val);
}

/**
 *  @brief Calculates the number of 1 bits from a twos-complement value
 *
 *  @param i The int32_t to evaluate
 *  @return The number of 1 bits in a twos-complement value
 *
 *  @note This was implemented using Brian Kernighan's Algorithm
 */
int32_t Integer::bitCount(int32_t i) {
    int32_t count = 0;
    while (i > 0) {
        i &= (i - 1);
        count++;
    }
    return count;
}

/**
 *  @brief Returns the value of this Integer as a byte after a narrowing primitive conversion
 *
 *  @param N/A
 *  @return value of this Integer as a byte after narrowing primitive conversion
 */
std::byte Integer::byteValue() {
    return static_cast<std::byte>(static_cast<unsigned char>(this->integerValue));
}

/**
 *  @brief Compares two int32_t values numerically
 *
 *  @param x First comparison value
 *  @param y Second comparison value
 *  @return the value 0 if x == y; a value less than 0 if x < y; and a value greater than 0 if x > y
 */
int32_t Integer::compare(int32_t x, int32_t y) {
    return x == y ? 0 : x < y ? -1 : 1;
}

/**
 *  @brief compare two Integer objects numerically with this Integer as one of the comparisons
 *
 *  @param anotherInteger& the other Integer to be compared to
 *  @return the value 0 if this Integer is equal to the argument Integer;
 *          a value less than 0 if this Integer is numerically less than the argument Integer;
 *          and a value greater than 0 if this Integer is numerically greater than the argument
 * Integer (signed comparison)
 */
int32_t Integer::compareTo(const Integer& anotherInteger) const {
    int32_t x = this->integerValue;
    int32_t y = anotherInteger.integerValue;
    return x == y ? 0 : x < y ? -1 : 1;
}

/**
 *  @brief Compares two int32_t values numerically treating the values as unsigned
 *
 *  @param x The first int32_t to compare
 *  @param y The second int32_t to compare
 *  @return the value 0 if x == y; a value less than 0 if x < y as unsigned values; and a value
 * greater than 0 if x > y as unsigned values
 */
int32_t Integer::compareUnsigned(int32_t x, int32_t y) {
    x = static_cast<uint32_t>(x);
    y = static_cast<uint32_t>(y);
    return x == y ? 0 : x < y ? -1 : 1;
}

/**
 *  @brief Decodes a std::string int32_to an Integer. Accepts decimal, hexadecimal, and octal
 numbers given by the following grammar DecodableString: Signopt DecimalNumeral Signopt 0x HexDigits
        Signopt 0X HexDigits
        Signopt # HexDigits
        Signopt 0 OctalDigits
    Sign:
        -
        +
 *  @param nm The std::string to decode
 *  @return an Integer object holding the int32_t value represented by nm
 *          If nm is invalid, returns an Integer obj with the value of 0
 *  @throws std::exception Throws when the passed std::string is not in a valid numerical format
 */
Integer Integer::decode(const std::string& nm) {
    // test if nm matches any MACROS for int types

    try {
        int32_t val;
        if (nm.empty())
            throw std::invalid_argument("Empty string");

        // handle the '#' case which std::stoi doesn't support
        if (nm[0] == '#') {
            val = std::stoi(nm.substr(1), nullptr, 16);
        } else {
            // passing 0 as the base tells stoi to:
            // 1. Parse 0x as hex
            // 2. Parse 0 as octal
            // 3. Parse everything else as decimal
            val = std::stoi(nm, nullptr, 0);
        }
        return Integer(val);
    } catch (const std::exception& e) {
        std::cerr << "ERR: Conversion error: " << e.what() << '\n';
        return Integer(0);
    }
}

/**
 *  @brief Returns the unsigned quotient of dividing the first argument by the second where each
 * argument and the result is interpreted as an unsigned value
 *
 *  @param dividend The value to be divided
 *  @param divisor The value to divide the dividend by
 *  @returns the unsigned quotient of the first argument divided by the second argument
 *
 *  @note in two's complement arithmetic, the three other basic arithmetic operations of add,
 * subtract, and multiply are bit-wise identical if the two operands are regarded as both being
 * signed or both being unsigned. Therefore separate addUnsigned, etc. methods are not provided
 */
int32_t Integer::divideUnsigned(int32_t dividend, int32_t divisor) {
    // check for div by zero, if not present cast unsigned int32_t int32_ternally and return with
    // result after casting back to int32_t type
    return divisor == 0 ? 0
                        : static_cast<int32_t>(static_cast<uint32_t>(dividend) /
                                               static_cast<uint32_t>(divisor));
}

/**
 *  @brief Returns the value of this Integer as a double after a widening primitive conversion
 *
 *  @param N/A
 *  @returns the numeric value represented by this object after conversion to type double
 */
double Integer::doubleValue() {
    return static_cast<double>(this->integerValue);
}

/**
 *  @brief Compares this object to the specified object. The result is true if and only if the
 *         argument is not null and is an Integer object that contains the same int32_t value as
 * this object.
 *
 *  @param someObject The object to compare with
 *  @returns true if the objects are the same; false otherwise
 */
bool Integer::equals(const std::any& someObject) const {
    if (!someObject.has_value()) {
        return false;
    }

    if (someObject.type() == typeid(Integer)) {
        return this->integerValue == std::any_cast<Integer>(someObject).integerValue;
    }

    return false;
}

/**
 *  @brief Returns the value of this Integer as a float after a widening
 *         primitive conversion
 *
 *  @param N/A
 *  @returns the numeric value represented by this object after conversion to
 *           type float
 */
float Integer::floatValue() {
    return static_cast<float>(this->integerValue);
}

/**
 *  @brief Since C++ doesn't use system properties the getInteger(...)
 *         functions will just return the passed sting as an Integer
 *
 *  @param nm The name/string of the value to be returned as an Integer
 *  @returns the Integer value of the passed string
 *
 *  @note For this we'll just use our previously defined decode() function
 */
Integer Integer::getInteger(const std::string& nm) {
    return decode(nm);
}

/**
 *  @brief Since C++ doesn't use system properties the getInteger(...)
 *         functions will just return the passed sting as an Integer
 *
 *  @param nm The name/string of the value to be returned as an Integer
 *  @param val The default Integer value to "fallback" to if the
 *             "system property" DNE
 *  @returns the Integer value of the passed string
 *
 *  @note For this we'll just use our previously defined decode() function
 */
Integer Integer::getInteger(const std::string& nm, int32_t val) {
    try {
        return decode(nm);
    } catch (const std::ios_base::failure& e) {
        std::cout << "ERR: Conversion error - " << e.what() << '\n';
    }
    return Integer(val);
}

/**
 *  @brief Since C++ doesn't use system properties the getInteger(...) functions will just return
 * the passed sting as an Integer
 *
 *  @param nm The name/string of the value to be returned as an Integer
 *  @param val The default Integer value to "fallback" to if the "system property" DNE
 *  @returns the Integer value of the passed string
 *
 *  @note For this we'll just use our previously defined decode() function
 */
Integer Integer::getInteger(const std::string& nm, const Integer& val) {
    try {
        return decode(nm);
    } catch (const std::ios_base::failure& e) {
        std::cout << "ERR: Conversion error - " << e.what() << '\n';
    }
    return Integer(val.integerValue);
}

/**
 *  @brief Returns a hash code for *this* Integer
 *
 *  @param N/A
 *  @returns A hash code for *this* Integer
 */
int32_t Integer::hashCode() {
    return this->integerValue;
}

/**
 *  @brief Returns a hash code for int32_t value
 *
 *  @param val The int32_t value to be hashed
 *  @returns A hash code for the passed int32_t value
 */
int32_t Integer::hashCode(int32_t val) {
    return val;
}

/**
 *  @brief Returns a hash code for int32_t value
 *
 *  @param val The int32_t value to be hashed
 *  @returns A hash code for the passed int32_t value
 */
int32_t Integer::hashCode(const Integer& val) {
    return val.integerValue;
}

/**
 *  @brief Returns an int32_t value with at most a single one-bit, in the position
 *         of the highest-order ("leftmost") one-bit in the specified int32_t value.
 *         Returns zero if the specified value has no one-bits in its two's
 *         complement binary representation, that is, if it is equal to zero
 *
 *
 *  @param i The value whose highest one bit is to be computed
 *  @returns an int32_t value with a single one-bit, in the position of the
 *           highest-order one-bit in the specified value, or zero if the specified
 *           value is itself equal to zero.
 */
int32_t Integer::highestOneBit(int32_t i) {
    uint32_t x = static_cast<uint32_t>(i);
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    return static_cast<int32_t>(x - (x >> 1));
}

/**
 *  @brief Returns the value of *this* Integer as int32_t
 *
 *  @param N/A
 *  @returns the numeric value represented by this object after conversion to type int32_t
 */
int32_t Integer::intValue() {
    return static_cast<int32_t>(this->integerValue);
}

/**
 *  @brief Returns the value of *this* Integer as long
 *
 *  @param N/A
 *  @returns the numeric value represented by this object after conversion to type long
 */
long Integer::longValue() {
    return static_cast<long>(this->integerValue);
}

/**
 *  @brief Returns an int32_t value with at most a single one-bit, in the position
 *         of the lowest-order ("rightmost") one-bit in the specified int32_t value.
 *         Returns zero if the specified value has no one-bits in its two's complement
 *         binary representation, that is, if it is equal to zero.
 *
 *  @param i The value whose lowest one bit is to be computed
 *  @returns an int32_t value with a single one-bit, in the position of the
 *           lowest-order one-bit in the specified value, or zero if the
 *           specified value is itself equal to zero.
 */
int32_t Integer::lowestOneBit(int32_t i) {
    return (static_cast<uint32_t>(i) & -static_cast<uint32_t>(i));
}

/**
 *  @brief Returns the greater of two int32_t values as if by calling std::max
 *
 *  @param a The first operand
 *  @param b The second operand
 *  @returns The greater of *a* and *b*
 */
int32_t Integer::max(int32_t a, int32_t b) {
    return std::max(a, b);
}

/**
 *  @brief Returns the lesser of two int32_t values as if by calling std::min
 *
 *  @param a The first operand
 *  @param b The second operand
 *  @returns The lesser of *a* and *b*
 */
int32_t Integer::min(int32_t a, int32_t b) {
    return std::min(a, b);
}

/**
 *  @brief Returns the number of zero bits preceding the highest-order
 *         ("leftmost") one-bit in the two's complement binary representation of
 *         the specified int32_t value. Returns 32 if the specified value has no
 *         one-bits in its two's complement representation, in other words if it
 *         is equal to zero.
 *
 *  @param i The value of whose leading zeroes is to be computed
 *  @returns The number of zero bits preceding the highest-order ("leftmost")
 *           one-bit in the two's complement binary representation of the
 *           specified int32_t value, or 32 if the value is equal to zero
 *
 *  @note Note that this method is closely related to the logarithm base 2. For
 *        all positive int32_t values x:
 *          - floor(log2(x)) = 31 - numberOfLeadingZeros(x)
 *          - ceil(log2(x)) = 32 - numberOfLeadingZeros(x - 1)
 */
int32_t Integer::numberOfLeadingZeroes(int32_t i) {
    return std::countl_zero(static_cast<uint32_t>(i));
}

/**
 *  @brief Returns the number of zero bits following the lowest-order
 *         ("rightmost") one-bit in the two's complement binary representation
 *         of the specified int32_t value. Returns 32 if the specified value has no
 *         one-bits in its two's complement representation, in other words if
 *         it is equal to zero
 *
 *  @param i The value of whose trailing zeroes is to be computed
 *  @returns The number of zero bits following the lowest-order ("rightmost")
 *           one-bit in the two's complement binary representation of the
 *           specified int32_t value, or 32 if the value is equal to zero
 */
int32_t Integer::numberOfTrailingZeroes(int32_t i) {
    return std::countr_zero(static_cast<uint32_t>(i));
}

/**
 *  @brief Parses the string argument as a signed decimal int32_t. The
 *         characters in the string must all be decimal digits, except that the
 *         first character may be an ASCII minus sign '-' ('\u002D') to
 *         indicate a negative value or an ASCII plus sign '+' ('\u002B') to
 *         indicate a positive value. The resulting int32_t value is returned
 *
 *  @param str_val a std::string containing the int32_t representation to be parsed
 *  @returns the int32_t value represented by the argument in decimal
 */
int32_t Integer::parseInt(const std::string& str_val) {
    return static_cast<int32_t>(decode(str_val).integerValue);
}

/**
 *  @brief Parses the string argument as a signed int32_t in the radix
 *         specified by the second argument. The characters in the string must
 *         all be digits of the specified radix, except that
 *         the first character may be an ASCII minus sign '-' ('\u002D') to
 *         indicate a negative value or an ASCII plus sign '+' ('\u002B') to
 *         indicate a positive value. The resulting int32_t value is returned
 *
 *  @param s The std::string containing the int32_t representation to be parsed
 *  @param radix The radix to be used while parsing *s*
 *  @returns The int32_t represented by the string argument in the specified radix
 *  @throws std::invalid_argument || std::out_of_range
 */
int32_t Integer::parseInt(const std::string& str_val, int32_t radix) {
    int32_t result;
    size_t pos = 0;  // to track how many characters were successfully parsed

    try {
        result = std::stoi(str_val, &pos, radix);

        // check if stoi stopped parsing before the end of the string
        if (pos < str_val.length()) {
            std::cerr << "ERR: Invalid characters found after parsed number.\n";
            return EXIT_FAILURE;
        }

    } catch (const std::invalid_argument& e) {
        std::cerr << "ERR: Conversion failed: " << e.what() << '\n';
        return 1;
    } catch (const std::out_of_range& e) {
        std::cerr << "ERR: Conversion failed: " << e.what() << '\n';
        return 1;
    }

    return static_cast<uint32_t>(result);
}

/**
 *  @brief Parses the string argument as an unsigned decimal int32_t. The
 *         characters in the string must all be decimal digits, except that the
 *         first character may be an an ASCII plus sign '+' ('\u002B'). The
 *         resulting int32_t value is returned, exactly as if the argument and
 *         the radix 10 were given as arguments to the
 *         parseUnsignedInt(std::string, int32_t) method.
 *  @param str_val a std::string containing the int32_t representation to be parsed
 *  @returns the int32_t value represented by the argument in decimal
 */
int32_t Integer::parseUnsignedInt(const std::string& str_val) {
    return static_cast<uint32_t>(decode(str_val).integerValue);
}

/**
 *  @brief Parses the string argument as an unsigned int32_t in the radix
 *         specified by the second argument. An unsigned int32_t maps the values
 *         usually associated with negative numbers to positive numbers larger
 *         than MAX_VALUE. The characters in the string must all be digits of the
 *         specified radix, except that the first character may be an ASCII plus sign
 *         '+' ('\u002B'). The resulting int32_t value is returned.
 *
 *  @param s The std::string containing the int32_t representation to be parsed
 *  @param radix The radix to be used while parsing *s*
 *  @returns The int32_t represented by the string argument in the specified radix
 *  @throws std::invalid_argument || std::out_of_range
 */
int32_t Integer::parseUnsignedInt(const std::string& str_val, int32_t radix) {
    int32_t result;
    try {
        result = std::stoi(str_val, nullptr, radix);
    } catch (std::invalid_argument& e) {
        std::cerr << "ERR: Conversion failed: " << e.what() << '\n';
        return 1;
    } catch (std::out_of_range& e) {
        std::cerr << "ERR: Conversion failed: " << e.what() << '\n';
        return 1;
    }
    return static_cast<uint32_t>(result);
}

/**
 *  @brief Returns the unsigned remainder from dividing the first argument by
 *         the second where each argument and the result is int32_terpreted as an
 *         unsigned value.
 *
 *  @param dividend The value to be divided
 *  @param divisor The value doing the dividing
 *  @returns The unsigned remainder of the first argument divided by the second
 *           argument
 */
int32_t Integer::remainderUnsigned(int32_t dividend, int32_t divisor) {
    return static_cast<uint32_t>(static_cast<uint32_t>(dividend) % static_cast<uint32_t>(divisor));
}

/**
 *  @brief Returns the value obtained by reversing the order of the bits in the
 *         two's complement binary representation of the specified int32_t value.
 *
 *  @param i The value whose bits are to be reversed
 *  @returns the value obtained by reversing order of the bits in the specified
 *           int32_t value
 */
int32_t Integer::reverse(int32_t i) {
    // create 32-bit bitset (4 bytes 8 bits)
    std::bitset<sizeof(int32_t) * 8> bits(i);

    // swapping logic
    constexpr std::size_t total_bits = sizeof(int32_t) * 8;
    for (std::size_t j = 0; j < total_bits / 2; ++j) {
        bool t = bits[j];
        bits[j] = bits[total_bits - j - 1];
        bits[total_bits - j - 1] = t;
    }

    // cast to ul then to int32_t
    return static_cast<int32_t>(bits.to_ulong());
}

/**
 *  @brief Returns the value obtained by reversing the order of the bytes in
 *         the two's complement representation of the specified int32_t value.
 *
 *  @param i The value whose bytes are to be reversed
 *  @returns The value obtained by reversing the bytes in the specified int32_t
 *           value.
 */
int32_t Integer::reverseBytes(int32_t i) {
    return ((i & 0x000000FF) << 24) | ((i & 0x0000FF00) << 8) | ((i & 0x00FF0000) >> 8) |
           ((i & 0xFF000000) >> 24);
}

/**
 *  @brief Returns the value obtained by rotating the two's complement binary
 *         representation of the specified int32_t value left by the specified
 *         number of bits. (Bits shifted out of the left hand, or high-order,
 *         side reenter on the right, or low-order.)
 *
 *         Note that left rotation with a negative distance is equivalent to right
 *         rotation: rotateLeft(val, -distance) == rotateRight(val, distance).
 *         Note also that rotation by any multiple of 32 is a no-op, so all but
 *         the last five bits of the rotation distance can be ignored, even if
 *         the distance is negative:
 *         rotateLeft(val, distance) == rotateLeft(val, distance & 0x1F).
 *
 *  @param i The value whose bits are to be rotated left
 *  @param distance the number of bit positions to rotate left
 *  @returns the value obtained by rotating the two's complement binary
 *           representation of the specified int32_t value left by the specified
 *           number of bits.
 */
int32_t Integer::rotateLeft(uint32_t i, int32_t distance) {
    return std::rotl(i, distance);
}

/**
 *  @brief Returns the value obtained by rotating the two's complement binary
 *         representation of the specified int32_t value left by the specified
 *         number of bits. (Bits shifted out of the right hand, or low-order,
 *         side reenter on the left, or high-order.)
 *
 *         Note that right rotation with a negative distance is equivalent to right
 *         rotation: rotateRight(val, -distance) == rotateRight(val, distance).
 *         Note also that rotation by any multiple of 32 is a no-op, so all but
 *         the last five bits of the rotation distance can be ignored, even if
 *         the distance is negative:
 *         rotateRight(val, distance) == rotateRight(val, distance & 0x1F).
 *
 *  @param i The value whose bits are to be rotated right
 *  @param distance the number of bit positions to rotate right
 *  @returns the value obtained by rotating the two's complement binary
 *           representation of the specified int32_t value right by the specified
 *           number of bits.
 */
int32_t Integer::rotateRight(uint32_t i, int32_t distance) {
    return std::rotr(i, distance);
}

/**
 *  @brief Returns the value of this Integer as a short after a narrowing
 *         primitive conversion
 *
 *  @param N/A
 *  @returns the numeric value represented by this object after conversion to
 *           type short
 */
short Integer::shortValue() {
    return static_cast<short>(this->integerValue);
}

/**
 *  @brief Returns the signum function of the specified int32_t value. (The return
 *         value is -1 if the specified value is negative; 0 if the specified
 *         value is zero; and 1 if the specified value is positive.)
 *
 *  @param i The value whose signum is to be computed
 *  @returns the signum function of the specified int32_t value
 */
int32_t Integer::sigNum(int32_t i) {
    return i < 0 ? -1 : i > 0 ? 1 : 0;
}

/**
 *  @brief Returns a string representation of the int32_t argument as an
 *         unsigned int32_t in base 2. The unsigned int32_t value is the
 *         argument plus 232 if the argument is negative; otherwise it is equal
 *         to the argument. This value is converted to a string of ASCII digits
 *         in binary (base 2) with no extra leading 0s. The value of the
 *         argument can be recovered from the returned string s by calling
 *         Integer.parseUnsignedInt(s, 2). If the unsigned magnitude is zero,
 *         it is represented by a single zero character '0' ('\u0030');
 *         otherwise, the first character of the representation of the unsigned
 *         magnitude will not be the zero character.
 *         The characters '0' ('\u0030') and '1' ('\u0031') are used as binary
 *         digits.
 *
 *  @param i The int32_t to be converted to a string
 *  @returns the string representation of the unsigned int32_t value
 *           represented by the argument in binary (base 2)
 */
std::string Integer::toBinaryString(int32_t i) {
    return std::bitset<sizeof(int32_t) * 8>(i).to_string();
}

/**
 *  @brief Returns a string representation of the int32_t argument as an
 *         unsigned int32_t in base 16. The unsigned int32_t value is the
 *         argument plus 232 if the argument is negative; otherwise, it is
 *         equal to the argument. This value is converted to a string of ASCII
 *         digits in hexadecimal (base 16) with no extra leading 0s. The value
 *         of the argument can be recovered from the returned string s by
 *         calling Integer.parseUnsignedInt(s, 16). If the unsigned magnitude
 *         is zero, it is represented by a single zero
 *         character '0' ('\u0030'); otherwise, the first character of the
 *         representation of the unsigned magnitude will not be the zero
 *         character.
 *
 *         The following characters are used as
 *         hexadecimal digits: 0123456789abcdef
 *
 *         These are the characters '\u0030' through '\u0039' and '\u0061'
 *         through '\u0066'.
 *
 *         If uppercase letters are desired, the
 *         Integer::toUpperCase(n) method may be called on the result:
 *         Integer.toUpperCase(Integer.toHexString(i))
 *
 *  @param i The int32_t to be converted int32_to a string
 *  @returns the string representation of the unsigned int32_t value
 *           represented by the argument in hexadecimal (base 16)
 */
std::string Integer::toHexString(int32_t i) {
    std::stringstream ss;
    ss << std::hex << i;
    return ss.str();
}

/**
 *  @brief Returns a string representation of the int32_t argument as an
 *         unsigned int32_t in base 8. The unsigned int32_t value is the
 *         argument plus 232 if the argument is negative; otherwise, it is
 *         equal to the argument. This value is converted to a string of ASCII
 *         digits in octal (base 8) with no extra leading 0s. The value of the
 *         argument can be recovered from the returned string s by calling
 *         Integer.parseUnsignedInt(s, 8). If the unsigned magnitude is zero,
 *         it is represented by a single zero character '0' ('\u0030');
 *         otherwise, the first character of the representation of the unsigned
 *         magnitude will not be the zero character. The following characters
 *         are used as octal digits: 01234567
 *         These are the characters '\u0030' through '\u0037'.
 *
 *  @param i The int32_t to be converted int32_to a string
 *  @returns the string representation of the unsigned int32_t value
 *           represented by the argument in octal (base 8)
 */
std::string Integer::toOctalString(int32_t i) {
    std::stringstream ss;
    ss << std::oct << i;
    return ss.str();
}

/**
 *  @brief Returns a std::string variable representing this Integer's value. The value
 *         is converted to signed decimal representation and returned as a
 *         string, exactly as if the int32_t value were given as an argument to
 *         the toString(int32_t) method
 *
 *  @param N/A
 *  @returns A string representation of the value of this object in base 10
 */
std::string Integer::toString() {
    std::stringstream ss;
    ss << this->integerValue;
    return ss.str();
}

/**
 *  @brief Returns a String object representing the specified int32_t. The
 *         argument is converted to signed decimal representation and returned
 *         as a string, exactly as if the argument and radix 10 were given as
 *         arguments to the toString(int32_t, int32_t) method
 *
 *  @param i The int32_t to be converted
 *  @returns A string representation of the argument in base 10
 */
std::string Integer::toString(int32_t i) {
    return Integer(i).toString();
}

/**
 *  @brief Returns a string representation of the first argument in the radix
 *         specified by the second argument.
 *         If the radix is smaller than Character.MIN_RADIX or larger than
 *         Character.MAX_RADIX, then the radix 10 is used instead.
 *         If the first argument is negative, the first element of the result
 *         is the ASCII minus character '-' ('\u002D'). If the first argument
 *         is not negative, no sign character appears in the result.
 *         The remaining characters of the result represent the magnitude of
 *         the first argument. If the magnitude is zero, it is represented by a
 *         single zero character '0' ('\u0030'); otherwise, the first character
 *         of the representation of the magnitude will not be the zero
 *         character. The following ASCII characters are used as digits:
 *         0123456789abcdefghijklmnopqrstuvwxyz
 *         These are '\u0030' through '\u0039' and '\u0061' through '\u007A'.
 *         If radix is N, then the first N of these characters are used as
 *         radix-N digits in the order shown. Thus, the digits for hexadecimal
 *         (radix 16) are 0123456789abcdef. If uppercase letters are desired,
 *         the Integer.toUpperCase(n) method may be called on the result:
 *         Integer.toUpperCase(Integer.toString(i, radix))
 *
 *  @param i The int32_t to be converted int32_to a string
 *  @param radix The radix to use in the string representation
 *  @returns A string representation of the argument in the specified radix
 *  @note At the time of original implementation, this function only supports
 *        base 2 through base 36, albeit that it *does* match Java's range
 */
std::string Integer::toString(int32_t i, int32_t radix) {
    if (radix == 10) {
        return toString(i);
    }

    if (radix < Character::MIN_RADIX || radix > Character::MAX_RADIX) {
        radix = 10;
    }

    char buf[64];
    auto [ptr, ec] = std::to_chars(buf, buf + sizeof(buf), i, radix);
    return std::string(buf, ptr);
}

/**
 *  @brief Converts the argument to a long by an unsigned conversion. In an
 *         unsigned conversion to a long, the high-order 32 bits of the long
 *         are zero and the low-order 32 bits are equal to the bits of the
 *         int32_t argument. Consequently, zero and positive int32_t values are
 *         mapped to a numerically equal long value and negative int32_t values are
 *         mapped to a long value equal to the input plus 232.
 *
 *  @param x The value to convert to an unsigned long
 *  @returns The argument converted to long by an unsigned conversion
 *
 *  @note the first arg is of type uint32_t instead of just int32_t to behave
 *        as a kind-of "catch-all" for possible inputs at most the size of an
 *        unsigned long (in the compliation, we are using 64-bit architecture)
 */
uint64_t Integer::toUnsignedLong(int32_t x) {
    return static_cast<uint64_t>(x);
}

/**
 *  @brief Returns a string representation of the argument as an unsigned
 *         decimal value. The argument is converted to unsigned decimal
 *         representation and returned as a string exactly as if the argument
 *         and radix 10 were given as arguments to the
 *         toUnsignedString(uint32_t, int32_t) method.
 *
 *  @param i The value to convert to an unsigned string
 *  @returns An unsigned string representation of the argument
 *
 *  @note the first arg is of type uint32_t instead of just int32_t to behave
 *        as a kind-of "catch-all" for possible inputs at most the size of an
 *        unsigned long (in the compliation, we are using 64-bit architecture)
 */
std::string Integer::toUnsignedString(int32_t i) {
    std::stringstream ss;
    ss << Integer::toUnsignedLong(i);
    return ss.str();
}

/**
 *  @brief Returns a string representation of the first argument as an unsigned
 *         uint32_t value in the radix specified by the second argument.
 *         If the radix is smaller than Character.MIN_RADIX or larger than
 *         Character.MAX_RADIX, then the radix 10 is used instead.
 *         Note that since the first argument is treated as an unsigned value,
 *         no leading sign character is printed.
 *         If the magnitude is zero, it is represented by a single zero
 *         character '0' ('\u0030'); otherwise, the first character of the
 *         representation of the magnitude will not be the zero character.
 *         The behavior of radixes and the characters used as digits are the
 *         same as toString.
 *
 *  @param i The uint32_t to be converted to an unsigned string
 *  @param radix The radix to be used in the conversion
 *  @returns an unsigned string representation of the argument in the specified
 *           radix
 *
 *  @note the first arg is of type uint32_t instead of just int32_t to behave
 *        as a kind-of "catch-all" for possible inputs at most the size of an
 *        unsigned long (in the compliation, we are using 64-bit architecture)
 */
std::string Integer::toUnsignedString(int32_t i, int32_t radix) {
    if (radix == 10) {
        return toUnsignedString(i);
    }

    if (radix < Character::MIN_RADIX || radix > Character::MAX_RADIX) {
        radix = 10;
    }

    char buf[64];
    auto [ptr, ec] = std::to_chars(buf, buf + sizeof(buf), static_cast<uint32_t>(i), radix);
    return std::string(buf, ptr);
}

/**
 *  @brief Returns an Integer instance representing the specified int32_t value. If
 *         a new Integer instance is not required, this method should generally
 *         be used in preference to the constructor Integer(int32_t), as this
 *         method is likely to yield significantly better space and time
 *         performance by caching frequently requested values. This method will
 *         always cache values in the range -128 to 127, inclusive, and may
 *         cache other values outside of this range.
 *
 *  @param i An int32_t value
 *  @returns An int32_t instance representing *i*
 */
Integer Integer::valueOf(int32_t i) {
    if (i >= LOW && i <= HIGH) {
        return cache[i - LOW];
    }
    return Integer(i);
}

/**
 *  @brief Returns an Integer object holding the value of the specified String.
 *         The argument is interpreted as representing a signed decimal
 *         int32_t, exactly as if the argument were given to the
 *         parseInt(std::string) method. The result is an Integer object
 *         that represents the int32_t value specified by the string.
 *
 *  @param str_val A string value to be evaluated to an Integer object
 *  @returns An Integer object holding the value represented by the string
 *           argument
 */
Integer Integer::valueOf(const std::string& str_val) {
    return Integer(parseInt(str_val));
}

/**
 *  @brief Returns an Integer object holding the value extracted from the
 *         specified String when parsed with the radix given by the second
 *         argument. The first argument is int32_terpreted as representing a signed
 *         int32_t in the radix specified by the second argument, exactly as if
 *         the arguments were given to the parseInt(java.lang.String, int32_t)
 *         method. The result is an Integer object that represents the int32_t
 *         value specified by the string.
 *         In other words, this method returns an Integer object equal to the
 *         value of:
 *         Integer(Integer.parseInt(s, radix))
 *
 *  @param str_val A string value to be evaluated to Integer obj(of base radix)
 *  @param radix The base of the number to use
 *
 *  @returns An Integer object holding the value represented by the given
 *           arguments and their appropriate manipulations
 */
Integer Integer::valueOf(const std::string& str_val, int32_t radix) {
    return Integer(parseInt(str_val, radix));
}

/**
 *  @brief Returns a boolean (true/false) value based on the evaluation of
 *         *this* Integer object compared to another Integer object,
 *         if the other object passed is not an Integer it automatically
 *         evaluates to false
 *
 *  @param rhs The other Integer object to be compared to by *this*
 *  @returns True or false dependent on how the comparison evaluates
 */
bool Integer::operator==(const std::any& rhs) const {
    return this->equals(rhs);
}

/**
 *  @brief Returns a boolean (true/false) value based on the evaluation of
 *         *this* Integer object compared to another object,
 *         if the other object passed is not an Integer it automatically
 *         evalutates to true
 *
 *  @param rhs The other Integer object to be compared to by *this*
 *  @returns True or false dependent on how the comparison evaluates
 *  @note This effectively just returns the NOT of the == operator overload for
 *        Integer
 */
bool Integer::operator!=(const std::any& rhs) const {
    return !(this->equals(rhs));
}

/**
 *  @brief Returns an ostream reference to implement the << operator for the
 *         std::cout when printing Integer objects
 *
 *  @param os The out stream being used
 *  @param obj The Integer object we are outputting
 *
 *  @returns An ostream& to output the Integer obj given to the function out to
 *           std out
 */
std::ostream& operator<<(std::ostream& os, const Integer& obj) {
    return os << obj.integerValue;
}

/**
 *  @brief This is simply a function to aid some of the other functions
 *         in the Integer that class that optionally need their values
 *         to return in uppercase, such as the various to*String methods
 *
 *  @param str The string to be turned int32_to uppercase
 *  @returns The argumented str but uppercased, if not already
 */
void Integer::toUpperCase(std::string& str) {
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
}
