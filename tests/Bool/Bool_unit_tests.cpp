#include "../../include/Cppuccino/Bool.h"

#include <gtest/gtest.h>

TEST(BoolTest, CheckBoolPublicConstValues) {
    EXPECT_EQ(Bool::TRUE, Bool{true});
    EXPECT_EQ(Bool::FALSE, Bool{false});
}

TEST(BoolTest, CheckTypeReturnedByConstructors) {
    EXPECT_EQ(typeid(Bool{true}), typeid(Bool)) << "Should be 'Bool'";
    EXPECT_EQ(typeid(Bool{false}), typeid(Bool)) << "Should be 'Bool'";

    EXPECT_EQ(typeid(Bool("true")), typeid(Bool)) << "Should be 'Bool'";
    EXPECT_EQ(typeid(Bool("false")), typeid(Bool)) << "Should be 'Bool'";
}

TEST(BoolTest, CreateFunction) {
    EXPECT_EQ(typeid(Bool::create(15)).name(), typeid(std::unique_ptr<Bool>).name());
    EXPECT_NE(Bool::create(15), nullptr);
}

TEST(BoolTest, BoolValueTest) {
    EXPECT_EQ(Bool(true).boolValue(), true);
    EXPECT_EQ(Bool(false).boolValue(), false);
    EXPECT_EQ(Bool("true").boolValue(), true);
    EXPECT_EQ(Bool("false").boolValue(), false);
}

TEST(BoolTest, CompareFunction) {
    EXPECT_EQ(Bool::compare(true, false), 1);
    EXPECT_EQ(Bool::compare(true, true), 0);
    EXPECT_EQ(Bool::compare(false, false), 0);
    EXPECT_EQ(Bool::compare(false, true), -1);
}

TEST(BoolTest, CompareToFuntion) {
    EXPECT_EQ(Bool(true).compareTo(false), 1);
    EXPECT_EQ(Bool(true).compareTo(true), 0);
    EXPECT_EQ(Bool(false).compareTo(false), 0);
    EXPECT_EQ(Bool(false).compareTo(true), -1);
}

TEST(BoolTest, EqualsFunction) {
    EXPECT_TRUE(Bool(true).equals(true));
    EXPECT_TRUE(Bool(false).equals(false));
    EXPECT_FALSE(Bool(true).equals(false));
    EXPECT_FALSE(Bool(false).equals(true));
}

TEST(BoolTest, GetBoolFunction) {
    std::string value{"true"};
    EXPECT_TRUE(Bool::getBool(value)); 

    value = "false";
    EXPECT_FALSE(Bool::getBool(value));
}

TEST(BoolTest, HashCodeFunctions) {
    /* -- int16_t hashCode() -- */
    EXPECT_EQ(Bool(true).hashCode(), 1231);
    EXPECT_EQ(Bool(false).hashCode(), 1237);
    EXPECT_EQ(Bool("true").hashCode(), 1231);
    EXPECT_EQ(Bool("false").hashCode(), 1237);
    
    /* -- int16_t hashCode(const bool&) -- */
    EXPECT_EQ(Bool::hashCode(true), 1231);
    EXPECT_EQ(Bool::hashCode(false), 1237);
}

TEST(BoolTest, LogicalFunctions) {
    /* -- bool logicalAnd() -- */
    EXPECT_TRUE(Bool::logicalAnd(true, true));
    EXPECT_FALSE(Bool::logicalAnd(true, false));
    EXPECT_FALSE(Bool::logicalAnd(false, true));
    EXPECT_FALSE(Bool::logicalAnd(false, false));

    /* -- bool logicalOr() -- */
    EXPECT_TRUE(Bool::logicalOr(true, true));
    EXPECT_TRUE(Bool::logicalOr(true, false));
    EXPECT_TRUE(Bool::logicalOr(false, true));
    EXPECT_FALSE(Bool::logicalOr(false, false));

    /* -- bool logicalXor() -- */
    EXPECT_FALSE(Bool::logicalXor(true, true));
    EXPECT_TRUE(Bool::logicalXor(true, false));
    EXPECT_TRUE(Bool::logicalXor(false, true));
    EXPECT_FALSE(Bool::logicalXor(false, false));
}

TEST(BoolTest, ParseBoolFunction) {
    std::string value{"true"};
    EXPECT_TRUE(Bool::parseBool(value));
    
    value = "false";
    EXPECT_FALSE(Bool::parseBool(value));
}

TEST(BoolTest, ToStringFunctions) {
    /* -- std::string toString() const-- */
    EXPECT_EQ(Bool(true).toString(), "true");
    EXPECT_EQ(Bool(false).toString(), "false");
    EXPECT_EQ(Bool("true").toString(), "true");
    EXPECT_EQ(Bool("false").toString(), "false");

    /* -- std::string toString(const bool) -- */
    EXPECT_EQ(Bool::toString(true), "true");
    EXPECT_EQ(Bool::toString(false), "false");
}

TEST(BoolTest, ValueOfFunctions) {
    /* -- Bool valueOf(const bool&) -- */
    EXPECT_EQ(Bool::valueOf(true), Bool{true});
    EXPECT_EQ(Bool::valueOf(false), Bool{false});

    /* -- Bool valueOf(std::string&) -- */
    EXPECT_EQ(Bool::valueOf("true"), Bool{true});
    EXPECT_EQ(Bool::valueOf("false"), Bool{false});
}

TEST(BoolTest, SpaceshipOperator) {
    // "operator<=>(const Bool&) = default" auto-defines our comparison operators
    /* -- == -- */
    EXPECT_TRUE(Bool{true} == true);
    EXPECT_FALSE(Bool{true} == false);
    EXPECT_TRUE(Bool{false} == false);
    EXPECT_FALSE(Bool{false} == true);
    EXPECT_TRUE(Bool{"true"} == true);
    EXPECT_FALSE(Bool{"true"} == false);
    EXPECT_TRUE(Bool{"false"} == false);
    EXPECT_FALSE(Bool{"false"} == true);
    
    /* -- != -- */
    EXPECT_FALSE(Bool{true} != true);
    EXPECT_TRUE(Bool{true} != false);
    EXPECT_FALSE(Bool{false} != false);
    EXPECT_TRUE(Bool{false} != true);
    EXPECT_FALSE(Bool{"true"} != true);
    EXPECT_TRUE(Bool{"true"} != false);
    EXPECT_FALSE(Bool{"false"} != false);
    EXPECT_TRUE(Bool{"false"} != true);
    
    /* -- >= -- */
    EXPECT_TRUE(Bool{true} >= true);
    EXPECT_TRUE(Bool{true} >= false);
    EXPECT_TRUE(Bool{false} >= false);
    EXPECT_FALSE(Bool{false} >= true);
    EXPECT_TRUE(Bool{"true"} >= true);
    EXPECT_TRUE(Bool{"true"} >= false);
    EXPECT_TRUE(Bool{"false"} >= false);
    EXPECT_FALSE(Bool{"false"} >= true);
    
    /* -- <= -- */
    EXPECT_TRUE(Bool{true} <= true);
    EXPECT_FALSE(Bool{true} <= false);
    EXPECT_TRUE(Bool{false} <= false);
    EXPECT_TRUE(Bool{false} <= true);
    EXPECT_TRUE(Bool{"true"} <= true);
    EXPECT_FALSE(Bool{"true"} <= false);
    EXPECT_TRUE(Bool{"false"} <= false);
    EXPECT_TRUE(Bool{"false"} <= true);
    
    /* -- < -- */
    EXPECT_FALSE(Bool{true} < true);
    EXPECT_FALSE(Bool{true} < false);
    EXPECT_FALSE(Bool{false} < false);
    EXPECT_TRUE(Bool{false} < true);
    EXPECT_FALSE(Bool{"true"} < true);
    EXPECT_FALSE(Bool{"true"} < false);
    EXPECT_FALSE(Bool{"false"} < false);
    EXPECT_TRUE(Bool{"false"} < true);
    
    /* -- > -- */
    EXPECT_FALSE(Bool{true} > true);
    EXPECT_TRUE(Bool{true} > false);
    EXPECT_FALSE(Bool{false} > false);
    EXPECT_FALSE(Bool{false} > true);
    EXPECT_FALSE(Bool{"true"} > true);
    EXPECT_TRUE(Bool{"true"} > false);
    EXPECT_FALSE(Bool{"false"} > false);
    EXPECT_FALSE(Bool{"false"} > true);
}

TEST(BoolTest, StreamOverload) {
    /* -- operator<<(std::ostream&. Bool&) -- */
    std::stringstream out;    
    out << Bool{true};
    EXPECT_EQ(out.str(), "true");

    out.str("");
    out << Bool{"true"};
    EXPECT_EQ(out.str(), "true");

    out.str("");
    out << Bool{false};
    EXPECT_EQ(out.str(), "false");
    
    out.str("");
    out << Bool{"false"};
    EXPECT_EQ(out.str(), "false");
}

TEST(BoolTest, HelperFunctions) {
    /* -- toLowerCase(std::string&) -- */
    {
        std::string s1 = "true";  EXPECT_EQ((Bool::toLowerCase(s1), s1), "true");
        std::string s2 = "True";  EXPECT_EQ((Bool::toLowerCase(s2), s2), "true");
        std::string s3 = "tRue";  EXPECT_EQ((Bool::toLowerCase(s3), s3), "true");
        std::string s4 = "trUe";  EXPECT_EQ((Bool::toLowerCase(s4), s4), "true");
        std::string s5 = "truE";  EXPECT_EQ((Bool::toLowerCase(s5), s5), "true");
        std::string s6 = "TRue";  EXPECT_EQ((Bool::toLowerCase(s6), s6), "true");
        std::string s7 = "TrUe";  EXPECT_EQ((Bool::toLowerCase(s7), s7), "true");
        std::string s8 = "TruE";  EXPECT_EQ((Bool::toLowerCase(s8), s8), "true");
        std::string s9 = "TRUe";  EXPECT_EQ((Bool::toLowerCase(s9), s9), "true");
        std::string s10 = "TRuE"; EXPECT_EQ((Bool::toLowerCase(s10), s10), "true");
        std::string s11 = "TRUE"; EXPECT_EQ((Bool::toLowerCase(s11), s11), "true");
    }
    
    {
        std::string s1 = "false";  EXPECT_EQ((Bool::toLowerCase(s1), s1), "false");
        std::string s2 = "False";  EXPECT_EQ((Bool::toLowerCase(s2), s2), "false");
        std::string s3 = "fAlse";  EXPECT_EQ((Bool::toLowerCase(s3), s3), "false");
        std::string s4 = "faLse";  EXPECT_EQ((Bool::toLowerCase(s4), s4), "false");
        std::string s5 = "falSe";  EXPECT_EQ((Bool::toLowerCase(s5), s5), "false");
        std::string s6 = "falsE";  EXPECT_EQ((Bool::toLowerCase(s6), s6), "false");
        std::string s7 = "FAlse";  EXPECT_EQ((Bool::toLowerCase(s7), s7), "false");
        std::string s8 = "FaLse";  EXPECT_EQ((Bool::toLowerCase(s8), s8), "false");
        std::string s9 = "FalSe";  EXPECT_EQ((Bool::toLowerCase(s9), s9), "false");
        std::string s10 = "FalsE"; EXPECT_EQ((Bool::toLowerCase(s10), s10), "false");
        std::string s11 = "FALse"; EXPECT_EQ((Bool::toLowerCase(s11), s11), "false");
        std::string s12 = "FAlSe"; EXPECT_EQ((Bool::toLowerCase(s12), s12), "false");
        std::string s13 = "FAlsE"; EXPECT_EQ((Bool::toLowerCase(s13), s13), "false");
        std::string s14 = "FALSe"; EXPECT_EQ((Bool::toLowerCase(s14), s14), "false");
        std::string s15 = "FALsE"; EXPECT_EQ((Bool::toLowerCase(s15), s15), "false");
        std::string s16 = "FALSE"; EXPECT_EQ((Bool::toLowerCase(s16), s16), "false");
    }

    /* -- toUpperCase(std::string&) -- */
    {
        std::string s1 = "true";  EXPECT_EQ((Bool::toUpperCase(s1), s1), "TRUE");
        std::string s2 = "True";  EXPECT_EQ((Bool::toUpperCase(s2), s2), "TRUE");
        std::string s3 = "tRue";  EXPECT_EQ((Bool::toUpperCase(s3), s3), "TRUE");
        std::string s4 = "trUe";  EXPECT_EQ((Bool::toUpperCase(s4), s4), "TRUE");
        std::string s5 = "truE";  EXPECT_EQ((Bool::toUpperCase(s5), s5), "TRUE");
        std::string s6 = "TRue";  EXPECT_EQ((Bool::toUpperCase(s6), s6), "TRUE");
        std::string s7 = "TrUe";  EXPECT_EQ((Bool::toUpperCase(s7), s7), "TRUE");
        std::string s8 = "TruE";  EXPECT_EQ((Bool::toUpperCase(s8), s8), "TRUE");
        std::string s9 = "TRUe";  EXPECT_EQ((Bool::toUpperCase(s9), s9), "TRUE");
        std::string s10 = "TRuE"; EXPECT_EQ((Bool::toUpperCase(s10), s10), "TRUE");
        std::string s11 = "TRUE"; EXPECT_EQ((Bool::toUpperCase(s11), s11), "TRUE");
    }
    
    {
        std::string s1 = "false";  EXPECT_EQ((Bool::toUpperCase(s1), s1), "FALSE");
        std::string s2 = "False";  EXPECT_EQ((Bool::toUpperCase(s2), s2), "FALSE");
        std::string s3 = "fAlse";  EXPECT_EQ((Bool::toUpperCase(s3), s3), "FALSE");
        std::string s4 = "faLse";  EXPECT_EQ((Bool::toUpperCase(s4), s4), "FALSE");
        std::string s5 = "falSe";  EXPECT_EQ((Bool::toUpperCase(s5), s5), "FALSE");
        std::string s6 = "falsE";  EXPECT_EQ((Bool::toUpperCase(s6), s6), "FALSE");
        std::string s7 = "FAlse";  EXPECT_EQ((Bool::toUpperCase(s7), s7), "FALSE");
        std::string s8 = "FaLse";  EXPECT_EQ((Bool::toUpperCase(s8), s8), "FALSE");
        std::string s9 = "FalSe";  EXPECT_EQ((Bool::toUpperCase(s9), s9), "FALSE");
        std::string s10 = "FalsE"; EXPECT_EQ((Bool::toUpperCase(s10), s10), "FALSE");
        std::string s11 = "FALse"; EXPECT_EQ((Bool::toUpperCase(s11), s11), "FALSE");
        std::string s12 = "FAlSe"; EXPECT_EQ((Bool::toUpperCase(s12), s12), "FALSE");
        std::string s13 = "FAlsE"; EXPECT_EQ((Bool::toUpperCase(s13), s13), "FALSE");
        std::string s14 = "FALSe"; EXPECT_EQ((Bool::toUpperCase(s14), s14), "FALSE");
        std::string s15 = "FALsE"; EXPECT_EQ((Bool::toUpperCase(s15), s15), "FALSE");
        std::string s16 = "FALSE"; EXPECT_EQ((Bool::toUpperCase(s16), s16), "FALSE");
    }
}