#include <sys/socket.h> //socket funcs
#include <netinet/in.h> //sockaddr_in
#include <arpa/inet.h>  //inet_aton
#include <iostream>
#include <cstring> //bzero
#include <chrono>
#include <cassert>
using namespace std;
using namespace std::chrono;
using Clock = std::chrono::high_resolution_clock;

template <typename T>
const sockaddr *SOCK_CAST(T arg)
{
    return reinterpret_cast<const sockaddr *>(arg);
}

int main(int argc, char **argv)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0); //TCP
    assert(fd > 0);
    sockaddr_in servaddr;
    ::bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(55555);
    inet_aton("192.3.4.5", &servaddr.sin_addr);
    auto start = Clock::now();
    int err = connect(fd, SOCK_CAST(&servaddr), sizeof(servaddr));
    auto end = Clock::now();
    assert(err == -1);
    perror("errno");
    cout << duration_cast<seconds>(end - start).count() << " seconds connection failed." << endl;
    return 0;
}