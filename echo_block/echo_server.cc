#include "../common_include.hpp"

#include <thread>
using namespace std;

int main(int argc, char **argv)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0); //TCP
    assert(fd > 0);
    sockaddr_in servaddr;
    ::bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(55555);
    inet_aton("127.0.0.1", &servaddr.sin_addr);
    int err = bind(fd, SOCK_CAST(&servaddr), sizeof(servaddr));
    assert(err == 0);
    err = listen(fd, 5);
    assert(err == 0);

    while (1)
    {
        sockaddr_in client_addr;
        socklen_t client_addr_len;
        int connfd = accept(fd, SOCK_CAST(&client_addr), &client_addr_len);
        std::thread worker([&]()
                           {
                               int myfd = connfd;
                               while (1)
                               {
                                   char buf[4096];
                                   int nread = read(myfd, buf, 4096);
                                   cout << "read " << nread << " bytes" << endl;
                                   if (nread <= 0)
                                   {
                                       break;
                                   }
                                   int nsend = write(myfd, buf, nread);
                                   cout << "send " << nsend << " bytes" << endl;
                                   if (nsend <= 0)
                                   {
                                       break;
                                   }
                               }
                               close(myfd);
                           });
        worker.detach();
    }
    return 0;
}