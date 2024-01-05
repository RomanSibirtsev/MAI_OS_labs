#include "node.hpp"
#include "socket.hpp"
#include <fstream>
#include <signal.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        perror("Not enough arguments");
        exit(EXIT_FAILURE);
    }
    
    Node task(atoi(argv[1]), atoi(argv[2]));
    std::string programPath = getenv("PROGRAM_PATH");
    while(1) {
        std::string message;
        std::string command = " ";
        if (auto msg = ReceiveMessage(&(task.parent)); msg.has_value()) {
            message = *msg;
        }
        std::istringstream request(message);
        request >> command;

        if (command == "create") {
            int idChild;
            request >> idChild;
            std::string ans = task.Create(idChild, programPath);
            SendMessage(&task.parent, ans);
        } else if (command == "pid") {
            std::string ans = task.Pid();
            SendMessage(&task.parent, ans);
        } else if (command == "ping") {
            int idChild;
            request >> idChild;
            std::string ans = task.Ping(idChild);
            SendMessage(&task.parent, ans);
        } else if (command == "send") {
            int id;
            request >> id;
            std::string str;
            getline(request, str);
            str.erase(0, 1);
            std::string ans;
            ans = task.Send(str, id);
            SendMessage(&task.parent, ans);
        } else if (command == "exec") {
            long unsigned int i, j;
            std::string a, b, res = "";
            request >> a >> b;
            for (i = 0; i <= a.size() - b.size(); ++i) {
                for (j = 0; j < b.size(); ++j) {
                    if (a[i + j] != b[j]) {
                        break;
                    }
                }
                if (j == b.size()) {
                    res += std::to_string(i) + ";";
                }
            }
            if (res == "") res = "-1;";
            std::string to_send;
            to_send = "Ok: " + std::to_string(task.id) + ": " + res;
            SendMessage(&task.parent,to_send);
        } else if (command == "kill") {
            std::string ans = task.Kill();
            ans = std::to_string(task.id) + " " + ans;
            SendMessage(&task.parent, ans);
            Disconnect(&task.parent, task.parentPort);
            task.parent.close();
            break;
        }
    }

    return 0;
}