#include "../../include/Cppuccino/Double.h"

#include <gtest/gtest.h>
#include <cmath>
#include <limits>
#include <sstream>

TEST(DoubleTest, CheckPublicConstValues) {
    EXPECT_EQ(Double::SIZE, 64) << "Should be '64'";
    EXPECT_EQ(Double::BYTES, 8) << "Should be '8'";
    EXPECT_EQ(Double::PRECISION, 53) << "Should be '53'";
    EXPECT_EQ(Double::MAX_EXPONENT, std::numeric_limits<double>::max_exponent);
    EXPECT_EQ(Double::MIN_EXPONENT, std::numeric_limits<double>::min_exponent);
    EXPECT_EQ(Double::MAX_VALUE, std::numeric_limits<double>::max());
    EXPECT_EQ(Double::MIN_VALUE, std::numeric_limits<double>::denorm_min());
    EXPECT_EQ(Double::MIN_NORMAL, std::numeric_limits<double>::min());
    EXPECT_TRUE(std::isnan(Double::NaN));
    EXPECT_EQ(Double::NEGATIVE_INFINITY, -std::numeric_limits<double>::infinity());
    EXPECT_EQ(Double::POSITIVE_INFINITY, std::numeric_limits<double>::infinity());
}

TEST(DoubleTest, CheckTypeReturnedByConstructors) {
    EXPECT_EQ(typeid(Double(15.5)), typeid(Double)) << "Should be 'Double'";
    EXPECT_EQ(typeid(Double("15.5")), typeid(Double)) << "Should be 'Double'";
}

TEST(DoubleTest, CreateFunction) {
    EXPECT_EQ(typeid(Double::create(15.0)).name(), typeid(std::unique_ptr<Double>).name());
    EXPECT_NE(Double::create(15.0), nullptr);
}

TEST(DoubleTest, ByteValueFunction) {
    EXPECT_EQ(Double(15.9).byteValue(), static_cast<int8_t>(15));
    EXPECT_EQ(Double(-16.2).byteValue(), static_cast<int8_t>(-16));
    EXPECT_EQ(Double(0.0).byteValue(), static_cast<int8_t>(0));
}

TEST(DoubleTest, CompareFunction) {
    EXPECT_LT(Double::compare(1.5, 2.5), 0);
    EXPECT_EQ(Double::compare(2.5, 2.5), 0);
    EXPECT_GT(Double::compare(2.5, 1.5), 0);
    EXPECT_GT(Double::compare(Double::POSITIVE_INFINITY, 1.5), 0);
    EXPECT_LT(Double::compare(Double::NEGATIVE_INFINITY, 1.5), 0);
}

TEST(DoubleTest, CompareToFunction) {
    EXPECT_LT(Double(1.5).compareTo(Double(2.5)), 0);
    EXPECT_EQ(Double(2.5).compareTo(Double(2.5)), 0);
    EXPECT_GT(Double(2.5).compareTo(Double(1.5)), 0);
}

TEST(DoubleTest, DoubleToLongBitsFunctions) {
    /* -- static doubleToLongBits(double) -- */
    EXPECT_EQ(Double::doubleToLongBits(1.0), 4607182418800017408LL);
    EXPECT_EQ(Double::doubleToLongBits(Double::POSITIVE_INFINITY), 0x7ff0000000000000LL);
    EXPECT_EQ(Double::doubleToLongBits(Double::NEGATIVE_INFINITY), -4503599627370496LL); // 0xfff0000000000000LL

    /* -- static doubleToRawLongBits(double) -- */
    EXPECT_EQ(Double::doubleToRawLongBits(1.0), 4607182418800017408LL);
    EXPECT_EQ(Double::doubleToRawLongBits(Double::POSITIVE_INFINITY), 0x7ff0000000000000LL);
}

TEST(DoubleTest, DoubleValueFunction) {
    EXPECT_EQ(Double(15.5).doubleValue(), 15.5);
    EXPECT_EQ(Double(-15.5).doubleValue(), -15.5);
    EXPECT_EQ(Double("15.5").doubleValue(), 15.5);
}

TEST(DoubleTest, EqualsFunction) {
    EXPECT_TRUE(Double(15.5).equals(Double(15.5)));
    EXPECT_TRUE(Double(15.5).equals(Double("15.5")));
    EXPECT_TRUE(Double("15.5").equals(Double(15.5)));
    EXPECT_TRUE(Double("15.5").equals(Double("15.5")));

    EXPECT_FALSE(Double(15.5).equals(Double(16.5)));
    EXPECT_FALSE(Double(15.5).equals(Double("16.5")));
    EXPECT_FALSE(Double("15.5").equals(Double(16.5)));
    EXPECT_FALSE(Double("15.5").equals(Double("16.5")));

    EXPECT_FALSE(Double("15.5").equals(std::any())); // empty any
    EXPECT_FALSE(Double("15.5").equals(std::string("testing value")));
    EXPECT_FALSE(Double("15.5").equals(std::vector<Double>({Double(1.0), Double(2.0)})));
}

TEST(DoubleTest, FloatValueFunction) {
    EXPECT_EQ(Double(15.5).floatValue(), 15.5f);
    EXPECT_EQ(Double(-15.5).floatValue(), -15.5f);
    EXPECT_EQ(Double("15.5").floatValue(), 15.5f);
}

TEST(DoubleTest, HashCodeFunctions) {
    /* -- hashCode() -- */
    EXPECT_EQ(Double(15.5).hashCode(), Double::hashCode(15.5));
    EXPECT_EQ(Double("15.5").hashCode(), Double::hashCode(15.5));

    /* -- static hashCode(double) -- */
    int64_t bits = Double::doubleToRawLongBits(15.5);
    int32_t expectedHash = static_cast<int32_t>(bits ^ (static_cast<uint64_t>(bits) >> 32));
    EXPECT_EQ(Double::hashCode(15.5), expectedHash);
}

TEST(DoubleTest, IntValueFunction) {
    EXPECT_EQ(Double(15.9).intValue(), 15);
    EXPECT_EQ(Double("-15.9").intValue(), -15);
}

TEST(DoubleTest, IsFiniteFunctions) {
    /* -- static isFinite(double) -- */
    EXPECT_TRUE(Double::isFinite(15.5));
    EXPECT_TRUE(Double::isFinite(0.0));
    EXPECT_TRUE(Double::isFinite(-15.5));
    EXPECT_FALSE(Double::isFinite(Double::POSITIVE_INFINITY));
    EXPECT_FALSE(Double::isFinite(Double::NEGATIVE_INFINITY));
    EXPECT_FALSE(Double::isFinite(Double::NaN));
}

TEST(DoubleTest, IsInfiniteFunctions) {
    /* -- isInfinite() -- */
    EXPECT_FALSE(Double(15.5).isInfinite());
    EXPECT_TRUE(Double(Double::POSITIVE_INFINITY).isInfinite());
    EXPECT_TRUE(Double(Double::NEGATIVE_INFINITY).isInfinite());

    /* -- static isInfinite(double) -- */
    EXPECT_FALSE(Double::isInfinite(15.5));
    EXPECT_TRUE(Double::isInfinite(Double::POSITIVE_INFINITY));
    EXPECT_TRUE(Double::isInfinite(Double::NEGATIVE_INFINITY));
}

TEST(DoubleTest, IsNaNFunctions) {
    /* -- isNaN() -- */
    EXPECT_FALSE(Double(15.5).isNaN());
    EXPECT_TRUE(Double(Double::NaN).isNaN());

    /* -- static isNaN(double) -- */
    EXPECT_FALSE(Double::isNaN(15.5));
    EXPECT_TRUE(Double::isNaN(Double::NaN));
}

TEST(DoubleTest, LongBitsToDoubleFunction) {
    EXPECT_EQ(Double::longBitsToDouble(4607182418800017408LL), 1.0);
    EXPECT_EQ(Double::longBitsToDouble(0x7ff0000000000000LL), Double::POSITIVE_INFINITY);
    EXPECT_TRUE(Double::isNaN(Double::longBitsToDouble(Double::doubleToRawLongBits(Double::NaN))));
}

TEST(DoubleTest, LongValueFunction) {
    EXPECT_EQ(Double(15.9).longValue(), static_cast<int64_t>(15));
    EXPECT_EQ(Double("-15.9").longValue(), static_cast<int64_t>(-15));
}

TEST(DoubleTest, MinMaxFunctions) {
    /* -- static max(double, double) -- */
    EXPECT_EQ(Double::max(15.5, 16.5), 16.5);
    EXPECT_EQ(Double::max(16.5, 16.5), 16.5);
    EXPECT_EQ(Double::max(-1.5, -2.5), -1.5);

    /* -- static min(double, double) -- */
    EXPECT_EQ(Double::min(15.5, 16.5), 15.5);
    EXPECT_EQ(Double::min(16.5, 16.5), 16.5);
    EXPECT_EQ(Double::min(-1.5, -2.5), -2.5);
}

TEST(DoubleTest, ParseDoubleFunction) {
    EXPECT_EQ(Double::parseDouble("15.5"), 15.5);
    EXPECT_EQ(Double::parseDouble("-15.5"), -15.5);
    EXPECT_EQ(Double::parseDouble("0.0"), 0.0);
    EXPECT_EQ(Double::parseDouble("-0.0"), -0.0);
    EXPECT_EQ(Double::parseDouble("Infinity"), Double::POSITIVE_INFINITY);
    EXPECT_EQ(Double::parseDouble("-Infinity"), Double::NEGATIVE_INFINITY);
    EXPECT_TRUE(Double::isNaN(Double::parseDouble("NaN")));
}

TEST(DoubleTest, ShortValueFunction) {
    EXPECT_EQ(Double(15.9).shortValue(), static_cast<int16_t>(15));
    EXPECT_EQ(Double(-15.9).shortValue(), static_cast<int16_t>(-15));
}

TEST(DoubleTest, SumFunction) {
    EXPECT_EQ(Double::sum(15.5, 4.5), 20.0);
    EXPECT_EQ(Double::sum(-15.5, 15.5), 0.0);
}

TEST(DoubleTest, ToHexStringFunction) {
    EXPECT_EQ(Double::toHexString(1.0), "0x1p0");
    EXPECT_EQ(Double::toHexString(-1.0), "-0x1p0");
    EXPECT_EQ(Double::toHexString(0.0), "0x0.0p0");
    EXPECT_EQ(Double::toHexString(-0.0), "-0x0.0p0");
    EXPECT_EQ(Double::toHexString(Double::NaN), "NaN");
    EXPECT_EQ(Double::toHexString(Double::POSITIVE_INFINITY), "Infinity");
    EXPECT_EQ(Double::toHexString(Double::NEGATIVE_INFINITY), "-Infinity");
}

TEST(DoubleTest, ToStrFunctions) {
    /* -- toString() -- */
    EXPECT_EQ(Double(15.5).toString(), std::to_string(15.5));
    EXPECT_EQ(Double(-15.5).toString(), std::to_string(-15.5));
    EXPECT_EQ(Double(0.0).toString(), "0.0");
    EXPECT_EQ(Double(-0.0).toString(), "-0.0");
    EXPECT_EQ(Double(Double::POSITIVE_INFINITY).toString(), "Infinity");
    EXPECT_EQ(Double(Double::NEGATIVE_INFINITY).toString(), "-Infinity");
    EXPECT_EQ(Double(Double::NaN).toString(), "NaN");

    /* -- static toString(double) -- */
    EXPECT_EQ(Double::toString(15.5), std::to_string(15.5));
    EXPECT_EQ(Double::toString(-15.5), std::to_string(-15.5));
    EXPECT_EQ(Double::toString(0.0), "0.0");
    EXPECT_EQ(Double::toString(-0.0), "-0.0");
    EXPECT_EQ(Double::toString(Double::POSITIVE_INFINITY), "Infinity");
    EXPECT_EQ(Double::toString(Double::NEGATIVE_INFINITY), "-Infinity");
    EXPECT_EQ(Double::toString(Double::NaN), "NaN");
}

TEST(DoubleTest, ValueOfFunctions) {
    /* -- static valueOf(double) -- */
    EXPECT_EQ(Double::valueOf(15.5).doubleValue(), 15.5);
    EXPECT_EQ(Double::valueOf(-15.5).doubleValue(), -15.5);

    /* -- static valueOf(const std::string&) -- */
    EXPECT_EQ(Double::valueOf("15.5").doubleValue(), 15.5);
    EXPECT_EQ(Double::valueOf("-15.5").doubleValue(), -15.5);
    EXPECT_EQ(Double::valueOf("Infinity").doubleValue(), Double::POSITIVE_INFINITY);
    EXPECT_EQ(Double::valueOf("-Infinity").doubleValue(), Double::NEGATIVE_INFINITY);
    EXPECT_TRUE(Double::valueOf("NaN").isNaN());
}

TEST(DoubleTest, CompareOperatorOverloads) {
    EXPECT_TRUE(Double(15.5) == Double(15.5));
    EXPECT_TRUE(Double(15.5) <= Double(15.5));
    EXPECT_TRUE(Double(15.5) >= Double(15.5));
    EXPECT_FALSE(Double(15.5) != Double(15.5));

    EXPECT_TRUE(Double(15.5) < Double(16.5));
    EXPECT_TRUE(Double(16.5) > Double(15.5));
    EXPECT_TRUE(Double(15.5) != Double(16.5));
}

TEST(DoubleTest, StreamOverload) {
    /* -- operator<<(std::ostream&, const Double&) -- */
    std::stringstream out;
    out << Double(0.0);
    EXPECT_EQ(out.str(), "0.0");

    out.str("");
    out << Double(-0.0);
    EXPECT_EQ(out.str(), "-0.0");

    out.str("");
    out << Double(Double::POSITIVE_INFINITY);
    EXPECT_EQ(out.str(), "Infinity");

    out.str("");
    out << Double(15.5);
    EXPECT_EQ(out.str(), std::to_string(15.5));
}