#pragma once
#include <ws2tcpip.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

class CNetUnits
{
public:
	CNetUnits(void);
	~CNetUnits(void);
	int SocketInit(void);//socket 初始化
	int SocketExit(void);//清理套接字占用的资源
	//创建socket, 返回-1表示失败, type=SOCK_STREAM, ... , protocol=IPPROTO_TCP,...
	SOCKET SocketCreate(int af, int type, int protocol);
	void SocketDestroy(SOCKET skt);//销毁socket
	/* 连接远端 ,timeout为等待连接超时时间 单位为秒*/
	int SocketConnect(SOCKET skt, char* strip, unsigned int port, int timeout = 5);
	int SocketBind(SOCKET skt, char* strip, unsigned int port);/* 绑定接收地址和端口 */
	int SocketListen(SOCKET skt, int max);/* 开始监听, max为悬挂队列长度 */
	SOCKET SocketAccept(SOCKET skt, char* strip, unsigned int* port);/* 等待远程连接 */
	int SocketIoctl(SOCKET skt, int type, unsigned long* val);/* 输入输出控制 */
	int SocketOpt(SOCKET skt, int level, int optname, const char* optval, int optlen);/* 设置参数 */
	/* 检测状态,timeout单位ms, timeout=-1表示无限等待 */
	int SocketSelect(int maxfd, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, int timeout);
	int SocketSend(SOCKET skt, char* buf, int size, int timeout);/* 发送数据 */
	int SocketRecv(SOCKET skt, char* buf, int size, int timeout);/* 接收数据 */
	int SocketJoin(SOCKET skt, char* strip);/* 加入多播组 */
	int SocketDrop(SOCKET skt, char* strip);/* 退出组播组 */
	int SocketSendto(SOCKET skt, char* strip, unsigned int port, char* buf, int size, int timeout);/* 发送数据 */
	int SocketRecvfrom(SOCKET skt, char* strip, unsigned int* port, char* buf, int size, int timeout);/* 接收数据 */
	int SocketGetLastError(void);/*获取错误信息*/
	void GetHostIp(char* ip);/*获取本机IP地址*/
	int GetHostPort(SOCKET skt);/*获取本机可用端口*/
};
