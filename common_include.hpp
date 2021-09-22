#include <sys/socket.h> //socket funcs
#include <netinet/in.h> //sockaddr_in
#include <arpa/inet.h>  //inet_aton
#include <iostream>
#include <cstring> //bzero
#include <chrono>
#include <cassert>
#include <fcntl.h>
#include <unistd.h>
#include <chrono>

template <typename T>
sockaddr *SOCK_CAST(T ptr)
{
    return reinterpret_cast<sockaddr *>(ptr);
}

inline void ExitAssert(bool judge, std::string &&msg)
{
    if (!judge)
    {
        std::cerr << "error: " << msg << std::endl;
        exit(-1);
    }
}