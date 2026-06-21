#include "../../include/Cppuccino/Integer.h"

#include <gtest/gtest.h>

TEST(IntegerTest, CheckPublicConstValues) {
    EXPECT_EQ(Integer::BYTES, 4) << "Should be '4'";
    EXPECT_EQ(Integer::MAX_VALUE, INT_MAX) << "Should be '2147483647'";
    EXPECT_EQ(Integer::MIN_VALUE, INT_MIN) << "Should be '-2147483648'";
    EXPECT_EQ(Integer::SIZE, 32) << "Should be '32'";
}

TEST(IntegerTest, CheckTypeReturnedByConstructors) {
    EXPECT_EQ(typeid(Integer(rand() % 10)), typeid(Integer)) << "Should be 'Integer'";

    EXPECT_EQ(typeid(Integer("test name")), typeid(Integer)) << "Should be 'Integer'";
}

TEST(IntegerTest, CreateFunction) {
    EXPECT_EQ(typeid(Integer::create(15)).name(), typeid(std::unique_ptr<Integer>).name());
    EXPECT_NE(Integer::create(15), nullptr);
}

TEST(IntegerTest, BitCountFunction) {
    EXPECT_EQ(Integer::bitCount(2), 1);
    EXPECT_EQ(Integer::bitCount(3), 2);
}

TEST(IntegerTest, ByteValueFunction) {
    EXPECT_EQ(Integer(15).byteValue(), std::byte(0x0F));
    EXPECT_EQ(Integer(16).byteValue(), std::byte(0x10));
    EXPECT_EQ(Integer(0).byteValue(), std::byte(0x00));
}

TEST(IntegerTest, CompareFunction) {
    EXPECT_LT(Integer::compare(1, 2), 0);
    EXPECT_EQ(Integer::compare(2, 2), 0);
    EXPECT_GT(Integer::compare(2, 1), 0);
}

TEST(IntegerTest, CompareToFunction) {
    EXPECT_LT(Integer(1).compareTo(Integer(2)), 0);
    EXPECT_EQ(Integer(2).compareTo(Integer(2)), 0);
    EXPECT_GT(Integer(2).compareTo(Integer(1)), 0);
}

TEST(IntegerTest, CompareUnsignedFunction) {
    EXPECT_LT(Integer::compare(1, 2), 0);
    EXPECT_EQ(Integer::compare(2, 2), 0);
    EXPECT_GT(Integer::compare(2, 1), 0);
}

TEST(IntegerTest, DecodeFunction) {
    // cleaner syntax within single TEST block
    auto check_decode = [](const std::string& input, int expected) {
        SCOPED_TRACE("Testing input: " + input);
        Integer result = Integer::decode(input);
        EXPECT_EQ(result.intValue(), expected);
    };

    check_decode("500", 500);
    check_decode("-100", -100);
    check_decode("0", 0);

    // hex with 0x
    check_decode("0x10", 16);
    check_decode("0XFF", 255);
    check_decode("-0x1", -1);

    // hex with #
    check_decode("#10", 16);
    check_decode("#FF", 255);

    // octal
    check_decode("010", 8);
    check_decode("0123", 83);

    // edge cases
    EXPECT_NO_THROW({
        Integer::decode("not_a_number");
        Integer::decode("");
        Integer::decode("0xZZZ");
    });
}

TEST(IntegerTest, DivideUnsignedFunction) {
    EXPECT_EQ(Integer::divideUnsigned(static_cast<int>(16), static_cast<int>(4)), 4);
    EXPECT_EQ(Integer::divideUnsigned(static_cast<int>(-16), static_cast<int>(4)),
              ((std::pow(2, 32) - 16) / 4));
}

TEST(IntegerTest, DoubleValueFunction) {
    EXPECT_EQ(Integer(static_cast<int>(15)).doubleValue(), 15.0);
    EXPECT_EQ(Integer(static_cast<int>(-15)).doubleValue(), -15.0);
    EXPECT_EQ(Integer("15").doubleValue(), 15.0);
}

TEST(IntegerTest, EqualsFunction) {
    EXPECT_TRUE(Integer(15).equals(Integer(15)));
    EXPECT_TRUE(Integer(15).equals(Integer("15")));
    EXPECT_TRUE(Integer("15").equals(Integer(15)));
    EXPECT_TRUE(Integer("15").equals(Integer("15")));

    EXPECT_FALSE(Integer(15).equals(Integer(16)));
    EXPECT_FALSE(Integer(15).equals(Integer("16")));
    EXPECT_FALSE(Integer("15").equals(Integer(16)));
    EXPECT_FALSE(Integer("15").equals(Integer("16")));

    EXPECT_FALSE(Integer("15").equals(nullptr));
    EXPECT_FALSE(Integer("15").equals(std::string("testing value")));
    EXPECT_FALSE(Integer("15").equals(std::vector<Integer>({Integer(1), Integer(2), Integer(3)})));
    EXPECT_FALSE(Integer("15").equals(std::pair<Integer, Integer>({Integer(1), Integer(2)})));
}

TEST(IntegerTest, FloatValueFunction) {
    EXPECT_EQ(Integer(static_cast<int>(15)).floatValue(), 15.0f);
    EXPECT_EQ(Integer(static_cast<int>(-15)).floatValue(), -15.0f);
    EXPECT_EQ(Integer("15").floatValue(), 15.0f);
}

TEST(IntegerTest, GetIntegerFunctions) {
    /* -- getInteger(std::string) -- */
    EXPECT_EQ(Integer::getInteger("15"), Integer(15));
    EXPECT_EQ(Integer::getInteger("15"), Integer("15"));
    EXPECT_EQ(Integer::getInteger("0x0F"), Integer("15"));
    EXPECT_EQ(Integer::getInteger("#0F"), Integer("15"));

    /* -- getInteger(std::string, int32_t) -- */
    EXPECT_EQ(Integer::getInteger("15", 1), Integer(15));
    EXPECT_EQ(Integer::getInteger("15", 1), Integer("15"));
    EXPECT_EQ(Integer::getInteger("0x0F", 1), Integer("15"));
    EXPECT_EQ(Integer::getInteger("#0F", 1), Integer("15"));

    /* -- getInteger(std::string, Integer) -- */
    EXPECT_EQ(Integer::getInteger("15", Integer(1)), Integer(15));
    EXPECT_EQ(Integer::getInteger("15", Integer(1)), Integer("15"));
    EXPECT_EQ(Integer::getInteger("0x0F", Integer(1)), Integer("15"));
    EXPECT_EQ(Integer::getInteger("#0F", Integer(1)), Integer("15"));
}

TEST(IntegerTest, HashCodeFunctions) {
    /* -- hashCode() -- */
    EXPECT_EQ(Integer(15).hashCode(), 15);
    EXPECT_EQ(Integer("15").hashCode(), 15);

    /* -- static hashCode(int32_t) -- */
    EXPECT_EQ(Integer::hashCode(15), 15);
    EXPECT_EQ(Integer::hashCode(Integer(15).intValue()), 15);
    EXPECT_EQ(Integer::hashCode(Integer("15").intValue()), 15);
}

TEST(IntegerTest, HighestOneBitFunction) {
    EXPECT_EQ(Integer::highestOneBit(4), 4);
    EXPECT_EQ(Integer::highestOneBit(16), 16);
    EXPECT_EQ(Integer::highestOneBit(17), 16);
    EXPECT_EQ(Integer::highestOneBit(18), 16);
}

TEST(IntegerTest, IntValueFunction) {
    EXPECT_EQ(Integer(15).intValue(), 15);
    EXPECT_EQ(Integer("15").intValue(), 15);
}

TEST(IntegerTest, LongValueFunction) {
    EXPECT_EQ(Integer(15).longValue(), static_cast<long>(15));
    EXPECT_EQ(Integer("15").longValue(), static_cast<long>(15));
}

TEST(IntegerTest, LowestOneBitFunction) {
    EXPECT_EQ(Integer::lowestOneBit(15), 1);
    EXPECT_EQ(Integer::lowestOneBit(4), 4);
    EXPECT_EQ(Integer::lowestOneBit(Integer("15").intValue()), 1);
}

TEST(IntegerTest, MinMaxFunctions) {
    /* -- static max(int32_t, int32_t) -- */
    EXPECT_EQ(Integer::max(15, 16), 16);
    EXPECT_EQ(Integer::max(16, 16), 16);
    EXPECT_EQ(Integer::max(INT_MAX, INT_MAX / 2), INT_MAX);

    /* -- static min(int32_t, int32_t) -- */
    EXPECT_EQ(Integer::min(15, 16), 15);
    EXPECT_EQ(Integer::min(16, 16), 16);
    EXPECT_EQ(Integer::min(INT_MAX, INT_MAX / 2), (INT_MAX / 2));
}

TEST(IntegerTest, NumLeadingZeroesFunction) {
    EXPECT_EQ(Integer::numberOfLeadingZeroes(15), 28);
    EXPECT_EQ(Integer::numberOfLeadingZeroes(16), 27);
    EXPECT_EQ(Integer::numberOfLeadingZeroes(8), 28);
}

TEST(IntegerTest, NumTrailingZeroesFunction) {
    EXPECT_EQ(Integer::numberOfTrailingZeroes(15), 0);
    EXPECT_EQ(Integer::numberOfTrailingZeroes(16), 4);
    EXPECT_EQ(Integer::numberOfTrailingZeroes(8), 3);
}

TEST(IntegerTest, ParseIntFunctions) {
    /* -- static parseInt(const std::string&) -- */
    EXPECT_EQ(Integer::parseInt("15"), 15);
    EXPECT_EQ(Integer::parseInt("+15"), 15);
    EXPECT_EQ(Integer::parseInt("-15"), -15);
    EXPECT_EQ(Integer::parseInt(Integer(15).toString()), 15);

    /* -- static parseInt(const std::string&, int32_t) -- */
    EXPECT_EQ(Integer::parseInt("10101001", 2), 169);
    EXPECT_EQ(Integer::parseInt(Integer(15).toString(), 16), 21);

    /* -- static parseUnsignedInt(const std::string&) -- */
    EXPECT_EQ(Integer::parseUnsignedInt("15"), 15);
    EXPECT_EQ(Integer::parseUnsignedInt("+15"), 15);
    EXPECT_EQ(Integer::parseUnsignedInt("-15"), ((-15) % INT32_MAX));
    EXPECT_EQ(Integer::parseUnsignedInt(Integer(-15).toString()), ((-15) % INT32_MAX));

    /* -- static parseUnsignedInt(const std::string&, int32_t) -- */
    EXPECT_EQ(Integer::parseUnsignedInt("15", 16), 21);
    EXPECT_EQ(Integer::parseUnsignedInt("+15", 4), EXIT_FAILURE);
    EXPECT_EQ(Integer::parseUnsignedInt("-00001111", 2), ((-15) % INT32_MAX));
    EXPECT_EQ(Integer::parseUnsignedInt(Integer(-15).toString(), 36), ((-41) % INT32_MAX));
}

TEST(IntegerTest, RemainderUnsignedFunction) {
    EXPECT_EQ(Integer::remainderUnsigned(32, 2), 0);
    EXPECT_EQ(Integer::remainderUnsigned(15, 2), 1);
    EXPECT_EQ(Integer::remainderUnsigned(7, 2), 1);

    EXPECT_EQ(Integer::remainderUnsigned(-32, 2), 0);
    EXPECT_EQ(Integer::remainderUnsigned(-15, 2),
              1);  // C/C++ (and similar langs) truncate towards zero
    EXPECT_EQ(Integer::remainderUnsigned(7, 2),
              1);  // C/C++ (and similar langs) truncate towards zero
}

TEST(IntegerTest, ReverseFunction) {
    EXPECT_EQ(Integer::reverse(15),
              -268435456);  // since reverse() returns an int32_t, this returns a negative number
                            // due to two's complement and size restrictions on 32-bit ints
    EXPECT_EQ(Integer::reverse(-1), -1);  // since reverse() returns an int32_t, this returns a
                                          // negative number due to two's complement
}

TEST(IntegerTest, ReverseBytesFunction) {
    EXPECT_EQ(Integer::reverseBytes(15), 251658240);
    EXPECT_EQ(Integer::reverseBytes(32), 536870912);
    EXPECT_EQ(Integer::reverseBytes(-1), -1);  // managed by two's complement
}

TEST(IntegerTest, RotateFunctions) {
    /* -- rotateLeft(uint32_t, int32_t) -- */
    EXPECT_EQ(Integer::rotateLeft(15, 4), 240);
    EXPECT_EQ(Integer::rotateLeft(15, -4), -268435456);

    /* -- rotateRight(uint32_t, int32_t) -- */
    EXPECT_EQ(Integer::rotateRight(15, 4), -268435456);
    EXPECT_EQ(Integer::rotateRight(15, -4), 240);
}

TEST(IntegerTest, ShortValueFunction) {
    EXPECT_EQ(Integer(15).shortValue(), 15);
    EXPECT_EQ(Integer(-15).shortValue(), -15);
    EXPECT_EQ(Integer(SHRT_MAX + 1).shortValue(), -32768);
    EXPECT_EQ(Integer(SHRT_MIN - 1).shortValue(), 32767);
}

TEST(IntegerTest, SigNumFunction) {
    EXPECT_EQ(Integer::sigNum(15), 1);
    EXPECT_EQ(Integer::sigNum(-15), -1);
    EXPECT_EQ(Integer::sigNum(0), 0);
}

TEST(IntegerTest, ToBinStrFunction) {
    EXPECT_EQ(Integer::toBinaryString(15), "00000000000000000000000000001111");
    EXPECT_EQ(Integer::toBinaryString(-15), "11111111111111111111111111110001");
    EXPECT_EQ(Integer::toBinaryString(INT32_MAX), "01111111111111111111111111111111");
    EXPECT_EQ(Integer::toBinaryString(INT32_MIN), "10000000000000000000000000000000");
}

TEST(IntegerTest, ToHexStrFunction) {
    EXPECT_EQ(Integer::toHexString(15), "f");
    EXPECT_EQ(Integer::toHexString(-15), "fffffff1");
    EXPECT_EQ(Integer::toHexString(INT32_MAX), "7fffffff");
    EXPECT_EQ(Integer::toHexString(INT32_MIN), "80000000");
}

TEST(IntegerTest, ToOctStrFunction) {
    EXPECT_EQ(Integer::toOctalString(15), "17");
    EXPECT_EQ(Integer::toOctalString(-15), "37777777761");
    EXPECT_EQ(Integer::toOctalString(INT32_MAX), "17777777777");
    EXPECT_EQ(Integer::toOctalString(INT32_MIN), "20000000000");
}

TEST(IntegerTest, ToStrFunctions) {
    /* -- toString(this) -- */
    EXPECT_EQ(Integer(15).toString(), "15");
    EXPECT_EQ(Integer(-15).toString(), "-15");
    EXPECT_EQ(Integer(INT32_MAX).toString(), "2147483647");
    EXPECT_EQ(Integer(INT32_MIN).toString(), "-2147483648");

    /* -- toString(int32_t) -- */
    EXPECT_EQ(Integer::toString(15), "15");
    EXPECT_EQ(Integer::toString(-15), "-15");
    EXPECT_EQ(Integer::toString(INT32_MAX), "2147483647");
    EXPECT_EQ(Integer::toString(INT32_MIN), "-2147483648");

    /* -- toString(int32_t, int32_t) -- */
    EXPECT_EQ(Integer::toString(15, 10), "15");
    EXPECT_EQ(Integer::toString(15, 4), "33");
    EXPECT_EQ(Integer::toString(-15, 10), "-15");
    EXPECT_EQ(Integer::toString(-15, 4), "-33");
    EXPECT_EQ(Integer::toString(INT32_MAX, 10), "2147483647");
    EXPECT_EQ(Integer::toString(INT32_MAX, 4), "1333333333333333");
    EXPECT_EQ(Integer::toString(INT32_MIN, 10), "-2147483648");
    EXPECT_EQ(Integer::toString(INT32_MIN, 4), "-2000000000000000");
}

TEST(IntegerTest, ToULongFunction) {
    EXPECT_EQ(Integer::toUnsignedLong(15), 15);
    EXPECT_EQ(Integer::toUnsignedLong(-15), 18446744073709551601);
    EXPECT_EQ(Integer::toUnsignedLong(INT32_MAX), 2147483647);
    EXPECT_EQ(Integer::toUnsignedLong(INT32_MIN), 18446744071562067968);
    EXPECT_EQ(Integer::toUnsignedLong(ULONG_MAX + 1), 0);
    EXPECT_EQ(Integer::toUnsignedLong(LONG_MIN - 2), 18446744073709551614);
}

TEST(IntegerTest, ToUStrFunctions) {
    /* -- toUnsignedString(int32_t) -- */
    EXPECT_EQ(Integer::toUnsignedString(15), "15");
    EXPECT_EQ(Integer::toUnsignedString(-15), "18446744073709551601");
    EXPECT_EQ(Integer::toUnsignedString(INT32_MAX), "2147483647");
    EXPECT_EQ(Integer::toUnsignedString(INT32_MIN), "18446744071562067968");
    EXPECT_EQ(Integer::toUnsignedString(ULONG_MAX + 1), "0");
    EXPECT_EQ(Integer::toUnsignedString(LONG_MIN - 2), "18446744073709551614");

    /* -- toUnsignedString(int32_t, int32_t) -- */
    EXPECT_EQ(Integer::toUnsignedString(15, 10), "15");
    EXPECT_EQ(Integer::toUnsignedString(15, 4), "33");
    EXPECT_EQ(Integer::toUnsignedString(-15, 10), "18446744073709551601");
    EXPECT_EQ(Integer::toUnsignedString(-15, 4), "3333333333333301");
    EXPECT_EQ(Integer::toUnsignedString(INT32_MAX, 10), "2147483647");
    EXPECT_EQ(Integer::toUnsignedString(INT32_MAX, 4), "1333333333333333");
    EXPECT_EQ(Integer::toUnsignedString(INT32_MIN, 10), "18446744071562067968");
    EXPECT_EQ(Integer::toUnsignedString(INT32_MIN, 4), "2000000000000000");
    EXPECT_EQ(Integer::toUnsignedString(UINT64_MAX + 1, 4), "0");
    EXPECT_EQ(Integer::toUnsignedString(INT32_MIN - 2, 4), "1333333333333332");
}

TEST(IntegerTest, ValueOfFunctions) {
    /* -- valueOf(int32_t) -- */
    EXPECT_EQ(Integer::valueOf(15), Integer(15));
    EXPECT_EQ(Integer::valueOf(-15), Integer(-15));
    EXPECT_EQ(Integer::valueOf(4), Integer(4));
    EXPECT_EQ(Integer::valueOf(-4), Integer(-4));
    EXPECT_EQ(Integer::valueOf(INT32_MAX), Integer(INT32_MAX));
    EXPECT_EQ(Integer::valueOf(INT32_MIN), Integer(INT32_MIN));

    /* -- valueOf(const std::string&) -- */
    EXPECT_EQ(Integer::valueOf("15"), Integer(15));
    EXPECT_EQ(Integer::valueOf("-15"), Integer(-15));
    EXPECT_EQ(Integer::valueOf("4"), Integer(4));
    EXPECT_EQ(Integer::valueOf("-4"), Integer(-4));
    EXPECT_EQ(Integer::valueOf("2147483647"), Integer(INT32_MAX));
    EXPECT_EQ(Integer::valueOf("-2147483648"), Integer(INT32_MIN));

    /* -- valueOf(const std::string&, int32_t) -- */
    EXPECT_EQ(Integer::valueOf("15", 16), Integer(21));
    EXPECT_EQ(Integer::valueOf("33", 4), Integer(15));
    EXPECT_EQ(Integer::valueOf("-33", 4), Integer(-15));
}

TEST(IntegerTest, BoolOverloads) {
    class FakeClass {
       private:
        std::string notAnInt;
        int32_t thisIsAnInt;

       public:
        FakeClass(std::string x, int32_t y) : notAnInt(x), thisIsAnInt{y} {}
        std::string getPrivStr() { return this->notAnInt; }
        int32_t getPrivInt() { return this->thisIsAnInt; }
    };

    /* -- operator==(std::any&) -- */
    EXPECT_TRUE(Integer(15) == Integer(15));
    EXPECT_TRUE(Integer("15") == Integer(15));
    EXPECT_TRUE(Integer("15") == Integer("15"));
    EXPECT_TRUE(Integer(15) == Integer("15"));
    EXPECT_TRUE(Integer(15) == Integer(FakeClass("15", 15).getPrivInt()));

    EXPECT_FALSE(Integer(15) == FakeClass("15", 0).getPrivStr());
    EXPECT_FALSE(Integer("15") == FakeClass("15", 0).getPrivStr());

    /* -- operator!=(std::any&) -- */
    EXPECT_FALSE(Integer(15) != Integer(15));
    EXPECT_FALSE(Integer("15") != Integer(15));
    EXPECT_FALSE(Integer("15") != Integer("15"));
    EXPECT_FALSE(Integer(15) != Integer("15"));
    EXPECT_FALSE(Integer(15) != Integer(FakeClass("15", 15).getPrivInt()));

    EXPECT_TRUE(Integer(15) != FakeClass("15", 0).getPrivStr());
    EXPECT_TRUE(Integer("15") != FakeClass("15", 0).getPrivStr());
}

TEST(IntegerTest, StreamOverload) {
    /* -- operator<<(std::ostream&. Integer&) -- */
    std::stringstream out;    
    out << Integer(15);
    EXPECT_EQ(out.str(), "15");

    out.str("");
    out << Integer("15");
    EXPECT_EQ(out.str(), "15");

    out.str("");
    out << Integer(Integer(15));
    EXPECT_EQ(out.str(), "15");
    
    out.str("");
    out << Integer(Integer("15"));
    EXPECT_EQ(out.str(), "15");
}

TEST(IntegerTest, UpperCaseHelper) {
    std::string test_str = "this is a test string";
    Integer::toUpperCase(test_str);
    EXPECT_EQ(test_str, "THIS IS A TEST STRING");

    test_str = "THIS IS A TEST STRING";
    Integer::toUpperCase(test_str);
    EXPECT_EQ(test_str, "THIS IS A TEST STRING");

    test_str = "15";
    Integer::toUpperCase(test_str);
    EXPECT_EQ(test_str, "15");
}