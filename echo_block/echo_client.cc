#include "../common_include.hpp"

int main(int argc, char **argv)
{
    ExitAssert(argc == 3, "usage: ./echo_client port msg_len");
    int fd = socket(AF_INET, SOCK_STREAM, 0); //TCP
    assert(fd > 0);
    sockaddr_in servaddr;
    ::bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(std::atoi(argv[1]));
    inet_aton("127.0.0.1", &servaddr.sin_addr);

    int err = connect(fd, SOCK_CAST(&servaddr), sizeof(servaddr));
    ExitAssert(err == 0, "connect");

    const size_t msgLen = std::atoi(argv[2]);
    size_t left = msgLen;
    char buf[4096];
    while (left)
    {
        int nwrite = 0;
        if (left > 4096)
        {
            nwrite = write(fd, buf, 4096);
        }
        else
        {
            nwrite = write(fd, buf, left);
        }
        ExitAssert(nwrite >= 0, "write");
        left -= nwrite;
    }
    left = msgLen;
    while (left)
    {
        int nread = 0;
        if (left > 4096)
        {
            nread = read(fd, buf, 4096);
        }
        else
        {
            nread = read(fd, buf, left);
        }

        if (nread <= 0)
        {
            break;
        }
        left -= nread;
    }
    std::cout << "read " << msgLen << " bytes" << std::endl;
    close(fd);
    return 0;
}