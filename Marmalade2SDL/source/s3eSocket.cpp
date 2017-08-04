#pragma once
#include "s3eSocket.h"
#include <s3e.h>
#include <SDL_net.h>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <memory>
#include <string>
#include <string.h>
#include <list>

std::list<s3eSocket> sockets;

int32_t s3eSocketGetInt(s3eSocketProperty socketProperty) //TODO
{
	return int32_t();
}

s3eResult s3eSocketSetOpt(s3eSocket * s, s3eSocketOption opt, void * value, int valueLen) //TODO
{
	return s3eResult();
}

s3eResult s3eSocketGetOpt(s3eSocket * s, s3eSocketOption opt, void * out, int * outLen) //TODO
{
	return s3eResult();
}

const char * s3eSocketGetString(s3eSocketProperty socketProperty) //TODO
{
	return nullptr;
}

s3eSocketErrors s3eSocketGetError()
{
	s3eSocketError temp = socketError;
	socketError = S3E_SOCKET_ERR_NONE;
	return temp;
}

const char * s3eSocketGetErrorString() //TODO
{
	return nullptr;
}

s3eResult s3eInetAton(s3eInetIPAddress * result, const char * addr) //TODO
{
	return S3E_RESULT_ERROR;
}

s3eResult s3eInetPton(const char * addr, void * buf, int * len) //Not Tested
{
	if (strpbrk(addr, ".") == 0)
	{
		//IPv4 address
		uint32_t characterCount = 0;

		while (addr[characterCount] != '\0')
		{
			characterCount++;
		}
		characterCount++;

		if (characterCount == 1)
		{
			return S3E_RESULT_ERROR;
		}

		std::unique_ptr<char> modifiableAddr(new char[characterCount]);

		for (uint32_t i = 0; i < characterCount; i++)
		{
			modifiableAddr.get()[i] = addr[i];
		}

		std::vector<char*> partsOfAddr;
		char * part;

		part = strtok(modifiableAddr.get(), ".");
		while (part != NULL)
		{
			partsOfAddr.push_back(part);
			part = strtok(NULL, ".");
		}

		if (partsOfAddr.size() > 4)
		{
			return S3E_RESULT_ERROR;
		}

		uint8_t parts[4] = { static_cast<uint8_t>(std::strtoul(partsOfAddr.data()[0], NULL, 0)),
							 static_cast<uint8_t>(std::strtoul(partsOfAddr.data()[1], NULL, 0)),
							 static_cast<uint8_t>(std::strtoul(partsOfAddr.data()[2], NULL, 0)),
							 static_cast<uint8_t>(std::strtoul(partsOfAddr.data()[3], NULL, 0)) };
		
		memcpy(buf, parts, 4);

		return S3E_RESULT_SUCCESS;
		
	}
	else if (strpbrk(addr, ":") == 0)
	{
		//IPv6 address
		return S3E_RESULT_ERROR;
	}

	return S3E_RESULT_ERROR;
}

uint32_t s3eInetNtohl(uint32_t addr) //TODO
{
	return uint32_t();
}

uint32_t s3eInetHtonl(uint32_t addr) //TODO
{
	return uint32_t();
}

uint16_t s3eInetNtohs(uint16_t addr) //TODO
{
	return uint16_t();
}

uint16_t s3eInetHtons(uint16_t addr)
{
	uint8_t data[2];
	memcpy(data, &addr, 2);

	uint8_t temp = data[0];
	data[0] = data[1];
	data[1] = temp;

	uint16_t returnAddr;
	memcpy(&returnAddr, data, 2);

	return returnAddr;
}

char * s3eInetNtoa(s3eInetIPAddress addr, char * buf, int len) //TODO
{
	return nullptr;
}

s3eResult s3eInetNtop(s3eSocketAddrType addressType, const void * addr, char * dst, int cnt) //TODO
{
	return s3eResult();
}

const char * s3eInetToString(const s3eInetAddress * s, s3eBool port) //TODO
{
	return nullptr;
}

s3eResult s3eInetLookup(const char * hostname, s3eInetAddress * addr, s3eCallback func, void * userData, s3eSocketDomain famHint, int maxIPs)
{
	if (func == NULL)
	{
		IPaddress address;
		if (SDLNet_ResolveHost(&address, hostname, 53151) == 0)
		{
			addr->m_IPAddress = address.host;
			return S3E_RESULT_SUCCESS;
		}
		else
		{
			socketError = S3E_SOCKET_ERR_UNKNOWN_HOST;
			return S3E_RESULT_ERROR;
		}
	}
	else
	{
		return S3E_RESULT_ERROR;
	}
}

void s3eInetAddrFree(s3eInetAddress * head) //TODO
{
}

void s3eInetLookupCancel() //TODO
{
}

s3eSocket * s3eSocketCreate(s3eSocketType type, int domain)
{
	sockets.emplace_back();
	s3eSocket * socket = &sockets.back();
	socket->type = type;
	socket->socketSet = SDLNet_AllocSocketSet(1);
	return socket;
}

s3eResult s3eSocketClose(s3eSocket * socket)
{
	if (socket->type == S3E_SOCKET_TCP)
	{
		SDLNet_TCP_Close(socket->tcpSocket);
		SDLNet_TCP_DelSocket(socket->socketSet, socket->tcpSocket);
		SDLNet_FreeSocketSet(socket->socketSet);
		sockets.remove(*socket);
		return S3E_RESULT_SUCCESS;
	} 
	else
	{
		socketError = S3E_SOCKET_ERR_PARAM;
		return S3E_RESULT_ERROR;
	}
}

s3eResult s3eSocketBind(s3eSocket * sock, const s3eInetAddress * addr, uint8_t reuseAddress) //TODO
{
	return s3eResult();
}

s3eResult s3eSocketGetLocalName(s3eSocket * sock, s3eInetAddress * addr) //TODO
{
	return s3eResult();
}

s3eResult s3eSocketGetPeerName(s3eSocket * sock, s3eInetAddress * addr) //TODO
{
	return s3eResult();
}

s3eResult s3eSocketConnect(s3eSocket * sock, const s3eInetAddress * addr, s3eSocketCallbackFn func, void * userdata)
{
	IPaddress address;
	address.host = addr->m_IPAddress;
	address.port = addr->m_Port;
	
	if (sock->type == S3E_SOCKET_TCP)
	{
		sock->tcpSocket = SDLNet_TCP_Open(&address);
		const char * error = SDLNet_GetError();

		if (sock->tcpSocket == NULL)
		{
			socketError = S3E_SOCKET_ERR_CONNREFUSED;
			return S3E_RESULT_ERROR;
		}
		else
		{
			int error = SDLNet_TCP_AddSocket(sock->socketSet, sock->tcpSocket);
			if (error > 0)
			{
				std::string output = "Connected with " + std::to_string(address.host) + ":" + std::to_string(address.port);
				s3eDebugTracePrintf(output.c_str());
				s3eResult result = S3E_RESULT_SUCCESS;
				func(sock, &result, userdata);
				return S3E_RESULT_SUCCESS;
			}
			else
			{
				socketError = S3E_SOCKET_ERR_CONNREFUSED;
				SDLNet_TCP_Close(sock->tcpSocket);
				return S3E_RESULT_ERROR;
			}
		}
	}
	else
	{
		socketError = S3E_SOCKET_ERR_PARAM;
		return S3E_RESULT_ERROR;
	}
}

size_t s3eSocketSend(s3eSocket * sock, const char * buf, size_t len, int flags)
{
	if (sock->type == S3E_SOCKET_TCP)
	{
		size_t result = SDLNet_TCP_Send(sock->tcpSocket, (void*)buf, len);
		
		if (result == 0)
		{
			socketError = S3E_SOCKET_ERR_NOTCONN;
			SDLNet_TCP_Close(sock->tcpSocket);
			return -1;
		}
		else 
		{
			std::string output = "Sent: " + std::string(buf);
			//s3eDebugTracePrintf(output.c_str());
			return result;
		}
	}
	else
	{
		socketError = S3E_SOCKET_ERR_PARAM;
		return -1;
	}
}

size_t s3eSocketRecv(s3eSocket * sock, char * buf, size_t len, int flags)
{
	if (sock && sock->type == S3E_SOCKET_TCP)
	{
		if (sock->socketSet) {
			
			int activeSockets = SDLNet_CheckSockets(sock->socketSet, 5000);
			const char * error = SDLNet_GetError();
		
			if (activeSockets != 0)
			{
				if (SDLNet_SocketReady(sock->tcpSocket) != 0)
				{
					int testReturn = SDLNet_TCP_Recv(sock->tcpSocket, (void*)buf, len);
					//std::string output = "Received: " + std::string(buf);
					//s3eDebugTracePrintf(output.c_str());
					return testReturn;
				}
			}
		}
	}
	else if (sock != nullptr)
	{
		socketError = S3E_SOCKET_ERR_PARAM;
		SDLNet_TCP_Close(sock->tcpSocket);
		return -1;
	}
	
	socketError = S3E_SOCKET_ERR_WOULDBLOCK;
	return -1;
}

size_t s3eSocketRecvFrom(s3eSocket * s, char * buf, size_t len, int flags, s3eInetAddress * from) //TODO
{
	return size_t();
}

size_t s3eSocketSendTo(s3eSocket * s, const char * buf, size_t len, int flags, const s3eInetAddress * to) //TODO
{
	return size_t();
}

s3eResult s3eSocketListen(s3eSocket * s, uint16_t backlog) //TODO
{
	return s3eResult();
}

s3eSocket * s3eSocketAccept(s3eSocket * s, s3eInetAddress * addr, s3eSocketCallbackFn callback, void * userdata) //TODO
{
	return nullptr;
}

s3eResult s3eSocketReadable(s3eSocket * s, s3eSocketCallbackFn readable, void * userData) //TODO
{
	return s3eResult();
}

s3eResult s3eSocketWritable(s3eSocket * s, s3eSocketCallbackFn writable, void * data) //TODO
{
	return s3eResult();
}
