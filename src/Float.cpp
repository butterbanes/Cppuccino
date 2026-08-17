#include "../include/Cppuccino/Float.h"

/** Float(float) and Float(double) defined inline in class header **/

Float::Float(const std::string& s) {
    this->fValue = Float::parseFloat(s);
}

/**
 *  @brief Creates a memory-safe Float objet using smart pointers.
 *         The goal of this function is to mimic overloading the *new* operator
 *         since no such actual overload is possible since the original *new*
 *         operator requires a direct return of a raw void* (which isn't
 *         considered safe ofc). Think of this as just another constructor.
 *
 *  @param val The double value to use when allocating the Float obj
 *  @returns A std::unique_ptr smart pointer, many prefer using the *auto*
 *           keyword to ease the initialization of a variable of such type
 *           ```cpp
 *           auto myFloat = Float::create(15.0);
 *           ```
 */
std::unique_ptr<Float> Float::create(double value) {
    return std::make_unique<Float>(value);
}

/**
 *  @brief Creates a memory-safe Float objet using smart pointers.
 *         The goal of this function is to mimic overloading the *new* operator
 *         since no such actual overload is possible since the original *new*
 *         operator requires a direct return of a raw void* (which isn't
 *         considered safe ofc). Think of this as just another constructor.
 *
 *  @param val The float value to use when allocating the Float obj
 *  @returns A std::unique_ptr smart pointer, many prefer using the *auto*
 *           keyword to ease the initialization of a variable of such type
 *           ```cpp
 *           auto myFloat = Float::create(15.0f);
 *           ```
 */
std::unique_ptr<Float> Float::create(float value) {
    return std::make_unique<Float>(value);
}

/**
 *  @brief Returns the value of *this* Float as a int8_t byte value
 *         after a narrowing primitive conversion
 * 
 *  @return *this* float value represented after converted 
 *          to an int8_t byte value
 */
int8_t Float::byteValue() const {
    return static_cast<int8_t>(this->fValue);
}

/**
 *  @brief Compares the two specified float values. The sign of the
 *         integer value returned is the same as that of the integer
 *         that would be returned by:
 *          ```cpp
 *              Float::valueOf(f1).compareTo(Float::valueOf(f2));
 *          ```
 * 
 * @param d1 The first float to compare
 * @param d2 The second float to compare
 * @return Returns 0 if f1 == f2, 
 *                <0 if f1 < f2,
 *                >0 if f1 > f2
 */
int8_t Float::compare(float f1, float f2) {
    if (f1 < f2) return -1;
    if (f1 > f2) return 1;

    int32_t thisBits = Float::floatToIntBits(f1);
    int32_t anotherBits = Float::floatToIntBits(f2);

    return (thisBits == anotherBits ? 0 :
            (thisBits < anotherBits ? -1 :
            1));
}

/**
 *  @brief Compares two Float objects numerically.
 * 
 *         This method imposes a total order on Float objects
 *         with two difference compared to the incomplete
 *         order defined by the Java lang numerical comparison
 *         operators on double values
 *         (i.e. <, <=, ==, >=, >)
 * 
 *  @param anotherFloat The Float to be compared
 *  @return Returns 0 if f1 == f2, 
 *                <0 if f1 < f2,
 *                >0 if f1 > f2 
 */
int8_t Float::compareTo(const Float& anotherFloat) const {
    return Float::compare(this->fValue, anotherFloat.floatValue());
}

/**
 *  @brief Converts, via a widening conversion, the value held by *this*
 *         Float object to a double type
 * 
 *  @return Returns a wideningly converted float to double value 
 */
double Float::doubleValue() const {
    return static_cast<double>(this->fValue);
}

/**
 *  @brief Compares *this* Float object against the specified object.
 *         The result is true iff the arg is not null and is a Float
 *         object that represents a float that has the same value as
 *         the float represented by *this*. For this purpose, two
 *         float values are considered to be the same iff the method
 *         floatToIntBits() returns the identical long value when
 *         applied to each.
 * 
 *  @param obj The object to compare with *this* via the 
 *             floatToIntBits() method
 *  @returns true || false; dependent on the evaluation of 
 *           floatToIntBits(this) == floatToIntBits(obj)
 */
bool Float::equals(const std::any& obj) const {
    if (!obj.has_value()) {
        return false;
    }
    if (obj.type() == typeid(Float)) {
        return floatToIntBits(std::any_cast<Float>(obj).fValue) == floatToIntBits(this->fValue);
    }
    return false;
}

/**
 *  @brief Checks if given value is not a NaN. Dependent on the result
 *         of Float::isNaN(float), the value is given to the 
 *         Float::floatToRawIntBits(float), otherwise Float::NaN is
 *         returned
 * 
 *  @param value The value to be converted to int32_t 
 *  @return A float casted to int32_t type via an internal std::bit_cast 
 *          of the argument iff the given argument isn't NaN
 */
int32_t Float::floatToIntBits(float value) {
    return !Float::isNaN(value) ? Float::floatToRawIntBits(value) : Float::NaN;
}

/**
 *  @brief Using a std::bit_cast, converts the bits of the given float value
 *         to match the layout of an int32_t bit layout
 * 
 *  @param value The value to be converted
 *  @returns A bit casted int32_t from the given float value
 */
int32_t Float::floatToRawIntBits(float value) {
    return std::bit_cast<int32_t>(value);
}

/**
 *  @brief Returns the value held by *this* Float object
 * 
 *  @returns Returns this->fValue
 */
float Float::floatValue() const {
    return this->fValue;
}

/**
 *  @brief Converts the bits of a given int32_t to a float type via
 *         a std::bit_cast
 * 
 *  @param bits The int32_t value whose bits to cast to a float type
 *  @returns A bit casted float from int32_t value
 */
float Float::intBitsToFloat(int32_t bits) {
    return std::bit_cast<float>(bits);
}

/**
 *  @brief Converts, via a narrowing primitive conversion, the float value
 *         held by *this*, to an int32_t
 * 
 *  @returns *this* float value converted to an int32_t
 */
int32_t Float::intValue() const {
    return static_cast<int32_t>(this->fValue);
}

/**
 *  @brief Checks the argumented value if it's finite
 * 
 *  @param d The value to check if it is finite
 *  @returns true || false;
 *           dependent on the absolute value of the 
 *           argumented float value compared to the 
 *           Float::MAX_VALUE constant
 */
bool Float::isFinite(float f) {
    return std::abs(f) <= Float::MAX_VALUE;
}

/**
 *  @brief Checks if the float value held by *this*
 *         is an infinite value or not
 * 
 *  @returns true || false;
 *           dependent on what is returned by calling
 *           Float::isInfinite(this->fValue)
 */
bool Float::isInfinite() const {
    return Float::isInfinite(this->fValue);
}

/**
 *  @brief Checks if the float value held by the
 *         argumented value is infinite value
 * 
 *  @returns true || false;
 *           dependent on what is returned by comparing
 *           the float argument to Float::MAX_VALUE
 */
bool Float::isInfinite(float f) {
    return std::abs(f) > Float::MAX_VALUE;
}

/**
 *  @brief Checks if the value held by *this* Float
 *         object is NaN
 * 
 *  @returns true || false;
 *           dependent on what is returned by calling
 *           Float::isNan(this->fValue)
 */
bool Float::isNaN() const {
    return Float::isNaN(this->fValue);
}

/**
 *  @brief Checks if the value held by the Float
 *         object passed as an argument is NaN
 * 
 *  @returns true || false;
 *           dependent on what is returned by calling
 *           std::isnan(float);
 */
bool Float::isNaN(float v) {
    return std::isnan(v);
}

/**
 *  @brief Converts, via a narrowing primitive conversion, the float value
 *         held by *this*, to an int64_t (long)
 * 
 *  @returns *this* float value converted to an int64_t (long)
 */
int64_t Float::longValue() const {
    return static_cast<int64_t>(this->fValue);
}

/**
 *  @brief Returns the greater of the two float values
 *         passed as arguments as if by calling the std::max()
 *         method
 *
 *  @param a The first operand
 *  @param b The second operand
 *  @returns The greater of the two argumented operands
 */
float Float::max(float a, float b) {
    return std::max(a, b);
}

/**
 *  @brief Returns the lesser of the two float values
 *         passed as arguments as if by calling the std::min()
 *         method
 *
 *  @param a The first operand
 *  @param b The second operand
 *  @returns The lesser of the two argumented operands
 */
float Float::min(float a, float b) {
    return std::min(a, b);
}

/**
 *  @brief Returns a new float initialized to the value represented
 *         by the specified std::string, as performed by the
 *         Float::valueOf() method.
 * 
 *  @param s The string to be parsed
 *  @returns The float value represented by the std::string arg
 */
float Float::parseFloat(const std::string& s) {
    return Float::valueOf(s).floatValue();
}

/**
 *  @brief Converts, via a narrowing primitive conversion, the float value
 *         held by *this*, to an int16_t (short)
 * 
 *  @returns *this* float value converted to an int16_t (short)
 */
int16_t Float::shortValue() const {
    return static_cast<int16_t>(this->fValue);
}

/**
 *  @brief Adds two float values together as per the + operator
 * 
 *  @param a The first operand
 *  @param b The second operand
 *  @returns The sum of a and b
 */
float Float::sum(float a, float b) {
    return a + b;
}

/**
 *  @brief Returns a hexadecimal string representation of the float
 *         argument.
 *         
 *         If the argument is NaN, the resulting string is "NaN".
 *         Otherwise, the result is a string that represents the sign
 *         and magnitude of the argument.
 *         If the sign is negative '-' the first character of the returned
 *         string will contain a '-'. If no sign appears is positive, no
 *         sign character will appear in the result.
 * 
 *  @param f The float value to be converted to a hex string
 *  @returns A hex string representation of the argument
 */
std::string Float::toHexString(float f) {
    if (!Float::isFinite(f)) {
        return Float::toString(f);
    }
    
    bool negative = Float::floatToIntBits(f) < 0.0f;

    if (f == 0.0f) {
        return (negative) ? "-0x0.0p0f" : "0x0.0p0f";
    }

    std::stringstream ss;
    ss << std::hexfloat << f;
    std::string result = ss.str();

    size_t plusSymPos = result.find("p+");
    if (plusSymPos != std::string::npos) {
        result.erase(plusSymPos+1, 1);
    }

    return result;
}

/**
 *  @brief Returns a string representation of the value held
 *         by *this* Float object as if by calling the
 *         Float::toString(float) method
 * 
 *  @returns a std::string representation of *this* Float 
 *           object's value
 */
std::string Float::toString() const {
    return Float::toString(this->fValue);
}

/**
 *  @brief Returns a string representation of the argumented
 *         float value.
 * 
 *         Any call to this function with a negative float value,
 *         the negative sign '-' will be retained in the returned
 *         string. Should a positive value be provided, NO plus
 *         symbol '+' will exist in the returned string
 * 
 *         If the argument is NaN, "NaN" is returned.
 *         If the argument is positive inf, "Infinity" is returned
 *         If the argument is negative inf, "-Infinity" is returned
 *         
 *         If the argument is positive or negative 0.0, "0.0" is 
 *         returned with its respective sign should -0.0 be 
 *         provided
 * 
 *         Apart from the previous caveats of return values, the argument
 *         will be positive and finite, which, at this point, will be converted
 *         to a string with std::to_string
 * 
 *  @param f The float value to be converted to a string
 *  @returns A std::string containing the value given by the argument d
 */
std::string Float::toString(float f) {
    if (f == Float::POSITIVE_INFINITY) {
        return "Infinity";
    }
    if (f == Float::NEGATIVE_INFINITY) {
        return "-Infinity";
    }
    if (Float::isNaN(f)) {
        return "NaN";
    }
    if (f == 0.0f) {
        return std::signbit(f) ? "-0.0f" : "0.0f";
    }

    return std::to_string(f);
}

/**
 *  @brief Returns a Float instance representing the specified
 *         float value provided by the argument
 * 
 *  @param f The float value to use
 *  @returns a Float instance representing d
 */
Float Float::valueOf(float f) {
    return Float(f);
}

/**
 *  @brief Returns a Float instance representing the speicifed
 *         value given by the std::string argument via the
 *         Float::parseFloat(std::string) method
 * 
 *  @param s The std::string to convert to a float that is
 *           given and returned as a new Float instance
 *  @returns a Float instance representing the value presented
 *           by the std::string argument s
 */
Float Float::valueOf(const std::string& s) {
    if (!s.compare("Infinity")) {
        return Float(Float::POSITIVE_INFINITY);
    }
    if (!s.compare("-Infinity")) {
        return Float(Float::NEGATIVE_INFINITY);
    }
    if (!s.compare("NaN")) {
        return Float(Float::NaN);
    }
    if (!s.compare("0.0f")) {
        return Float(0.0);
    }
    if (!s.compare("-0.0f")) {
        return Float(-0.0f);
    }

    float val = 0.0f;
    auto [ptr, ec] = std::from_chars(s.data(), s.data() + s.size(), val);

    if (ec == std::errc()) {
        if (ptr != s.data() + s.size()) {
            std::cerr << "ERROR: Some character remain unparsed | Invalid characters?";
        }
    }

    /// normally, we would check for NaN and OOR but we 
    /// account for those items at the beginning of this 
    /// method
    return val;
}

/**
 *  @brief Provides equals comparision between two variables,
 *         presumably two Float objects. Makes use of the
 *         Float::compareTo(Float) method
 * 
 *  @param rhs The other Float to compare to
 *  @returns true || false;
 *           dependent on what is returned by calling
 *           Float::equals(std::any);
 */
bool Float::operator==(const Float& rhs) const {
    return this->equals(rhs);
}


std::strong_ordering Float::operator<=>(const Float& rhs) const {
    int8_t result = this->compareTo(rhs);
    if (result < 0) return std::strong_ordering::less;
    if (result > 0) return std::strong_ordering::greater;
    return std::strong_ordering::equal;
}

/**
 *  @brief Modiifies an outstream for use in C++ cout "printing"
 *         (i.e. std::cout << Float(5.5));
 * 
 *  @param out The outstream to modify for printing use
 *  @param rhs The Float object to output
 *  @returns Returns the modified outstream to output the value
 *           of the provided Float object
 */
std::ostream& operator<<(std::ostream& out, const Float& rhs) {
    out << rhs.toString();
    return out;
}