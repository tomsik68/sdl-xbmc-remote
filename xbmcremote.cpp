#include "xbmcremote.h"
#include "xbmcclient.h"
#include <sys/types.h>

XBMCRemote::XBMCRemote(char* deviceName, char* addr, int port)
{
    this->address = new CAddress(addr, port);
    this->deviceName = deviceName;
}

int XBMCRemote::sayHello(){
    this->sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0){
        printf("Socket creation failed!\n");
        return CONNECT_FAILED;
    }
    address->Bind(sockfd);
    CPacketHELO packet(this->deviceName,ICON_NONE);
    packet.Send(sockfd, *address);
    return CONNECT_OK;
}

void XBMCRemote::sendPing(){
    CPacketPING packet;
    packet.Send(sockfd, *address);
}

void XBMCRemote::sayBye(){
    CPacketBYE bye;
    bye.Send(sockfd, *address);
}

void XBMCRemote::sendButton(char *button, char *keymap){
    CPacketBUTTON packet(button, keymap, 0);
    packet.Send(sockfd, *address);
}

void XBMCRemote::sendMouseMove(uint16_t x, uint16_t y){
    CPacketMOUSE packet(x,y);
    packet.Send(sockfd, *address);
}

void XBMCRemote::sendNotification(char *caption, char *message, int iconType, char *iconPath){
    CPacketNOTIFICATION packet(caption,message,iconType,iconPath);    // icon file (local)      packet.Send(sockfd, my_addr);
    packet.Send(sockfd, *address);
}

void XBMCRemote::sendButtonNumber(int button, bool press){
    CPacketBUTTON packet(button, "KB", (press ? BTN_DOWN : BTN_UP) | BTN_VKEY);
    packet.Send(sockfd, *address);
}

void XBMCRemote::sendMouseDown(int button){
    CPacketBUTTON packet(button, "MS", BTN_DOWN);
    packet.Send(sockfd, *address);
}
