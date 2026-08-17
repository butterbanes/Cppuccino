#include "../include/Cppuccino/Double.h"

/** Double(double) defined inline in class header **/
// Double(double value) : doubleValue(static_cast<double>(value));

Double::Double(const std::string& s) {
    this->dValue = Double::parseDouble(s);
}

/**
 *  @brief Creates a memory-safe Double objet using smart pointers.
 *         The goal of this function is to mimic overloading the *new* operator
 *         since no such actual overload is possible since the original *new*
 *         operator requires a direct return of a raw void* (which isn't
 *         considered safe ofc). Think of this as just another constructor.
 *
 *  @param val The double value to use when allocating the Double obj
 *  @returns A std::unique_ptr smart pointer, many prefer using the *auto*
 *           keyword to ease the initialization of a variable of such type
 *           ```cpp
 *           auto myDouble = Double::create(15.0);
 *           ```
 */
std::unique_ptr<Double> Double::create(double value) {
    return std::make_unique<Double>(value);
}

/**
 *  @brief Returns the value of *this* Double as a int8_t byte value
 *         after a narrowing primitive conversion
 * 
 *  @return *this* double value represented after converted 
 *          to an int8_t byte value
 */
int8_t Double::byteValue() const {
    return static_cast<int8_t>(this->dValue);
}

/**
 *  @brief Compares the two specified double values. The sign of the
 *         integer value returned is the same as that of the integer
 *         that would be returned by:
 *          ```cpp
 *              Double::valueOf(d1).compareTo(Double::valueOf(d2));
 *          ```
 * 
 * @param d1 The first double to compare
 * @param d2 The second double to compare
 * @return Returns 0 if d1 == d2, 
 *                <0 if d1 < d2,
 *                >0 if d1 > d2
 */
int8_t Double::compare(double d1, double d2) {
    if (d1 < d2) return -1;
    if (d1 > d2) return 1;

    int64_t thisBits = Double::doubleToLongBits(d1);
    int64_t anotherBits = Double::doubleToLongBits(d2);

    return (thisBits == anotherBits ? 0 :
            (thisBits < anotherBits ? -1 :
            1));
}

/**
 *  @brief Compares two Double objects numerically.
 * 
 *         This method imposes a total order on Double objects
 *         with two difference compared to the incomplete
 *         order defined by the Java lang numerical comparison
 *         operators on double values
 *         (i.e. <, <=, ==, >=, >)
 * 
 *  @param anotherDouble The Double to be compared
 *  @return Returns 0 if d1 == d2, 
 *                <0 if d1 < d2,
 *                >0 if d1 > d2 
 */
int8_t Double::compareTo(const Double& anotherDouble) const {
    return Double::compare(this->dValue, anotherDouble.doubleValue());
}

/**
 *  @brief Returns a representation of the specified floating-point
 *         value according to the IEEE 754 floating-point "double
 *         format" bit layout.
 * 
 *         Bit 63 (the bit that is selected by the mask
 *         0x8000000000000000L) represents the sign of the
 *         floating-point number. Bits
 *         62-52 (the bits that are selected by the mask
 *         0x7ff0000000000000L) represent the exponent. Bits 51-0
 *         (the bits that are selected by the mask
 *         0x000fffffffffffffL) represent the significand
 *         (sometimes called the mantissa) of the floating-point number.
 * 
 *         If the argument is positive infinity, the result is
 *         Double::POSITIVE_INFINITY.
 *    
 *         If the argument is negative infinity, the result is
 *         Double::NEGATIVE_INFINITY.
 *    
 *         If the argument is NaN, the result is
 *         Double::NaN.
 *    
 *         In all cases, the result is a long integer that, when
 *         given to the longBitsToDouble(long) method, will produce a
 *         floating-point value the same as the argument to
 *         doubleToLongBits (except all NaN values are
 *         collapsed to a single "canonical" NaN value).
 *    
 *  @param value A double precision floating-point number.
 *  @return the bits that represent the floating-point number.
 */
int64_t Double::doubleToLongBits(double value) {
    return !Double::isNaN(value) ? doubleToRawLongBits(value) : Double::NaN;
}

/**
 *  @brief Returns a representation of the specified floating-point value
 *         according to the IEEE 754 floating-point "double
 *         format" bit layout, preserving Not-a-Number (NaN) values.
 *
 *         Bit 63 (the bit that is selected by the mask
 *         0x8000000000000000L) represents the sign of the
 *         floating-point number. Bits
 *         62-52 (the bits that are selected by the mask
 *         0x7ff0000000000000L) represent the exponent. Bits 51-0
 *         (the bits that are selected by the mask
 *         0x000fffffffffffffL) represent the significand
 *         (sometimes called the mantissa) of the floating-point number.
 *
 *         If the argument is positive infinity, the result is
 *         0x7ff0000000000000L. (Double::POSITIVE_INFINITY)
 *
 *         If the argument is negative infinity, the result is
 *         0xfff0000000000000L. (Double::NEGATIVE_INFINITY)
 *
 *         If the argument is NaN, the result is the long
 *         integer representing the actual NaN value.  Unlike the
 *         doubleToLongBits method,
 *         doubleToRawLongBits does not collapse all the bit
 *         patterns encoding a NaN to a single "canonical" NaN
 *         value.
 *
 *         In all cases, the result is a long integer that,
 *         when given to the longBitsToDouble(long) method, will
 *         produce a floating-point value the same as the argument to
 *         doubleToRawLongBits.
 * 
 *  @param value A double precision floating-point number
 *  @return The bits that represent the floating-point number 
 */
int64_t Double::doubleToRawLongBits(double value) {
    return std::bit_cast<int64_t>(value);
}

/**
 *  @brief Returns the double value held by *this*
 * 
 *  @returns Returns this->dValue
 */
double Double::doubleValue() const {
    return this->dValue;
}

/**
 *  @brief Compares *this* Double object against the specified object.
 *         The result is true iff the arg is not null and is a Double
 *         object that represents a double that has the same value as
 *         the double represented by *this*. For this purpose, two
 *         double values are considered to be the same iff the method
 *         doubleToLongBits() returns the identical long value when
 *         applied to each.
 * 
 *  @param obj The object to compare with *this* via the 
 *             doubleToLongBits() method
 *  @returns true || false; dependent on the evaluation of 
 *           doubleToLongBits(this) == doubleToLongBits(obj)
 */
bool Double::equals(const std::any& obj) const {
    if (!obj.has_value()) {
        return false;
    }
    if (obj.type() == typeid(Double)) {
        return doubleToLongBits(std::any_cast<Double>(obj).dValue) == doubleToLongBits(this->dValue);
    }
    return false;
}

/**
 *  @brief Returns a narrowing conversion of the double value *this* holds
 * 
 *  @returns Returns the double value held by *this* after a narrowing
 *           conversion
 */
float Double::floatValue() const {
    return static_cast<float>(this->dValue);
}

/**
 *  @brief Returns a hash code for *this* Double object. The result is
 *         the exclusive OR of the two halves of the long integer bit
 *         representation, exactly as presented by the method
 *         doubleToLongBits(), of the primitive double value represented
 *         by *this* Double object.
 * 
 *  @returns A hash code value for *this* Double object 
 */
int32_t Double::hashCode() const {
    return Double::hashCode(this->dValue);
}

/**
 *  @brief Returns a hash code for a argumented Double object. The 
 *         result is the exclusive OR of the two halves of the long 
 *         integer bit representation, exactly as presented by the 
 *         method doubleToLongBits(), of the primitive double value
 *         represented by the passed Double object.
 * 
 *  @param value The value whose hash code to get
 *  @returns A hash code value for the Double object argument
 *  @note In the Java source code, this method calls on 
 *        "Long.hashCode(value)", which since this class is built
 *        first, we will swap which class calls on which. The overall
 *        implementation and functionality will be exactly the same :)
 *  @note We cast to uint64_t before our ">>" bit shift in order to mimic
 *        Java's unsigned right bit-shift >>> operator
 */
int32_t Double::hashCode(double value) {
    return static_cast<int32_t>(Double::doubleToRawLongBits(value) ^ (static_cast<uint64_t>(doubleToRawLongBits(value)) >> 32));
}

/**
 *  @brief Converts the double value held by *this* Double object to 
 *         an int32_t data type via a narrowing primitive conversion
 * 
 *  @returns Returns the double value held by *this* Double object
 *           after a narrowing primitive conversion to an int32_t
 *           data type
 */
int32_t Double::intValue() const {
    return static_cast<int32_t>(this->dValue);
}

/**
 *  @brief Checks the argumented value if it's finite
 * 
 *  @param d The value to check if it is finite
 *  @returns true || false;
 *           dependent on the absolute value of the 
 *           argumented double value compared to the 
 *           Double::MAX_VALUE constant
 */
bool Double::isFinite(double d) {
    return std::abs(d) <= Double::MAX_VALUE;
}

/**
 *  @brief Checks if the double value held by *this*
 *         is an infinite value or not
 * 
 *  @returns true || false;
 *           dependent on what is returned by calling
 *           Double::isInfinite(this->dValue)
 */
bool Double::isInfinite() const {
    return Double::isInfinite(this->dValue);
}

/**
 *  @brief Checks if the double value held by the
 *         argumented value is infinite value
 * 
 *  @returns true || false;
 *           dependent on what is returned by comparing
 *           the double argument to Double::MAX_VALUE
 */
bool Double::isInfinite(double d) {
    return std::abs(d) > Double::MAX_VALUE;
}

/**
 *  @brief Checks if the value held by *this* Double
 *         object is NaN
 * 
 *  @returns true || false;
 *           dependent on what is returned by calling
 *           Double::isNan(this->dValue)
 */
bool Double::isNaN() const {
    return Double::isNaN(this->dValue);
}

/**
 *  @brief Checks if the value held by the Double
 *         object passed as an argument is NaN
 * 
 *  @returns true || false;
 *           dependent on what is returned by calling
 *           std::isnan(double);
 */
bool Double::isNaN(double v) {
    return std::isnan(v);
}

/**
 *  @brief Returns the double value corresponding to the a givern
 *         bit representation. The arg is considered to be a representation
 *         of a floating-point valuie according to the IEEE754 floating-point
 *         "double format" bit layout
 * 
 *         If the argument is positive infinity, the result is
 *         Double::POSITIVE_INFINITY; if negative infinity, the
 *         retult is Double::NEGATIVE_INFINITY; otherwise, the
 *         result is considered NaN.
 * 
 *         There is no true way to distinguish between two NaN vals
 *         of the same type with different bit patterns. Distinct vals
 *         of NaN are only distinguishable via the 
 *         Double::doubleToRawLongBits() method
 * 
 *  @param bits The long data-type var to convert to a double type
 *  @returns A double converted from the argumented int64_t (long)
 *           variable via the std::bit_cast() function
 */
double Double::longBitsToDouble(int64_t bits) {
    return std::bit_cast<double>(bits);
}

/**
 *  @brief Provides a narrowing primitive conversion of the double
 *         value held by *this* Double object to int64_t (long)
 * 
 *  @returns An int64_t after the value held by *this* Double object
 *           undergoes a narrowing primitive conversion
 */
int64_t Double::longValue() const {
    return static_cast<int64_t>(this->dValue);
}

/**
 *  @brief Returns the greater of the two double values
 *         passed as arguments as if by calling the std::max()
 *         method
 *
 *  @param a The first operand
 *  @param b The second operand
 *  @returns The greater of the two argumented operands
 */
double Double::max(double a, double b) {
    return std::max(a, b);
}

/**
 *  @brief Returns the lesser of the two double values
 *         passed as arguments as if by calling the std::min()
 *         method
 *
 *  @param a The first operand
 *  @param b The second operand
 *  @returns The lesser of the two argumented operands
 */
double Double::min(double a, double b) {
    return std::min(a, b);
}

/**
 *  @brief Returns a new double initialized to the value represented
 *         by the specified std::string, as performed by the
 *         Double::valueOf() method.
 * 
 *  @param s The string to be parsed
 *  @returns The double value represented by the std::string arg
 */
double Double::parseDouble(const std::string& s) {
    return Double::valueOf(s).doubleValue();
}

/**
 *  @brief Performs a narrowing primitive conversion of the double
 *         value held by *this* Double object to int16_t (short)
 * 
 *  @returns An int16_t (short) value of a narrowingly primitive conversion
 *           of the double value held by *this* Double object
 */
int16_t Double::shortValue() const {
    return static_cast<int16_t>(this->dValue);
}

/**
 *  @brief Adds two double values together as per the + operator
 * 
 *  @param a The first operand
 *  @param b The second operand
 *  @returns The sum of a and b
 */
double Double::sum(double a, double b) {
    return a + b;
}

/**
 *  @brief Returns a hexadecimal string representation of the double
 *         argument.
 *         
 *         If the argument is NaN, the resulting string is "NaN".
 *         Otherwise, the result is a string that represents the sign
 *         and magnitude of the argument.
 *         If the sign is negative '-' the first character of the returned
 *         string will contain a '-'. If no sign appears is positive, no
 *         sign character will appear in the result.
 * 
 *  @param d The double value to be converted to a hex string
 *  @returns A hex string representation of the argument
 */
std::string Double::toHexString(double d) {
    if (!Double::isFinite(d)) {
        return Double::toString(d);
    }
    
    bool negative = Double::doubleToLongBits(d) < 0;

    if (d == 0.0) {
        return (negative) ? "-0x0.0p0" : "0x0.0p0";
    }
    

    std::stringstream ss;
    ss << std::hexfloat << d;
    std::string result = ss.str();

    size_t plusSymPos = result.find("p+");
    if (plusSymPos != std::string::npos) {
        result.erase(plusSymPos+1, 1);
    }

    return result;
}

/**
 *  @brief Returns a string representation of the value held
 *         by *this* Double object as if by calling the
 *         Double::toString(double) method
 * 
 *  @returns a std::string representation of *this* Double 
 *           object's value
 */
std::string Double::toString() const {
    return Double::toString(this->dValue);
}

/**
 *  @brief Returns a string representation of the argumented
 *         double value.
 * 
 *         Any call to this function with a negative double value,
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
 *  @param d The double value to be converted to a string
 *  @returns A std::string containing the value given by the argument d
 */
std::string Double::toString(double d) {
    if (d == Double::POSITIVE_INFINITY) {
        return "Infinity";
    }
    if (d == Double::NEGATIVE_INFINITY) {
        return "-Infinity";
    }
    if (Double::isNaN(d)) {
        return "NaN";
    }
    if (d == 0.0) {
        return std::signbit(d) ? "-0.0" : "0.0";
    }

    return std::to_string(d);
}

/**
 *  @brief Returns a Double instance representing the specified
 *         double value provided by the argument
 * 
 *  @param d The double value to use
 *  @returns a Double instance representing d
 */
Double Double::valueOf(double d) {
    return Double(d);
}

/**
 *  @brief Returns a Double instance representing the speicifed
 *         value given by the std::string argument via the
 *         Double::parseDouble(std::string) method
 * 
 *  @param s The std::string to convert to a double that is
 *           given and returned as a new Double instance
 *  @returns a Double instance representing the value presented
 *           by the std::string argument s
 */
Double Double::valueOf(const std::string& s) {
    if (!s.compare("Infinity")) {
        return Double(Double::POSITIVE_INFINITY);
    }
    if (!s.compare("-Infinity")) {
        return Double(Double::NEGATIVE_INFINITY);
    }
    if (!s.compare("NaN")) {
        return Double(Double::NaN);
    }
    if (!s.compare("0.0")) {
        return Double(0.0);
    }
    if (!s.compare("-0.0")) {
        return Double(-0.0);
    }

    double val = 0.0;
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
 *         presumably two Double objects. Makes use of the
 *         Double::compareTo(Double) method
 * 
 *  @param rhs The other Double to compare to
 *  @returns true || false;
 *           dependent on what is returned by calling
 *           Double::equals(std::any);
 */
bool Double::operator==(const Double& rhs) const {
    return this->equals(rhs);
}


std::strong_ordering Double::operator<=>(const Double& rhs) const {
    int8_t result = this->compareTo(rhs);
    if (result < 0) return std::strong_ordering::less;
    if (result > 0) return std::strong_ordering::greater;
    return std::strong_ordering::equal;
}

/**
 *  @brief Modiifies an outstream for use in C++ cout "printing"
 *         (i.e. std::cout << Double(5.5));
 * 
 *  @param out The outstream to modify for printing use
 *  @param rhs The Double object to output
 *  @returns Returns the modified outstream to output the value
 *           of the provided Double object
 */
std::ostream& operator<<(std::ostream& out, const Double& rhs) {
    out << rhs.toString();
    return out;
}