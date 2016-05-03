#ifndef DATAGRAM_FUNCTIONS_H
#define DATAGRAM_FUNCTIONS_H
void DgEcho(int sockFd, struct sockaddr *pclientAddr, socklen_t maxCliLen);
int DgClient (char *sendMsg, int sockFd, struct sockaddr *pservAddr, int servLen);
#endif
