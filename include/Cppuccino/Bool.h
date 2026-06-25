#ifndef BOOL_H
#define BOOL_H

#include <iostream>
#include <any>
#include <exception>
#include <optional>
#include <compare>
#include <algorithm>
#include <memory>
#include <sstream>

class Bool {

    private:
        bool truthValue;

    public:
        static const Bool FALSE;
        static const Bool TRUE;

        Bool(const bool& value);
        Bool(const std::string& s);
        Bool(const char* s);

        static std::unique_ptr<Bool> create(const bool& value);

        bool boolValue() const;

        static int8_t compare(const bool& x, const bool& y);
        int8_t compareTo(const std::optional<Bool>& b) const;

        bool equals(const std::any& someObject) const;

        static bool getBool(std::string& name);

        int16_t hashCode() const;
        static int16_t hashCode(const bool& value);

        static bool logicalAnd(const bool& a, const bool& b);
        static bool logicalOr(const bool& a, const bool& b);
        static bool logicalXor(const bool& a, const bool& b);
        
        static bool parseBool(const std::string& s);

        std::string toString() const;
        static std::string toString(const bool& b);

        static Bool valueOf(const bool& b);
        static Bool valueOf(const std::string& s);
        static Bool valueOf(const char* s);

        auto operator<=>(const Bool& rhs) const = default;

        friend std::ostream& operator<<(std::ostream& out, const Bool& obj);

        /* NON-JAVA HELPERS */
        static void toUpperCase(std::string& s);
        static void toLowerCase(std::string& s);
};

#endif // BOOL_H