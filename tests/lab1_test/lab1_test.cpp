#include <iostream>
#include <gtest/gtest.h>

#include "parent.hpp"

void TestParent(std::string &file1, std::string &file2) {
    std::ifstream srcStream(file1);
    std::ifstream resStream(file2);

    std::string result;
    std::getline(resStream, result);

    std::streambuf* buf = std::cin.rdbuf(srcStream.rdbuf());

    testing::internal::CaptureStdout();
    ParentWork(); 
    ASSERT_EQ(testing::internal::GetCapturedStdout(), result + '\n'); 

    std::cin.rdbuf(buf);
}


TEST(cin_test, ONE) {
    std::string file1 = "test1_src.txt";
    std::string file2 = "test1_res.txt";
    TestParent(file1, file2);
}

TEST(cin_test, TWO) {
    std::string file1 = "test2_src.txt";
    std::string file2 = "test2_res.txt";
    TestParent(file1, file2);
}

TEST(cin_test, THREE) {
    std::string file1 = "test3_src.txt";
    std::string file2 = "test3_res.txt";
    TestParent(file1, file2);
}
