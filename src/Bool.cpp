#include "../include/Cppuccino/Bool.h"

// defining the representatives of the primitive
const Bool Bool::FALSE = Bool(false);
const Bool Bool::TRUE = Bool(true);

Bool::Bool(bool value) {
    this->truthValue = value;
}

Bool::Bool(const std::string& s) {
    this->truthValue = Bool::parseBool(s);
}

Bool::Bool(const char* s) {
    this->truthValue = Bool::parseBool(std::string(s));
}

/**
 *  @brief Creates a memory-safe Bool objet using smart pointers.
 *         The goal of this function is to mimic overloading the *new* operator
 *         since no such actual overload is possible since the original *new*
 *         operator requires a direct return of a raw void* (which isn't
 *         considered safe ofc). Think of this as just another constructor.
 *
 *  @param value The bool value to use when allocating the Bool obj
 *  @returns A std::unique_ptr smart pointer, many prefer using the *auto*
 *           keyword to ease the initialization of a variable of such type
 *           ```cpp
 *           auto myBool = Bool::create(true);
 *           ```
 */
std::unique_ptr<Bool> Bool::create(bool value) {
    return std::make_unique<Bool>(value);
}

/**
 *  @brief Returns the value of *this* object as a bool primitive
 *  
 *  @returns the primitive bool value of *this* object
 */
bool Bool::boolValue() const {
    return this->truthValue;
}

/**
 *  @brief Compares two bool values. The value returned is identical
 *         to the value of what would be returned by:
 *              Bool::valueOf(x).compareTo(Bool::valueOf(y));
 * 
 *  @param x The first bool variable to compare
 *  @param y The second bool variable to compare
 *  @returns 0 IF x == y, 
 *           < 0 IF !x && y, 
 *           > 0 IF x && !y
 */
int8_t Bool::compare(bool x, bool y) {
    return (x == y) ? 0 : (x ? 1 : -1); 
}

/**
 *  @brief Compares *this* Bool instance with another
 * 
 *  @param b The Bool instance to be compared
 *  @returns 0 if *this* object represents the same boolean value as the
 *           argument; a positive value if *this* object represents true
 *           and the argument represents false; and a negative value if
 *           *this* object represents false and the argument represents true
 */
int8_t Bool::compareTo(const std::optional<Bool>& b) const {
    try {
        if (!b.has_value()) {
            throw std::invalid_argument("ERR: cannot compare a null pointer");
        } else {
            return compare(this->truthValue, b->boolValue());
        } 
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << '\n';
    }
}

/**
 *  @brief Returns true iff the arg is not null and it a Bool object that
 *         represents the same bool value as *this* object
 *  
 *  @param obj The object to compare with
 *  @returns true iff the Bool objects represent the same value, false otherwise
 */
bool Bool::equals(const std::any& someObject) const {
    if (!someObject.has_value()) {
        return false;
    }

    if (someObject.type() == typeid(Bool)) {
        return this->truthValue == std::any_cast<Bool>(someObject).boolValue();
    }

    if (someObject.type() == typeid(bool)) {
        return this->truthValue == std::any_cast<bool>(someObject);
    }

    return false;
}

/**
 *  @brief Since C++ doesn't use system properties like Java does with its getBoolean()
 *         we are just going to return the bool value of the passed std::string if it
 *         fits into the Bool(const std::string) constructor (i.e. is "true" or "false")
 * 
 *  @param s The string to gather a bool value from
 *  @returns the bool value of the passed std::string 
 */
bool Bool::getBool(std::string& name) {
    return Bool{name}.boolValue();
}

/**
 *  @brief Returns a hashcode for *this* Bool object
 * 
 *  @returns the integer 1231 if *this* object represents true
 *           OR
 *           the integer 1237 if *this* object represents false 
 */
int16_t Bool::hashCode() const {
    return Bool::hashCode(this->truthValue);
}

/**
 *  @brief Returns a hash code for a bool value. Compatible with
 *         Bool::hashCode() 
 * 
 *  @param value The bool value to get a hash code of
 *  @returns a hash code for a bool value
 */
int16_t Bool::hashCode(bool value){
    return value ? 1231 : 1237;
}

/**
 *  @brief Returns the result of applying the logical AND operator
 *         to the specified bool operands
 *
 *  @param a The first operand
 *  @param b The second operand
 *  @returns The logical AND of both operands 
 */
bool Bool::logicalAnd(bool a, bool b) {
    return a && b;
}

/**
 *  @brief Returns the result of applying the logical OR operator
 *         to the specified bool operands
 *
 *  @param a The first operand
 *  @param b The second operand
 *  @returns The logical OR of both operands 
 */
bool Bool::logicalOr(bool a, bool b) {
    return a || b;
}

/**
 *  @brief Returns the result of applying the logical XOR operator
 *         to the specified bool operands
 *
 *  @param a The first operand
 *  @param b The second operand
 *  @returns The logical XOR of both operands 
 */
bool Bool::logicalXor(bool a, bool b) {
    return a ^ b;
}

/**
 *  @brief Parses the std::string arg as a bool. The bool value returned
 *         represents true if the string is not null and is equals, ignoring
 *         case, to the string "true". Otherwise false is returned (including
 *         for a null argument)
 *  @param s the std::string containing the bool representation to be parsed
 *  @returns the bool represented by the string arg
 */
bool Bool::parseBool(const std::string& s) {
    std::string sCopy = s;
    Bool::toLowerCase(sCopy);
    return sCopy == "true";
}

/**
 *  @brief Returns a std::string representing *this* Bool's truthValue.
 *         If *this* object is true, the string returned is "true". Otherwise,
 *         a string "false" is returned.
 * 
 *  @returns a string represention of *this* object 
 */
std::string Bool::toString() const {
    return Bool::toString(this->truthValue);
}

/**
 *  @brief Returns a std::string representing a specified bool.
 *         If the specified bool is true, the string returned is "true". Otherwise,
 *         a string "false" is returned.
 * 
 *  @param b The bool to be converted
 *  @returns a string represention of a bool
 */
std::string Bool::toString(bool b) {
    return (b ? "true" : "false");
}

/**
 *  @brief Returns a Bool instance representing the specified bool value.
 *         If the specified bool value is true, this method returns Bool::TRUE.
 *         If the specified bool value is false, this method returns Bool::FALSE.
 * 
 *  @note JavaDocs recommends using this method over the actual Bool constructor
 *        because it's claimed to have better time and space performance (supposedly),
 *        but I'd say its up to you, the user, because based on my tests
 *        (and this just might be how C++ works under the hood) but the constructors seem
 *        to have better marks than the valueOf() functions.
 * 
 *  @param b A bool value 
 *  @return a Bool instance representing b
 */
Bool Bool::valueOf(bool b) {
    return (b ? Bool::TRUE : Bool::FALSE);
}

/**
 *  @brief Returns a Bool with a value represented by the specified std::string.
 *         The Bool returned represents a true value if the std::string arg is not
 *         null and is equal, ignoring case, to the string "true".
 *         Otherwise, a false value is returned, including for a null arg.
 * 
 *  @param s A std::string
 *  @return the Bool value represented by the std::string
 */
Bool Bool::valueOf(const std::string& s) {
    return (parseBool(s) ? Bool::TRUE : Bool::FALSE);
}

/**
 *  @brief Returns a Bool with a value represented by the specified char*.
 *         The Bool returned represents a true value if the char* arg is not
 *         null and is equal, ignoring case, to the string "true".
 *         Otherwise, a false value is returned, including for a null arg.
 * 
 *  @param s A char*
 *  @return the Bool value represented by the char*
 */
Bool Bool::valueOf(const char* s) {
    return Bool::valueOf(std::string(s));
}

/**
 *  @brief Returns an ostream reference to implement the << operator for the
 *         std::cout when printing Bool objects
 *
 *  @param os The out stream being used
 *  @param obj The Bool object we are outputting
 *
 *  @returns An ostream& to output the Integer obj given to the function out to
 *           std out
 */
std::ostream& operator<<(std::ostream& out, const Bool& obj) {
    return out << std::boolalpha << obj.boolValue();
}

void Bool::toUpperCase(std::string& s) {
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
}

void Bool::toLowerCase(std::string& s) {
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
}