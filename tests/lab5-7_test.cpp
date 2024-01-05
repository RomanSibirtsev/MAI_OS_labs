#include <gtest/gtest.h>

#include "set"

#include "node.hpp"
#include "socket.hpp"

TEST(FifthSeventhLabTests, PingTest) {
    std::string programPath = getenv("PROGRAM_PATH");
    std::set<int> Nodes;
    Node task(-1);
    Nodes.insert(-1);
    task.Create(1, programPath);
    Nodes.insert(1);

    std::string ans = task.Send("ping 1", 1);
    EXPECT_EQ(ans, "Ok: 1");

    ans = task.Send("ping 3", 3);
    EXPECT_EQ(ans, "Error: Not found");

    task.Kill();
}

TEST(FifthSeventhLabTests, ExecTest) {
    std::string programPath = getenv("PROGRAM_PATH");
    std::set<int> Nodes;
    Node task(-1);
    Nodes.insert(-1);
    task.Create(1, programPath);
    Nodes.insert(1);

    std::string ans = task.Send("exec asdfgh asd", 1);
    EXPECT_EQ(ans, "Ok: 1: 0;");

    task.Kill();
}

TEST(FifthSeventhLabTests, FullTest) {
    std::string programPath = getenv("PROGRAM_PATH");
    std::string ans;
    std::set<int> Nodes;
    Node task(-1);
    Nodes.insert(-1);
    task.Create(1, programPath);
    Nodes.insert(1);
    task.Send("create 2", 1);
    Nodes.insert(2);
    task.Send("create 3", 2);
    Nodes.insert(3);
    
    ans = task.Send("ping 1", 1);
    EXPECT_EQ(ans, "Ok: 1");
    ans = task.Send("ping 2", 2);
    EXPECT_EQ(ans, "Ok: 1");

    ans = task.Send("exec qwqwqwqwqw qw", 2);
    EXPECT_EQ(ans, "Ok: 2: 0;2;4;6;8;");

    ans = task.Send("exec qwerty ert", 3);
    EXPECT_EQ(ans, "Ok: 3: 2;");

    task.Kill();
}
