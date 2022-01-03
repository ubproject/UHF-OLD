#pragma once
#ifndef INCLUDE_GUARD_SANAENET_H
#define INCLUDE_GUARD_SANAENET_H
#include <winsock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

/*�Q�l�T�C�g
https://shizenkarasuzon.hatenablog.com/entry/2020/06/25/150229
https://qiita.com/srs/items/c9286b5cff99e741b993
https://www.geekpage.jp/programming/winsock/tcp.php
https://qiita.com/parallax_kk/items/9e877542fecb4087729f
https://codehero.jp/c%2B%2B/8032080/how-to-convert-char-to-wchar-t
https://c-lang.net/%e3%83%9e%e3%83%ab%e3%83%81%e3%83%90%e3%82%a4%e3%83%88%e6%96%87%e5%ad%97%e5%88%97%e3%82%92%e3%83%af%e3%82%a4%e3%83%89%e6%96%87%e5%ad%97%e5%88%97%e3%81%ab%e5%a4%89%e6%8f%9b%e3%81%99%e3%82%8b-2/index.html
*/
#ifdef INCLUDE_GUARD_SANAESTR_H
//inet_addr���g�p����p
#pragma warning(disable:4996) 
namespace sanae {
	/*
	*Copyright 2021 SanaeProject.ALL Rights Reserved.
	* Author Usagi
	This header file did Implement of UDP and TCP for IPV4.
	*/
	namespace UDP {
		/*TestCode:
			Reader:
				sanae::UDP::udp t(111, "?.?.?.?");
				t.bind_udp();
				sanae::str d = t.recv_udp();
				printf("got:%s",d.c_str());
			Sender:
				sanae::UDP::udp t(111,"?.?.?.?");
				t.send_udp("hello");
		*/
		class udp {
		private:
			bool _bind = false;
			WSAData wsaData;
			int sock;
			struct sockaddr_in addr;
			const char* Inet_ntop(int family, const void* addrptr, char* strptr, size_t len) {
				if (family == AF_INET) {
					return inet_ntop(family, &((struct sockaddr_in*)addrptr)->sin_addr, strptr, len);
				}
				return (NULL);
			}
		public:
			const char* GetMyIp() {
				WSADATA wsadata;
				if (WSAStartup(MAKEWORD(1, 1), &wsadata) != 0) {
					puts("[ERROR]IP�A�h���X�擾�Ɏ��s���܂����B\n");
					exit(0);
				}
				char hostname[256];
				if (gethostname(hostname, sizeof(hostname)) != 0) {
					puts("[ERROR]IP�A�h���X�擾�Ɏ��s���܂����B\n");
					exit(0);
				}
				HOSTENT* hostend = gethostbyname(hostname);
				if (hostend == NULL) {
					puts("[ERROR]IP�A�h���X�擾�Ɏ��s���܂����B\n");
					exit(0);
				}
				IN_ADDR inaddr;
				memcpy(&inaddr, hostend->h_addr_list[0], 4);
				strcpy_s(HOSTIPADD, inet_ntoa(inaddr));
				WSACleanup();
			}
			char HOSTIPADD[16] = {0};
			char IPADD[16] = { 0 };
			//�u���b�L���O����:0 �u���b�L���O���Ȃ�:1
			u_long stop = 0;
			/*sanae::UDP::udp �ϐ�(�|�[�g�ԍ�,�ʐM��IP�A�h���X)*/
			udp(u_short port,sanae::str ip) {
				WSACleanup();
				int error=WSAStartup(MAKEWORD(2, 0), &wsaData);
				if (error != 0) {
					printf("Message:ERROR\nCode:%d\n", error);
					exit(0);
				}
				sock = socket(AF_INET, SOCK_DGRAM, 0);
				addr.sin_family = AF_INET;
				addr.sin_port = htons(port);
				addr.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
				GetMyIp();
				//�u���b�L���O�p
				ioctlsocket(sock, FIONBIO, &stop);
			}
			~udp() {
				closesocket(sock);
				WSACleanup();
			}
			void send_udp(sanae::str text) {
				sendto(sock, text.c_str(), text.len(), 0, (struct sockaddr*)&addr, sizeof(addr));
			}
			//recv_udp�����s����O��bind_udp�����s���Ă�������
			void bind_udp() {
				bind(sock, (const struct sockaddr*)&addr, sizeof(addr));
				_bind = true;
				Inet_ntop(AF_INET, &addr, IPADD, sizeof(IPADD));
			}
			char* recv_udp(size_t size = 1024) {
				if (!_bind) {
					this->bind_udp();
				}
				_bind = false;
				char* buf = (char*)calloc(size, sizeof(char*));
				if (buf==NULL) {
					if (buf == NULL) { printf("[Message]�������̊m�ۂɎ��s���܂����B"); exit(0); }
				}
				recv(sock, buf, size, 0);
				return buf;
			}
		};
	}
	namespace TCP {
		/*server�p�N���X(IPV4)*/
		class server {
		private:
			struct sockaddr_in addr;
			struct sockaddr_in client;
			SOCKET sock;
			sanae::str data;
			WSADATA wsaData;
			SOCKET sock0;
			int len;
			bool started = false;
			const char* Inet_ntop(int family, const void* addrptr, char* strptr, size_t len){
				if (family == AF_INET) {
					return inet_ntop(family,&((struct sockaddr_in*)addrptr)->sin_addr,strptr, len);
				}
				return (NULL);
			}
		public:
			char IPADD[16] = {0};
			//�����ݒ���s���܂�
			server(u_short PORT) {
				started = true;
				int error = WSAStartup(MAKEWORD(2, 0), &wsaData);
				if (error!=0) {
					printf("Message:ERROR\nCode:%d\n", error);
					exit(0);
				}
				sock0 = socket(AF_INET, SOCK_STREAM, 0);
				addr.sin_family = AF_INET;
				addr.sin_port = htons(PORT);
				addr.sin_addr.S_un.S_addr = INADDR_ANY;			
			}
			~server() {
				this->end();
			}
			//��t
			void accept_tcp() {
				bind(sock0, (struct sockaddr*)&addr, sizeof(addr));
				listen(sock0, 5);
				len = sizeof(client);
				sock = accept(sock0, (struct sockaddr*)&client, &len);
				Inet_ntop(AF_INET, &addr, IPADD, sizeof(IPADD));
			}
			//���M
			void send_tcp(const char* data) {
				send(sock, data, strlen(data)+1, 0);
			}
			//��M
			sanae::str recv_tcp(size_t datasize) {
				char* d = (char*)calloc(datasize,sizeof(char*));
				if (d == NULL) { printf("[Message]�������̊m�ۂɎ��s���܂����B"); exit(0); }
				int n = recv(sock,d, datasize, 0);
				data.add(d);
				return data;
			}
			//�I��
			void end() {
				closesocket(sock);
				WSACleanup();
			}
		};
		/*client�p�N���X(IPV4)*/
		class client {
		private:
			bool started = false;
			WSADATA wsaData;
			struct sockaddr_in server;
			SOCKET sock;
			sanae::str data;
		public:
			//���������܂�
			client() {
				started = true;
				int error=WSAStartup(MAKEWORD(2, 0), &wsaData);
				if (error!=0) {
					printf("Message:ERROR\nCode:%d\n",error);
					exit(0);
				}
				sock = socket(AF_INET, SOCK_STREAM, 0);
				server.sin_family = AF_INET;
			}
			~client() {
				this->end();
			}
			//�ڑ����܂�
			void connect_tcp(const char* ipaddr, u_short port) {
				server.sin_port = htons(port);
				size_t ret;
				const size_t cSize = strlen(ipaddr) + 1;
				wchar_t* wc = new wchar_t[cSize];
				mbstowcs_s(&ret, wc, cSize, ipaddr, _TRUNCATE);
				InetPton(AF_INET, wc, &server.sin_addr.S_un.S_addr);
				connect(sock, (struct sockaddr*)&server, sizeof(server));
			}
			//��M���܂�
			sanae::str recv_tcp(size_t datasize) {
				data.secure(datasize);
				int n = recv(sock, data, datasize, 0);
				return data;
			}
			//���M���܂�
			void send_tcp(const char* data) {
				send(sock, data, strlen(data) + 1, 0);
			}
			//�I�����܂�
			void end() {
				WSACleanup();
			}
		};
	}
}
#endif
#endif