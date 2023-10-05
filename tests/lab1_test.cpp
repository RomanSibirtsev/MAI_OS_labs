#include <iostream>
#include <gtest/gtest.h>
#include <fstream>

#include "parent.hpp"

void readUserInput()
{
    std::string value;
    while(std::getline(std::cin, value)) {
        std::cout << value << std::endl;
    }
}

void testParent() {
    int fildes[2];
    int status = pipe(fildes);
    ASSERT_NE(status, -1);

    status = dup2(fildes[0], STDIN_FILENO);
    ASSERT_NE(status, -1);

    const char buf[] = "aboba";
    const int bsize  = strlen(buf);

    ssize_t nbytes = write(fildes[1], buf, bsize);
    ASSERT_EQ(nbytes, bsize);

    close(fildes[1]);

    testing::internal::CaptureStdout();
    readUserInput();
    //parentWork(); 
    ASSERT_EQ(testing::internal::GetCapturedStdout(), "aboba\n"); 
    testing::internal::   

    close(fildes[0]);
}

// TEST(cin, Basic)
// {
//     // Create pipe to mock stdin
//     int fildes[2];
//     int status = pipe(fildes);
//     ASSERT_NE(status, -1);

//     // Swap `stdin` fd with the "read" end of the pipe
//     //int copy = dup(STDIN_FILENO);
//     status = dup2(fildes[0], STDIN_FILENO);
//     ASSERT_NE(status, -1);

//     // Create payload
//     const char buf[] = "45 ert";
//     const int bsize  = strlen(buf);
//     //const char end = EOF;

//     // Send payload through pipe
//     ssize_t nbytes = write(fildes[1], buf, bsize);
//     ASSERT_EQ(nbytes, bsize);

//    // write(fildes[1], &end, sizeof(end));
//     close(fildes[1]);
//     //ASSERT_EQ(readUserInput(), 2);
//     testing::internal::CaptureStdout();
//     readUserInput();
//     //parentWork();
//     ASSERT_EQ(testing::internal::GetCapturedStdout(), "45_ert\n");

//     close(fildes[0]);
// }

TEST(cin_test, ONE) {
    testParent();
}

TEST(cin_test, TWO) {
    readUserInput(); 
}