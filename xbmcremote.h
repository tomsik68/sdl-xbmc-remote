#ifndef XBMCREMOTE_H
#define XBMCREMOTE_H

#include "xbmcclient.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#define CONNECT_OK 0
#define CONNECT_FAILED -1

class XBMCRemote
{
public:
    XBMCRemote(char *deviceName,char *addr, int port);
    int sayHello();
    void sayBye();
    void sendPing();
    void sendButton( char *button, char *keymap);
    void sendMouse(int x, int y);
    void sendNotification(char *caption, char *message, int iconType, char *iconPath);
    void sendButtonNumber(int button, bool press);
private:
    CAddress *address;
    char *deviceName;
    int sockfd;

};

#endif // XBMCREMOTE_H
