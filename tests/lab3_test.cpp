#include <iostream>
#include <gtest/gtest.h>

#include "parent.hpp"

void TestParent(std::string &src, std::string &res) {
    std::istringstream srcStream(src);

    std::streambuf* buf = std::cin.rdbuf(srcStream.rdbuf());

    testing::internal::CaptureStdout();
    ParentWork(); 
    ASSERT_EQ(testing::internal::GetCapturedStdout(), res + '\n'); 

    std::cin.rdbuf(buf);
}


TEST(cin_test, ONE) {
    std::string src = "       \n\n";
    std::string res = "_______\n";
    TestParent(src, res);
}

TEST(cin_test, TWO) {
    std::string src = "AHAHAHAHAH\n\n";
    std::string res = "ahahahahah\n";
    TestParent(src, res);
}

TEST(cin_test, THREE) {
    std::string src = "   HELLO wOrLd 12 3\n\n";
    std::string res = "___hello_world_12_3\n";
    TestParent(src, res);
}
