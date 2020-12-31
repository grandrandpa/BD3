#pragma once
#include <ws2tcpip.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

class CNetUnits
{
public:
	CNetUnits(void);
	~CNetUnits(void);
	int SocketInit(void);//socket ��ʼ��
	int SocketExit(void);//�����׽���ռ�õ���Դ
	//����socket, ����-1��ʾʧ��, type=SOCK_STREAM, ... , protocol=IPPROTO_TCP,...
	SOCKET SocketCreate(int af, int type, int protocol);
	void SocketDestroy(SOCKET skt);//����socket
	/* ����Զ�� ,timeoutΪ�ȴ����ӳ�ʱʱ�� ��λΪ��*/
	int SocketConnect(SOCKET skt, char* strip, unsigned int port, int timeout = 5);
	int SocketBind(SOCKET skt, char* strip, unsigned int port);/* �󶨽��յ�ַ�Ͷ˿� */
	int SocketListen(SOCKET skt, int max);/* ��ʼ����, maxΪ���Ҷ��г��� */
	SOCKET SocketAccept(SOCKET skt, char* strip, unsigned int* port);/* �ȴ�Զ������ */
	int SocketIoctl(SOCKET skt, int type, unsigned long* val);/* ����������� */
	int SocketOpt(SOCKET skt, int level, int optname, const char* optval, int optlen);/* ���ò��� */
	/* ���״̬,timeout��λms, timeout=-1��ʾ���޵ȴ� */
	int SocketSelect(int maxfd, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, int timeout);
	int SocketSend(SOCKET skt, char* buf, int size, int timeout);/* �������� */
	int SocketRecv(SOCKET skt, char* buf, int size, int timeout);/* �������� */
	int SocketJoin(SOCKET skt, char* strip);/* ����ಥ�� */
	int SocketDrop(SOCKET skt, char* strip);/* �˳��鲥�� */
	int SocketSendto(SOCKET skt, char* strip, unsigned int port, char* buf, int size, int timeout);/* �������� */
	int SocketRecvfrom(SOCKET skt, char* strip, unsigned int* port, char* buf, int size, int timeout);/* �������� */
	int SocketGetLastError(void);/*��ȡ������Ϣ*/
	void GetHostIp(char* ip);/*��ȡ����IP��ַ*/
	int GetHostPort(SOCKET skt);/*��ȡ�������ö˿�*/
};
