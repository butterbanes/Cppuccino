#include "../../include/Cppuccino/Float.h"

#include <gtest/gtest.h>
#include <cmath>
#include <limits>
#include <sstream>

TEST(FloatTest, CheckPublicConstValues) {
    EXPECT_EQ(Float::SIZE, 32) << "Should be '32'";
    EXPECT_EQ(Float::BYTES, 4) << "Should be '4'";
    EXPECT_EQ(Float::PRECISION, 24) << "Should be '24'";
    EXPECT_EQ(Float::MAX_EXPONENT, std::numeric_limits<float>::max_exponent);
    EXPECT_EQ(Float::MIN_EXPONENT, std::numeric_limits<float>::min_exponent);
    EXPECT_FLOAT_EQ(Float::MAX_VALUE, std::numeric_limits<float>::max());
    EXPECT_FLOAT_EQ(Float::MIN_VALUE, std::numeric_limits<float>::denorm_min());
    EXPECT_FLOAT_EQ(Float::MIN_NORMAL, std::numeric_limits<float>::min());
    EXPECT_TRUE(std::isnan(Float::NaN));
    EXPECT_FLOAT_EQ(Float::NEGATIVE_INFINITY, -std::numeric_limits<float>::infinity());
    EXPECT_FLOAT_EQ(Float::POSITIVE_INFINITY, std::numeric_limits<float>::infinity());
}

TEST(FloatTest, CheckTypeReturnedByConstructors) {
    EXPECT_EQ(typeid(Float(15.5)), typeid(Float)) << "Should be 'Float'";
    EXPECT_EQ(typeid(Float(15.5f)), typeid(Float)) << "Should be 'Float'";
    EXPECT_EQ(typeid(Float("15.5")), typeid(Float)) << "Should be 'Float'";
}

TEST(FloatTest, ByteValueFunction) {
    EXPECT_EQ(Float(15.5f).byteValue(), static_cast<int8_t>(15));
    EXPECT_EQ(Float(-16.5f).byteValue(), static_cast<int8_t>(-16));
    EXPECT_EQ(Float(0.0f).byteValue(), static_cast<int8_t>(0));
}

TEST(FloatTest, CompareFunction) {
    EXPECT_LT(Float::compare(1.5f, 2.5f), 0);
    EXPECT_EQ(Float::compare(2.5f, 2.5f), 0);
    EXPECT_GT(Float::compare(2.5f, 1.5f), 0);
    EXPECT_GT(Float::compare(Float::POSITIVE_INFINITY, 1.5f), 0);
    EXPECT_LT(Float::compare(Float::NEGATIVE_INFINITY, 1.5f), 0);
}

TEST(FloatTest, CompareToFunction) {
    EXPECT_LT(Float(1.5f).compareTo(Float(2.5f)), 0);
    EXPECT_EQ(Float(2.5f).compareTo(Float(2.5f)), 0);
    EXPECT_GT(Float(2.5f).compareTo(Float(1.5f)), 0);
}

TEST(FloatTest, DoubleValueFunction) {
    EXPECT_DOUBLE_EQ(Float(15.5f).doubleValue(), 15.5);
    EXPECT_DOUBLE_EQ(Float(-15.5f).doubleValue(), -15.5);
    EXPECT_DOUBLE_EQ(Float("15.5").doubleValue(), 15.5);
}

TEST(FloatTest, EqualsFunction) {
    EXPECT_TRUE(Float(15.5f).equals(Float(15.5f)));
    EXPECT_TRUE(Float(15.5f).equals(Float("15.5")));
    EXPECT_TRUE(Float("15.5").equals(Float(15.5f)));
    EXPECT_TRUE(Float("15.5").equals(Float("15.5")));

    EXPECT_FALSE(Float(15.5f).equals(Float(16.5f)));
    EXPECT_FALSE(Float(15.5f).equals(Float("16.5")));
    EXPECT_FALSE(Float("15.5").equals(Float(16.5f)));
    EXPECT_FALSE(Float("15.5").equals(Float("16.5")));

    EXPECT_FALSE(Float("15.5").equals(std::any()));
    EXPECT_FALSE(Float("15.5").equals(std::string("testing value")));
}

TEST(FloatTest, FloatToIntBitsFunctions) {
    EXPECT_EQ(Float::floatToIntBits(1.0f), 1065353216);
    EXPECT_EQ(Float::floatToIntBits(Float::POSITIVE_INFINITY), 0x7f800000);
}

TEST(FloatTest, FloatValueFunction) {
    EXPECT_FLOAT_EQ(Float(15.5f).floatValue(), 15.5f);
    EXPECT_FLOAT_EQ(Float(-15.5f).floatValue(), -15.5f);
    EXPECT_FLOAT_EQ(Float("15.5").floatValue(), 15.5f);
}

TEST(FloatTest, IntValueFunction) {
    EXPECT_EQ(Float(15.9f).intValue(), 15);
    EXPECT_EQ(Float("-15.9").intValue(), -15);
}

TEST(FloatTest, IsFiniteFunctions) {
    /* -- static isFinite(float) -- */
    EXPECT_TRUE(Float::isFinite(15.5f));
    EXPECT_TRUE(Float::isFinite(0.0f));
    EXPECT_TRUE(Float::isFinite(-15.5f));
    EXPECT_FALSE(Float::isFinite(Float::POSITIVE_INFINITY));
    EXPECT_FALSE(Float::isFinite(Float::NEGATIVE_INFINITY));
    EXPECT_FALSE(Float::isFinite(Float::NaN));
}

TEST(FloatTest, IsInfiniteFunctions) {
    /* -- isInfinite() -- */
    EXPECT_FALSE(Float(15.5f).isInfinite());
    EXPECT_TRUE(Float(Float::POSITIVE_INFINITY).isInfinite());
    EXPECT_TRUE(Float(Float::NEGATIVE_INFINITY).isInfinite());

    /* -- static isInfinite(float) -- */
    EXPECT_FALSE(Float::isInfinite(15.5f));
    EXPECT_TRUE(Float::isInfinite(Float::POSITIVE_INFINITY));
    EXPECT_TRUE(Float::isInfinite(Float::NEGATIVE_INFINITY));
}

TEST(FloatTest, IsNaNFunctions) {
    /* -- isNaN() -- */
    EXPECT_FALSE(Float(15.5f).isNaN());
    EXPECT_TRUE(Float(Float::NaN).isNaN());

    /* -- static isNaN(float) -- */
    EXPECT_FALSE(Float::isNaN(15.5f));
    EXPECT_TRUE(Float::isNaN(Float::NaN));
}

TEST(FloatTest, LongValueFunction) {
    EXPECT_EQ(Float(15.9f).longValue(), static_cast<int64_t>(15));
    EXPECT_EQ(Float("-15.9").longValue(), static_cast<int64_t>(-15));
}

TEST(FloatTest, MinMaxFunctions) {
    /* -- static max(float, float) -- */
    EXPECT_FLOAT_EQ(Float::max(15.5f, 16.5f), 16.5f);
    EXPECT_FLOAT_EQ(Float::max(16.5f, 16.5f), 16.5f);
    EXPECT_FLOAT_EQ(Float::max(-1.5f, -2.5f), -1.5f);

    /* -- static min(float, float) -- */
    EXPECT_FLOAT_EQ(Float::min(15.5f, 16.5f), 15.5f);
    EXPECT_FLOAT_EQ(Float::min(16.5f, 16.5f), 16.5f);
    EXPECT_FLOAT_EQ(Float::min(-1.5f, -2.5f), -2.5f);
}

TEST(FloatTest, ParseFloatFunction) {
    EXPECT_FLOAT_EQ(Float::parseFloat("15.5"), 15.5f);
    EXPECT_FLOAT_EQ(Float::parseFloat("-15.5"), -15.5f);
    EXPECT_FLOAT_EQ(Float::parseFloat("0.0f"), 0.0f);
    EXPECT_FLOAT_EQ(Float::parseFloat("-0.0f"), -0.0f);
    EXPECT_FLOAT_EQ(Float::parseFloat("Infinity"), Float::POSITIVE_INFINITY);
    EXPECT_FLOAT_EQ(Float::parseFloat("-Infinity"), Float::NEGATIVE_INFINITY);
    EXPECT_TRUE(Float::isNaN(Float::parseFloat("NaN")));
}

TEST(FloatTest, ShortValueFunction) {
    EXPECT_EQ(Float(15.9f).shortValue(), static_cast<int16_t>(15));
    EXPECT_EQ(Float(-15.9f).shortValue(), static_cast<int16_t>(-15));
}

TEST(FloatTest, SumFunction) {
    EXPECT_FLOAT_EQ(Float::sum(15.5f, 4.5f), 20.0f);
    EXPECT_FLOAT_EQ(Float::sum(-15.5f, 15.5f), 0.0f);
}

TEST(FloatTest, ToHexStringFunction) {
    EXPECT_EQ(Float::toHexString(1.0f), "0x1p0");
    EXPECT_EQ(Float::toHexString(-1.0f), "-0x1p0");
    EXPECT_EQ(Float::toHexString(0.0f), "0x0.0p0f");
    EXPECT_EQ(Float::toHexString(-0.0f), "-0x0.0p0f");
    EXPECT_EQ(Float::toHexString(Float::NaN), "NaN");
    EXPECT_EQ(Float::toHexString(Float::POSITIVE_INFINITY), "Infinity");
    EXPECT_EQ(Float::toHexString(Float::NEGATIVE_INFINITY), "-Infinity");
}

TEST(FloatTest, ToStrFunctions) {
    /* -- toString() -- */
    EXPECT_EQ(Float(15.5f).toString(), std::to_string(15.5f));
    EXPECT_EQ(Float(-15.5f).toString(), std::to_string(-15.5f));
    EXPECT_EQ(Float(0.0f).toString(), "0.0f");
    EXPECT_EQ(Float(-0.0f).toString(), "-0.0f");
    EXPECT_EQ(Float(Float::POSITIVE_INFINITY).toString(), "Infinity");
    EXPECT_EQ(Float(Float::NEGATIVE_INFINITY).toString(), "-Infinity");
    EXPECT_EQ(Float(Float::NaN).toString(), "NaN");

    /* -- static toString(float) -- */
    EXPECT_EQ(Float::toString(15.5f), std::to_string(15.5f));
    EXPECT_EQ(Float::toString(-15.5f), std::to_string(-15.5f));
    EXPECT_EQ(Float::toString(0.0f), "0.0f");
    EXPECT_EQ(Float::toString(-0.0f), "-0.0f");
    EXPECT_EQ(Float::toString(Float::POSITIVE_INFINITY), "Infinity");
    EXPECT_EQ(Float::toString(Float::NEGATIVE_INFINITY), "-Infinity");
    EXPECT_EQ(Float::toString(Float::NaN), "NaN");
}

TEST(FloatTest, ValueOfFunctions) {
    /* -- static valueOf(float) -- */
    EXPECT_FLOAT_EQ(Float::valueOf(15.5f).floatValue(), 15.5f);
    EXPECT_FLOAT_EQ(Float::valueOf(-15.5f).floatValue(), -15.5f);

    /* -- static valueOf(const std::string&) -- */
    EXPECT_FLOAT_EQ(Float::valueOf("15.5").floatValue(), 15.5f);
    EXPECT_FLOAT_EQ(Float::valueOf("-15.5").floatValue(), -15.5f);
    EXPECT_FLOAT_EQ(Float::valueOf("Infinity").floatValue(), Float::POSITIVE_INFINITY);
    EXPECT_FLOAT_EQ(Float::valueOf("-Infinity").floatValue(), Float::NEGATIVE_INFINITY);
    EXPECT_TRUE(Float::valueOf("NaN").isNaN());
}

TEST(FloatTest, CompareOperatorOverloads) {
    /* -- operator==(const Float&) -- */
    EXPECT_TRUE(Float(15.5f) == Float(15.5f));
    EXPECT_FALSE(Float(15.5f) == Float(16.5f));

    /* -- operator<=>(const Float&) -- */
    EXPECT_TRUE(Float(15.5f) <= Float(15.5f));
    EXPECT_TRUE(Float(15.5f) >= Float(15.5f));
    EXPECT_TRUE(Float(15.5f) < Float(16.5f));
    EXPECT_TRUE(Float(16.5f) > Float(15.5f));
    EXPECT_FALSE(Float(15.5f) > Float(16.5f));
    EXPECT_FALSE(Float(16.5f) < Float(15.5f));
}

TEST(FloatTest, StreamOverload) {
    /* -- operator<<(std::ostream&, const Float&) -- */
    std::stringstream out;
    out << Float(0.0f);
    EXPECT_EQ(out.str(), "0.0f");

    out.str("");
    out << Float(-0.0f);
    EXPECT_EQ(out.str(), "-0.0f");

    out.str("");
    out << Float(Float::POSITIVE_INFINITY);
    EXPECT_EQ(out.str(), "Infinity");

    out.str("");
    out << Float(15.5f);
    EXPECT_EQ(out.str(), std::to_string(15.5f));
}