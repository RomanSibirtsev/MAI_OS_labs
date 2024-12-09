#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>

int ParentWork();
void CreatePipe(int *fd);
int CreateFork();
void DoClose(int fd);