#include "../../include/Cppuccino/Byte.h"

#include <gtest/gtest.h>

TEST(ByteTest, CheckBytePublicConstValues) {
    EXPECT_EQ(Byte::SIZE, 8);
    EXPECT_EQ(Byte::BYTES, 1);
    EXPECT_EQ(Byte::MAX_VALUE, 127);
    EXPECT_EQ(Byte::MIN_VALUE, -128);
}

TEST(ByteTest, CheckTypeReturnedByConstructors) {
    EXPECT_EQ(typeid(Byte{15}), typeid(Byte));
    EXPECT_EQ(typeid(Byte{-15}), typeid(Byte));
    
    EXPECT_EQ(typeid(Byte{127}), typeid(Byte));
    EXPECT_EQ(typeid(Byte{-128}), typeid(Byte));

    EXPECT_EQ(typeid(Byte{std::string{"127"}}), typeid(Byte));
    EXPECT_EQ(typeid(Byte{std::string{"-128"}}), typeid(Byte));
    
    EXPECT_EQ(typeid(Byte{"127"}), typeid(Byte));
    EXPECT_EQ(typeid(Byte{"-128"}), typeid(Byte));
}

TEST(ByteTest, CreateFunction) {
    EXPECT_EQ(typeid(Byte::create(15)).name(), typeid(std::unique_ptr<Byte>).name());
    EXPECT_EQ(typeid(Byte::create(-15)).name(), typeid(std::unique_ptr<Byte>).name());
}

TEST(ByteTest, ConstructorValues) {
    EXPECT_EQ(Byte{static_cast<int8_t>(15)}.byteValue(), 15);
    EXPECT_EQ(Byte{std::string{"127"}}.byteValue(), 127);
    EXPECT_EQ(Byte{"-128"}.byteValue(), -128);
}

TEST(ByteTest, CompareFunctions) {
    EXPECT_LT(Byte::compare(10, 20), 0);
    EXPECT_EQ(Byte::compare(10, 10), 0);
    EXPECT_GT(Byte::compare(20, 10), 0);

    EXPECT_LT(Byte{10}.compareTo(Byte{20}), 0);
    EXPECT_EQ(Byte{10}.compareTo(Byte{10}), 0);
    EXPECT_GT(Byte{20}.compareTo(Byte{10}), 0);

    EXPECT_LT(Byte::compareUnsigned(10, 20), 0);
    EXPECT_EQ(Byte::compareUnsigned(10, 10), 0);
    EXPECT_GT(Byte::compareUnsigned(-1, 10), 0);
}

TEST(ByteTest, DecodeFunction) {
    EXPECT_EQ(Byte::decode("127").byteValue(), 127);
    EXPECT_EQ(Byte::decode("-128").byteValue(), -128);
    EXPECT_EQ(Byte::decode("0x7F").byteValue(), 127);
    EXPECT_EQ(Byte::decode("-0x80").byteValue(), -128);
    EXPECT_EQ(Byte::decode("010").byteValue(), 8);
}

TEST(ByteTest, NumericValueConversions) {
    Byte b{42};
    EXPECT_EQ(b.doubleValue(), 42.0);
    EXPECT_EQ(b.floatValue(), 42.0f);
    EXPECT_EQ(b.intValue(), 42);
    EXPECT_EQ(b.longValue(), 42LL);
    EXPECT_EQ(b.shortValue(), 42);
}

TEST(ByteTest, EqualsFunction) {
    Byte b{42};
    EXPECT_TRUE(b.equals(std::make_any<Byte>(Byte{42})));
    EXPECT_FALSE(b.equals(std::make_any<Byte>(Byte{43})));
    EXPECT_FALSE(b.equals(std::make_any<int>(42)));
}

TEST(ByteTest, HashCodeFunctions) {
    Byte b{42};
    EXPECT_EQ(b.hashCode(), 42);
    EXPECT_EQ(Byte::hashCode(42), 42);
    EXPECT_EQ(Byte{-1}.hashCode(), -1);
}

TEST(ByteTest, ParseByteFunctions) {
    EXPECT_EQ(Byte::parseByte("127"), 127);
    EXPECT_EQ(Byte::parseByte("-128"), -128);
    EXPECT_EQ(Byte::parseByte("7F", 16), 127);
    EXPECT_EQ(Byte::parseByte("-80", 16), -128);
    EXPECT_EQ(Byte::parseByte("1111111", 2), 127);
}

TEST(ByteTest, ToStringFunctions) {
    EXPECT_EQ(Byte{127}.toString(), "127");
    EXPECT_EQ(Byte{-128}.toString(), "-128");
    EXPECT_EQ(Byte::toString(127), "127");
    EXPECT_EQ(Byte::toString(-128), "-128");
}

TEST(ByteTest, UnsignedConversions) {
    EXPECT_EQ(Byte::toUnsignedInt(-1), 255);
    EXPECT_EQ(Byte::toUnsignedLong(-1), 255);
    EXPECT_EQ(Byte::toUnsignedInt(127), 127);
    EXPECT_EQ(Byte::toUnsignedLong(127), 127);
}

TEST(ByteTest, ValueOfFunctions) {
    EXPECT_EQ(Byte::valueOf(static_cast<int8_t>(42)).byteValue(), 42);
    EXPECT_EQ(Byte::valueOf("42").byteValue(), 42);
    EXPECT_EQ(Byte::valueOf("2A", 16).byteValue(), 42);
}

TEST(ByteTest, RelationalOperators) {
    Byte a{10};
    Byte b{20};
    Byte c{10};
    
    EXPECT_TRUE(a == c);
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a < b);
    EXPECT_TRUE(a <= c);
    EXPECT_TRUE(b > a);
    EXPECT_TRUE(b >= a);
    EXPECT_TRUE(a != b);
}

TEST(ByteTest, StreamOverload) {
    std::stringstream out;
    out << Byte(15);
    EXPECT_EQ(out.str(), "15");

    out.str("");
    out << Byte("15");
    EXPECT_EQ(out.str(), "15");

    out.str("");
    out << Byte(127);
    EXPECT_EQ(out.str(), "127");

    out.str("");
    out << Byte("127");
    EXPECT_EQ(out.str(), "127");

    out.str("");
    out << Byte(-128);
    EXPECT_EQ(out.str(), "-128");
    
    out.str("");
    out << Byte("-128");
    EXPECT_EQ(out.str(), "-128");
}