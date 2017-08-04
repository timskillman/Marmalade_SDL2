#ifndef S3E_SOCKET_H
#define S3E_SOCKET_H

#define _CRT_SECURE_NO_WARNINGS 1
#include "SRGXTypes.h"
#include <SDL_net.h>

/**
* @addtogroup s3egroup
* @{
*/

/**
* @defgroup socketapigroup S3E Socket API Reference
*
* For more information on the Socket functionality provided by the S3E module,
* see the "S3E Socket Overview" section of the <em>S3E API Documentation</em>.
*
* @supported{
*             @platform{Android,android}
*             @platform{iOS,ios}
*             @platform{Mac OS X,mac}
*             @platform{Mac OS X Simulator,macsim}
*             @platform{Tizen,tizen}
*             @platform{Windows Desktop,windows}
*             @platform{Windows Desktop Simulator,windowssim}
*             @platform{Windows Phone 8,wp8}
*             @platform{Windows Phone 8.1,wp81}
*             @platform{Windows Store 8,ws8}
*             @platform{Windows Store 8.1,ws81}
*             @platform{Windows 10,win10}
*             @platform{NaCl,nacl}
* }
* @{
*/
#include "SRGXTypes.h"

/**
* Socket types to be passed into s3eSocketCreate.
* @see s3eSocketCreate
* @par Required Header Files
* s3eSocket.h
*/
typedef enum s3eSocketType
{
	S3E_SOCKET_TCP,
	S3E_SOCKET_UDP,
	S3E_SOCKET_RAW
} s3eSocketType;

/**
* Socket domains to be passed into s3eSocketCreate.
* @see s3eSocketCreate
* @par Required Header Files
* s3eSocket.h
*/
typedef enum s3eSocketDomain
{
	S3E_SOCKET_UNSPEC = 0, // Unspecified socket type
	S3E_SOCKET_LOCAL = 1,  // PF_LOCAL
	S3E_SOCKET_INET = 2,   // PF_INET (IPv4)
	S3E_SOCKET_INET6 = 30  // PF_INET6 (IPV6)
} s3eSocketDomain;

typedef enum s3eNetworkType
{
	S3E_NETWORK_TYPE_NONE = 0,
	S3E_NETWORK_TYPE_UNKNOWN = 1,
	S3E_NETWORK_TYPE_LAN = 2,
	S3E_NETWORK_TYPE_WLAN = 3,
	S3E_NETWORK_TYPE_GPRS = 4,
	S3E_NETWORK_TYPE_UMTS = 5,
	S3E_NETWORK_TYPE_EVDO = 6,
	S3E_NETWORK_TYPE_CDMA2000 = 7,
	S3E_NETWORK_TYPE_HSDPA = 8,
	S3E_NETWORK_TYPE_WIMAX = 9,
	S3E_NETWORK_TYPE_BLUETOOTH = 10,
	S3E_NETWORK_TYPE_EDGE = 11,
	S3E_NETWORK_TYPE_CDMA = 12,
	S3E_NETWORK_TYPE_IDEN = 13,
	S3E_NETWORK_TYPE_LTE = 14,
	S3E_NETWORK_TYPE_EHRPD = 15,
	S3E_NETWORK_TYPE_HSPAPLUS = 16,
	S3E_NETWORK_TYPE_EVDV = 17,
} s3eNetworkType;

/**
* Flags that can be passed to the send and/or recv functions.
*  <code>S3E_SOCKET_MORE</code>:   This flag acts as an indication to the send function that more data is
*                                  about to follow.  For TCP this should delay
*                                  the sending of the data packet pending a further
*                                  call to send.
* @see s3eSocketSend
* @see s3eSocketSendTo
*/
#define S3E_SOCKET_MORE (1 << 0)

/**
* Opaque struct representing a network socket.
*/
#ifndef S3E_SOCKET_DEFINED
#define S3E_SOCKET_DEFINED
typedef struct s3eSocket
{
	s3eSocketType type;
	SDLNet_SocketSet socketSet;
	TCPsocket tcpSocket;

	bool operator == (const s3eSocket& rhs) const
	{
		if (this->socketSet == rhs.socketSet && this->tcpSocket == rhs.tcpSocket && this->type == rhs.type)
		{
			return true;
		}
		else
		{
			return false;
		}

		return false;
	}

} s3eSocket;
#endif

/**
* The value of the first s3eSocket* handle.
* Historically s3eSocket pointers retured from the S3E API were actual pointers.
* Now they are actually integers starting at S3E_SOCKET_HANDLE_FIRST
*/
#define S3E_SOCKET_HANDLE_FIRST 3000

/**
* 32-bit IP address in network byte order.
*/
typedef uint32_t s3eInetIPAddress;

/**
* Address types to be passed into s3eSocketCreate.
* @see s3eSocketCreate
* @par Required Header Files
* s3eSocket.h
*/
typedef enum s3eSocketAddrType
{
	S3E_SOCKET_ADDR_UNRESOLVED = 0,
	S3E_SOCKET_ADDR_IPV4 = (1 << 0),
	S3E_SOCKET_ADDR_IPV6 = (1 << 1),
	S3E_SOCKET_ADDR_LOCAL = (1 << 2),
	S3E_SOCKET_ADDR_ANYIP = (S3E_SOCKET_ADDR_IPV4 | S3E_SOCKET_ADDR_IPV6)
} s3eSocketAddrType;


typedef uint8_t s3eInetIPv6Address[16];

/**
* Representation of Internet address.
* This is used in socket calls that require the
* specification of an address.  On systems that
* support local sockets both absolute and abstract
* local socket names are supported.
*
* @see s3eSocketBind, s3eSocketGetLocalName
* @par Required Header Files
* s3eSocket.h
*/
typedef struct s3eInetAddress
{
	/**Specifies address type. */
	s3eSocketAddrType m_Type;
	/** DEPRECATED - Indicates whether or not the address is a local UNIX socket. Deprecated - use m_Type */
	char             m_Local;
	/** Local socket name. */
	char             m_LocalAddress[128];
	/** Indicates whether or not local socket is abstract. */
	char             m_Abstract;
	/** 32-bit IPv4 address in network byte order */
	s3eInetIPAddress m_IPAddress;
	/** 128-bit IPv6 address in network byte order */
	s3eInetIPv6Address m_IPv6Address;
	/** 16-bit port number in network byte order */
	uint16_t           m_Port;
	/** DEPRECATED - The address as a human readable string. Deprecated - use s3eInetToString() */
	char             m_String[128];
	/* A next address in case of a linked list of addresses */
	struct s3eInetAddress*  m_Next;
} s3eInetAddress;

/**
* Socket Properties.
*  <code>S3E_SOCKET_MAX_SOCKETS</code>: indicates the maximum number of
*  sockets that the system
*  supports.
* @see s3eSocketGetInt
*/
typedef enum s3eSocketProperty
{
	/**
	* [read, int] the maximum number of sockets that the system  supports.
	*/
	S3E_SOCKET_MAX_SOCKETS,
	/**
	* [read, int] 1 if the networking is currently available, 0 if not.
	*/
	S3E_SOCKET_NETWORK_AVAILABLE,
	/**
	* [read, int] the current network type, if known
	*/
	S3E_SOCKET_NETWORK_TYPE,
	/**
	* [read, string] the domain name the device is in, if any.
	*/
	S3E_SOCKET_DOMAINNAME,
	/**
	* [read, string] the hostname of the device, if any.
	*/
	S3E_SOCKET_HOSTNAME,
	/**
	* [read, string] the proxy setup for the device, if any.
	*/
	S3E_SOCKET_HTTP_PROXY,
	/**
	* [read, int] 1 if the UDP is currently available over the network connection, 0 if not.
	*/
	S3E_SOCKET_UDP_AVAILABLE
} s3eSocketProperty;


typedef enum s3eSocketOption
{
	/**
	* Enable/disable the nagle algorithm and send all TCP data right away.
	* This property can be either 1 or 0. A 4 byte value should be passed to
	* s3eSocketSetOpt/s3eSocketGetOpt.
	*/
	S3E_SOCKET_NODELAY = 1,

	/**
	* Enable/disable TCP keepalive packets.  If enabled then keepalive packets
	* are sent after long periods (normally several hours) of inactivity.
	* This property can be either 1 or 0.
	* A 4 byte value should be passed to s3eSocketSetOpt/s3eSocketGetOpt.
	*/
	S3E_SOCKET_KEEPALIVE = 2,

	/**
	* Enable/disable UDP broadcasts.  When enabled the socket will have
	* the ability to send packets to the address 255.255.255.255.
	* This property can be either 1 or 0.
	* A 4 byte value should be passed to s3eSocketSetOpt/s3eSocketGetOpt.
	*/
	S3E_SOCKET_BROADCAST = 3,

	/**
	* Join multicast group.  When set the socket will have
	* the ability to receive UDP packets from the multicast
	* group specified.
	* An 8 byte value should be passed to s3eSocketSetOpt.
	* The first 4 bytes are the IP multicast address of the desired group.
	* The second 4 bytes are the local IP address of the local interface,
	* which should be set to 0.
	*/
	S3E_SOCKET_ADD_MEMBERSHIP = 4,

	/**
	* Leave multicast group.  When set the socket will no longer
	* have the ability to receive UDP packets from the multicast
	* group specified.
	* An 8 byte value should be passed to s3eSocketSetOpt.
	* The first 4 bytes are the IP multicast address of the desired group.
	* If these are zero, all multicast groups associated with the socket
	* will be dropped.
	* The second 4 bytes are the local IP address of the local interface,
	* which should be set to 0.
	*/
	S3E_SOCKET_DROP_MEMBERSHIP = 5,

	/**
	* If @ref s3eSocketSetOpt is called with this option and value
	* set to 1 then it will prevent sockets from generating the
	* SIG_PIPE signal when writing to a socket with no reader. Instead
	* s3eSocketGetError() will return S3E_SOCKET_ERR_SHUTDOWN. This is
	* equivalent to calling the BSD function setsockopt with SO_NOSIGPIPE.
	* This property can be either 1 or 0.
	* A 4 byte value should be passed to s3eSocketSetOpt/s3eSocketGetOpt.
	*
	* @supported{
	*             @platform{iOS,ios}
	*             @platform{Mac OS X,mac}
	* }
	*
	*/
	S3E_SOCKET_NOSIGPIPE = 6

} s3eSocketOption;

/**
* Retrieves an integer property for this subdevice.
* @param socketProperty property to get.
* @return
* - The value of the requested property if property is valid.
* - -1 otherwise.\n
*         Call s3eSocketGetError() to retrieve an error code.
*         This will return:
*   - @ref S3E_SOCKET_ERR_PARAM if @e socketProperty is not valid.
* @see s3eSocketGetString
* @par Required Header Files
* s3eSocket.h
*/
int32_t s3eSocketGetInt(s3eSocketProperty socketProperty);

/**
* Set a socket option for a particular socket.
* @param opt Option to set
* @param value [in] Pointer to value data
* @param valueLen Length of value data
* @return
* - S3E_RESULT_SUCCESS on success.
* - S3E_RESULT_ERROR otherwise.\n
*         Call s3eSocketGetError() to retrieve an error code.
*         This will return:
*   - @ref S3E_SOCKET_ERR_PARAM if @e opt is invalid, value is NULL or valueLen is 0.
*   - @ref S3E_SOCKET_ERR_UNSUPPORTED if the requested option is not supported
*/
s3eResult s3eSocketSetOpt(s3eSocket* s, s3eSocketOption opt, void* value, int valueLen);

/**
* Get a socket option for a particular socket.
* @param opt Option to get
* @param out [out] Pointer to area to write value data
* @param outLen [in, out] On input, pointer to length of @e out in bytes. On output, the
* number of bytes stored to @e out will be written here.
* @return S3E_RESULT_SUCCESS on success.
* - S3E_RESULT_ERROR otherwise.\n
*         Call s3eSocketGetError() to retrieve an error code.
*         This will return:
*   - @ref S3E_SOCKET_ERR_PARAM if @e opt is invalid, out is NULL, outLen is NULL or *outLen is 0
*   - @ref S3E_SOCKET_ERR_UNSUPPORTED if the requested option is not supported
*/
s3eResult s3eSocketGetOpt(s3eSocket* s, s3eSocketOption opt, void* out, int* outLen);

/**
* Retrieves a string property for this subdevice.
* @param S3E_SOCKET_DOMAINNAME the domain name the device is in, if any.
* @param S3E_SOCKET_HOSTNAME the hostname of the device, if any.
*   will return S3E_SOCKET_ERR_PARAM if @e socketProperty is not valid
* @see s3eSocketGetInt
* @par Required Header Files
* s3eSocket.h
*/
const char* s3eSocketGetString(s3eSocketProperty socketProperty);

/**
* Socket specific callback types.
* @param systemData callback-specific system supplied data.
* @param userData data supplied by user at callback registration.
* @par Required Header Files
* s3eSocket.h
*/
typedef int32_t(*s3eSocketCallbackFn)(s3eSocket* s, void* systemData, void* userData);

/**
* Socket Errors.
*
* @see s3eSocketGetError
* @see s3eSocketGetErrorString
* @par Required Header Files
* s3eSocket.h
*/
typedef enum s3eSocketError
{
	S3E_SOCKET_ERR_NONE = 0,    ///< No Error.
	S3E_SOCKET_ERR_PARAM = 1,    ///< Invalid parameter.
	S3E_SOCKET_ERR_TOO_MANY = 2,    ///< Maximum number of callbacks exceeded, or maximum number of sockets reached.
	S3E_SOCKET_ERR_ALREADY_REG = 3,    ///< The specified callback is already registered
	S3E_SOCKET_ERR_NOT_FOUND = 4,    ///< The specified callback was not found for removal
	S3E_SOCKET_ERR_UNAVAIL = 5,    ///< SOCKET is unavailable or feature is not supported.
	S3E_SOCKET_ERR_UNSUPPORTED = 7,    ///< The action requested is not supported

	S3E_SOCKET_ERR_WOULDBLOCK = 1000, ///< The operation would block, please try again later.
	S3E_SOCKET_ERR_INPROGRESS = 1001, ///< The operation is now in progress.
	S3E_SOCKET_ERR_ALREADY = 1002, ///< The operation was already in progress.
	S3E_SOCKET_ERR_NOTSOCK = 1003, ///< That object passed in is not a socket object.
	S3E_SOCKET_ERR_MSGSIZE = 1004, ///< The UDP message is to long for the underlying layer.
	S3E_SOCKET_ERR_ADDRINUSE = 1005, ///< The requested address is already in use.
	S3E_SOCKET_ERR_NETDOWN = 1006, ///< The network is down.
	S3E_SOCKET_ERR_CONNRESET = 1007, ///< The connection with the peer was reset.
	S3E_SOCKET_ERR_ISCONN = 1008, ///< The socket is connected and the requested operation requires an unconnected socket
	S3E_SOCKET_ERR_NOTCONN = 1009, ///< The socket is not connected and the requested operation requires a connected socket
	S3E_SOCKET_ERR_SHUTDOWN = 1010, ///< The socket has been shutdown.
	S3E_SOCKET_ERR_TIMEDOUT = 1011, ///< The requested operation timed out.
	S3E_SOCKET_ERR_CONNREFUSED = 1012, ///< The connection was refused.
	S3E_SOCKET_ERR_UNKNOWN_HOST = 1013, ///< The DNS system failed to lookup the hostname.
	S3E_SOCKET_ERR_NOTPERM = 1014  ///< THe operation is not permitted
} s3eSocketErrors;

#define S3E_SOCKET_ERR_AGAIN S3E_SOCKET_ERR_WOULDBLOCK
static s3eSocketError socketError = S3E_SOCKET_ERR_NONE;

/**
* Retrieves the last socket error, if any, for this subdevice.
* @see s3eSocketGetErrorString
*
* @remark Calling this function will retrieve the last error and then remove it
* from memory; therefore, any further calls to this function will not return
* an error unless a subsequent error has occurred.
*
* @par Required Header Files
* s3eSocket.h
*/
s3eSocketErrors s3eSocketGetError();

/**
* Retrieves the last error as a string, if any, for this subdevice. This is
* only available in debug builds.
* @see s3eSocketGetError
*
* @remark This function, as opposed to s3eSocketGetError(), will always return
* the last error no matter how many times it is called. This function should not be
* relied upon to indicate whether an error has just occurred.
*
* @par Required Header Files
* s3eSocket.h
*/
const char* s3eSocketGetErrorString();

/**
* Converts an IPv4 address in number-and-dots notation
* to a 32bit integer in network byte order.
*
* @return
* - @ref S3E_RESULT_SUCCESS if no error occurred.
* - @ref S3E_RESULT_ERROR if the string is not in valid number-and-dots
*         notation.
* @par Required Header Files
* s3eSocket.h
* @deprecated - use s3eInetPton for ipv4/ipv6 compatibility
*/
s3eResult s3eInetAton(s3eInetIPAddress* result, const char* addr);

/**
* Converts an IPv4/IPv6 address in number/dots/colon notation
* to a binary representation format (32/128bit in network byte order.
*
* @param addr the buffer to write to.
* @param type specifies the address type to be converted
* @param buf the buffer to write to.
* @param len the length of the address buffer and converted address.
* @return
* - @ref S3E_RESULT_SUCCESS if no error occurred.
* - @ref S3E_RESULT_ERROR if the address cannot be converted.
* @par Required Header Files
* s3eSocket.h
*/
s3eResult s3eInetPton(const char* addr, void* buf, int* len);

/**
* Converts a 32bit integer from network byte order
* to host byte order.
*
* @return The integer in host order.
* @par Required Header Files
* s3eSocket.h
*/
uint32_t s3eInetNtohl(uint32_t addr);

/**
* Converts a 32bit integer from host byte order
* to network byte order.
*
* @return The integer in network order.
* @par Required Header Files
* s3eSocket.h
*/
uint32_t s3eInetHtonl(uint32_t addr);

/**
* Converts a 16bit integer from network byte order
* to host byte order.
*
* @return The integer in host order.
* @par Required Header Files
* s3eSocket.h
*/
uint16_t s3eInetNtohs(uint16_t addr);

/**
* Converts a 16bit integer host byte order
* to network byte order.
*
* @return The integer in network order.
* @par Required Header Files
* s3eSocket.h
*/
uint16_t s3eInetHtons(uint16_t addr);

/**
* Converts a 32bit integer in network byte order into
* a string in standard numbers-and-dots notation.
* @param buf the buffer to write to.
* @param len the length of buf, in bytes.
* @return the buf pointer, if one was passed in, otherwise
* a pointer to a string allocated by s3eMalloc().  If buf
* is supplied and not long enough NULL is returned.
* @par Required Header Files
* s3eSocket.h
* @deprecated - use s3eInetNtop for ipv4/ipv6 compatibility
*/
char* s3eInetNtoa(s3eInetIPAddress addr, char* buf, int len);

/**
* Converts an IP address (usually 32bit ipv4 or 128bit
* ipv6 data structure in network byte order) into a string in
* presentation format suitable for display purposes.
* @param family specifies type of address
*               (S3E_SOCKET_AF_INET or S3E_SOCKET_AF_INET6)
* @param addr is the address to be converted
*             (usually 32b or 128b integer in network byte order)
* @param dst the buffer to write to.
* @param cnt the length of buf, in bytes.
* @return @ref S3E_RESULT_SUCCESS if no error occurred.
* - @ref S3E_RESULT_ERROR if the operation failed.
* @par Required Header Files
* s3eSocket.h
*/
s3eResult s3eInetNtop(s3eSocketAddrType addressType, const void *addr, char* dst, int cnt);

/**
* Convert an s3eInetAddress into string form.  The string
* returned is part of the s3eInetAddress structure so no
* allocation is needed.
* @param port specifies if to include the port number in the string
* @return the string representation of the address (ipv6 or ipv4)
*         empty string if unable to convert.
* @par Required Header Files
* s3eSocket.h
*/
const char* s3eInetToString(const s3eInetAddress* s, s3eBool port);

/**
* Initiates a DNS lookup.  This call can be synchronous or asynchronous,
* depending on the whether a callback function is provided. Only one lookup
* can be active at once. In case DNS resolved the hostname to mutliple IP
* addresses (ipv4/ipv6 o multi homed host) the function returns all
* results in linked list where addr is the first element. In that case
* it is necessary to deallocate the linked list after use using s3eInetAddrFree();
*
* @param hostname  The name to lookup.
* @param addr      The address structure to be filled in with the result.
* @param func      A callback function that is called back when the lookup is
*                  complete, or NULL if the operation is to be done
*                  synchronously.
* @param userData  Argument to func.
* @param famHint   s3eSocketDomain specifying application preference when resolving
*                  the name. S3E_SOCKET_UNSPEC if no preference.
*                  Defaults to S3E_SOCKET_INET for backward compatibility.
*                  Consider using S3E_SOCKET_UNSPEC for best interoperability
*                  in mixed ipv4/ipv6 environment
* @param maxIPs    Maximum number of IPs to return (in case DNS reply contains
*                  multiple entries for the host). Defaults to 1 for backward
*                  compatibility reasons. Set to 0 to return the amount of
*                  record resolved by DNS.
*
* - @ref S3E_RESULT_SUCCESS if no error occurred.
* - @ref S3E_RESULT_ERROR if the operation failed.\n
*   - @ref S3E_SOCKET_ERR_ALREADY if a lookup is already in progress.
*   - @ref S3E_SOCKET_ERR_UNKNOWN_HOST if host could not be found using DNS.
* @note The systemData passed to the callback registered with this function is
* a pointer to s3eInetAddress, and will be the same as the @a addr param passed
* into this function (which will have been filled in with the address) if
* the lookup succeeded, or NULL otherwise.
* @note In asynchronous mode this function will always return S3E_RESULT_SUCCESS.
* Failure will be notified through the registered callback.
*/
s3eResult s3eInetLookup(const char* hostname, s3eInetAddress* addr, s3eCallback func, void* userData, s3eSocketDomain famHint, int maxIPs);

/**
* Releases memory allocated in s3eInetLookup if addr contains linked
* list of addresses. Must be called when the list is no longer needed.
* @param addrs     Pointer s3eInetAddress structure (first element of the linked list)
* @note            Head of the linked list (address at addrs) itself is not deallocated.
*                  It is responsibility of the app to deallocate it.
* @see s3eInetLookup
*/
void s3eInetAddrFree(s3eInetAddress* head);

/**
* Cancel an outstanding lookup.
*/
void s3eInetLookupCancel();

/**
* Creates a new socket.
* @param type  The type of socket requested.
* @param domain The domain of socket requested (see s3eSocketDomain)
* @return
* - a valid pointer if no error occurred.
* - NULL if the operation failed. Call s3eSocketGetError() to
*   retrieve the error code.  This will return one of:
*   - @ref S3E_SOCKET_ERR_PARAM if the socket type given is not valid.
*   - @ref S3E_SOCKET_ERR_UNSUPPORTED if the socket type, or flags given
*      are are not supported on the current platform.
* @par Required Header Files
* s3eSocket.h
*/
s3eSocket* s3eSocketCreate(s3eSocketType type, int domain);

/**
* Closes a socket and frees all associated resources. Once this function
* returns, the socket handle is not longer valid.
* @param  socket  The socket to close and delete.
* @return
* - @ref S3E_RESULT_SUCCESS if no error occurred.
* - @ref S3E_RESULT_ERROR if the operation failed.\n
*         Call s3eSocketGetError() to retrieve the error code.
*   - @ref S3E_SOCKET_ERR_PARAM if the socket is not a valid socket handle.
* @par Required Header Files
* s3eSocket.h
*/
s3eResult s3eSocketClose(s3eSocket* socket);

/**
* Bind a socket to a particular local address.  If the address passed
* in to this function is NULL then the socket is bound to an arbitrary
* available port and address.  Likewise, if the port or ipaddress specified
* within the address is 0 then the socket is bound to an arbitrary free
* port or address respectively.
* If this function is not called prior to s3eSocketConnect(),
* s3eSocketListen() or s3eSocketSendTo() then the socket will be bound
* to an arbitrary free address upon calling one of these functions.
* @param sock          The socket to bind.
* @param addr          The address to bind to.
* @param reuseAddress  Pass non-zero uint8 to allow address reuse.
* @return
* - @ref S3E_RESULT_SUCCESS if no error occurred.
* - @ref S3E_RESULT_ERROR if the operation failed.\n
*         Call s3eSocketGetError() to retrieve the error code.
*   - @ref S3E_SOCKET_ERR_PARAM if the sock is not a valid socket handle,
*         or the socket is already bound, or the address requested does not
*         match any of the current device.
*   - @ref S3E_SOCKET_ERR_INPROGRESS if the bind operation is currently
*         active but has not yet completed.  Further calls to s3eSocketBind()
*         will return @ref S3E_SOCKET_ERR_INPROGRESS until the bind operation
*         has completed.
*   - @ref S3E_SOCKET_ERR_ADDRINUSE if the address is already bound to another
*         socket
* @see s3eSocketGetLocalName
* @par Required Header Files
* s3eSocket.h
*/
s3eResult s3eSocketBind(s3eSocket* sock, const s3eInetAddress* addr, uint8_t reuseAddress);

/**
* Get the local address of a socket.
* @param sock   The socket.
* @param addr   A pointer to an s3eInetAddress, which will be filled with the local
*               address of the socket.
* @return
* - @ref S3E_RESULT_SUCCESS if no error occurred.
* - @ref S3E_RESULT_ERROR if the operation failed.\n
*         Call s3eSocketGetError() to retrieve the error code.
*   - @ref S3E_SOCKET_ERR_PARAM if the sock is not a valid socket handle.
* @par Required Header Files
* s3eSocket.h
*/
s3eResult s3eSocketGetLocalName(s3eSocket* sock, s3eInetAddress* addr);

/**
* Get the address of the remote peer to which the socket is connected.
* This will only work for connected sockets.
* @param sock   The socket.
* @param addr   A pointer to an s3eInetAddress, which will be filled with the local
*               address of the socket.
* - @ref S3E_RESULT_SUCCESS if no error occurred.
* - @ref S3E_RESULT_ERROR if the operation failed.\n
*         Call s3eSocketGetError() to retrieve the error code.
*   - @ref S3E_SOCKET_ERR_PARAM if the sock is not a valid socket handle.
*/
s3eResult s3eSocketGetPeerName(s3eSocket* sock, s3eInetAddress* addr);

/**
* Connects a socket to a given peer. For TCP sockets this initiates
* the connection process (sends a SYN). For UDP sockets this allows
* s3eSocketSend() and s3eSocketRecv() to be called by binding to
* the given peer address. For TCP sockets the initial call to connect
* will generate @ref S3E_SOCKET_ERR_INPROGRESS, as will further calls until
* the operation completes at which point the actual error will be indicated
* or @ref S3E_SOCKET_ERR_ALREADY will be generated if the connection was
* successful. If a callback function is specified then it will be called
* once the connection operation completes. If the callback is called with
* S3E_RESULT_ERROR then s3eSocketGetError() can be used to retrieve the
* error code as usual.
* @param sock     The socket to connect.
* @param addr     The address to connect to.
* @param func     Function to be called on completion of the connect.
* @param userdata Parameter to be used when callback is called.
* @return
* - @ref S3E_RESULT_SUCCESS if no error occurred.
* - @ref S3E_RESULT_ERROR if the operation failed.\n
*         Call @ref s3eSocketGetError() to retrieve the error code.
*   - @ref S3E_SOCKET_ERR_PARAM if the socket is not a valid socket handle.
*   - @ref S3E_SOCKET_ERR_ALREADY if a connection operation is already in progress.
*   - @ref S3E_SOCKET_ERR_NETDOWN if there is no network connection available.
*   - @ref S3E_SOCKET_ERR_TIMEDOUT if the connection attempt timed out.
*   - @ref S3E_SOCKET_ERR_INPROGRESS if the connection operation is currently in progress.
*   - @ref S3E_SOCKET_ERR_CONNREFUSED if the connection was refused by the peer.
* @note The @a systemData passed to the callback registered with this function is
* a pointer to an s3eResult indicating whether the connection succeeded.
* @note It is not necessary to define a return value for any registered callback.
*
* @platnote{Windows Store 8, ws8}
* http://msdn.microsoft.com/en-us/library/windows/apps/hh452996.aspx
* Due to the network security system, you cannot connect to other applications running
* on the same machine. This means that you can only use "localhost" to connect to
* the same application (specifically, you can connect to a listener on the same machine
* running in the same app container)
* @endplatnote
*
* @platnote{Windows Store 8.1, ws81}
* http://msdn.microsoft.com/en-us/library/windows/apps/hh452996.aspx
* Due to the network security system, you cannot connect to other applications running
* on the same machine. This means that you can only use "localhost" to connect to
* the same application (specifically, you can connect to a listener on the same machine
* running in the same app container)
* @endplatnote
*/
s3eResult s3eSocketConnect(s3eSocket* sock, const s3eInetAddress* addr, s3eSocketCallbackFn func, void* userdata);

/**
* Sends data on a connected socket. s3eSocketConnect() must have been called
* before calling this function. If none of the data can be sent the function
* will return -1 and @ref S3E_SOCKET_ERR_WOULDBLOCK is set.
* In the case of failure s3eSocketGetError() can be used to retrieve error
* which will be one of the following:
*   - @ref S3E_SOCKET_ERR_PARAM if the sock is not a valid socket handle.
*   - @ref S3E_SOCKET_ERR_SHUTDOWN the peer shutdown the connection.
*   - @ref S3E_SOCKET_ERR_WOULDBLOCK there is currently no space in the output buffer.
*   - @ref S3E_SOCKET_ERR_NOTCONN the given socket is not connected.
*   - @ref S3E_SOCKET_ERR_MSGSIZE the socket type is UDP and the length of the
*       buffer exceeds the maximum UDP packet size.
* @param sock  The socket to use.
* @param buf   The data to send
* @param len   The number of bytes to send
* @param flags The bitwise OR of zero or more socket send flags.
* @return The number of bytes sent, or -1 on failure.
* @see s3eSocketConnect
*/
size_t s3eSocketSend(s3eSocket* sock, const char* buf, size_t len, int flags);

/**
* Receives data on a connected socket.
* s3eSocketConnect() must have been called before calling this function.  If
* no data is waiting, -1 will be returned and
* @ref S3E_SOCKET_ERR_WOULDBLOCK is set as the current error. In the case
* of failure s3eSocketGetError() can be used to retrieve error which will be
* one of the following:
*   - @ref S3E_SOCKET_ERR_PARAM if the sock is not a valid socket handle.
*   - @ref S3E_SOCKET_ERR_SHUTDOWN the peer shutdown the connection.
*   - @ref S3E_SOCKET_ERR_WOULDBLOCK there is currently no data available to be received.
*   - @ref S3E_SOCKET_ERR_NOTCONN the given socket is not connected.
* @param sock  the socket to receive data on.
* @param buf   pointer to a buffer to fill with data.
* @param len   the number of bytes to read.
* @param flags The bitwise OR of zero or more socket receive flags.
* @return number of bytes read from socket or -1 on failure.
* @see s3eSocketConnect
*/
size_t s3eSocketRecv(s3eSocket* sock, char* buf, size_t len, int flags);

/**
* Receives a datagram from an unconnected UDP socket.
* @param s the socket to receive data on.
* @param buf  pointer to a buffer to fill with data.
* @param len  the number of bytes to read.
* @param flags The bitwise OR of zero or more socket receive flags.
* @param from pointer to an address to be set to source address of the datagram.
* @return If no datagram is waiting -1 will be returned and
* @ref S3E_SOCKET_ERR_WOULDBLOCK is set as the current error on the
* socket.
* In the case of failure s3eSocketGetError() can be used to retrieve error
* which will be one of the following:
*   - @ref S3E_SOCKET_ERR_PARAM if @e s is not a valid socket handle, or the
*       socket is not bound.
*   - @ref S3E_SOCKET_ERR_WOULDBLOCK there is currently no data available to be received.
*   - @ref S3E_SOCKET_ERR_ISCONN the given socket is connected and s3eSocketRecv()
*       should therefore be used.
* @return the size in bytes of the datagram, or -1 on failure.
*/
size_t s3eSocketRecvFrom(s3eSocket* s, char* buf, size_t len, int flags, s3eInetAddress* from);

/**
* Sends a datagram on an unconnected UDP socket.
* If the datagram cannot be currently be sent, -1 will be returned and
* @ref S3E_SOCKET_ERR_WOULDBLOCK is set as the current error on the
* socket.   If the socket is not already bound when this function
* is first called it will be bound to an arbitrary local address
* automatically before sending any data.
*
* @param s The socket to receive data on.
* @param buf  A Pointer to the datagram which to send.
* @param len  The length of the datagram.
* @param flags The bitwise OR of zero or more socket send flags.
* @param to The address send the datagram to.
* @return the number of bytes sent if no error occurred, or -1 on failure.
*   s3eSocketGetError() can be used to retrieve error which will be one
*   of the following:
*     - @ref S3E_SOCKET_ERR_PARAM @e s is not a valid socket handle.
*     - @ref S3E_SOCKET_ERR_WOULDBLOCK there is currently no space in the output buffer.
*     - @ref S3E_SOCKET_ERR_ISCONN the given socket is connected and s3eSocketSend()
*       should therefore be used.
*     - @ref S3E_SOCKET_ERR_MSGSIZE the length of the buffer exceeds the
*       maximum UDP packet size.
*/
size_t s3eSocketSendTo(s3eSocket* s, const char* buf, size_t len, int flags, const s3eInetAddress* to);

/**
* Puts a socket in a state where it is listening for an incoming connection.
*
* @param s A bound, unconnected socket.
* @param backlog  The maximum length of the queue of pending connections.
* @return
* - @ref S3E_RESULT_SUCCESS if no error occurred.
* - @ref S3E_RESULT_ERROR if the operation failed.\n
*         Call s3eSocketGetError() to retrieve the error code.
*   - @ref S3E_SOCKET_ERR_PARAM if the socket is not a valid socket handle, or
*         the socket is not bound.
*   - @ref S3E_SOCKET_ERR_ADDRINUSE if another socket is already listening on
*         address s is bound to.
*   - @ref S3E_SOCKET_ERR_UNSUPPORTED if listening sockets are not supported by
*         the system.
* @par Required Header Files
* s3eSocket.h
*
* @platnote{Windows Store 8, ws8}
* http://msdn.microsoft.com/en-us/library/windows/apps/hh452996.aspx
* Due to the network security system, you cannot connect to other applications running
* on the same machine. This means that you can only use "localhost" to connect to
* the same application (specifically, you can connect to a listener on the same machine
* running in the same app container)
* @endplatnote
*
* @platnote{Windows Store 8.1, ws81}
* http://msdn.microsoft.com/en-us/library/windows/apps/hh452996.aspx
* Due to the network security system, you cannot connect to other applications running
* on the same machine. This means that you can only use "localhost" to connect to
* the same application (specifically, you can connect to a listener on the same machine
* running in the same app container)
* @endplatnote
*/
s3eResult s3eSocketListen(s3eSocket* s, uint16_t backlog);

/**
* Accepts an incoming connection attempt on a socket.
* @param s The socket which is in a listening state.
* @param addr [out] The network address of the connecting entity. This may be NULL.
* @param userdata Userdata to associate with callbacks.
* @param callback Function to called when the operation completes.  This may be NULL and is
* only used when this function returns NULL and sets the S3E_SOCKET_ERR_WOULDBLOCK error.  The
* callback is invoked when a new connection arrived and a subsequent call to s3eSocketAccept would
* then succeed.  The system data passed to the callback is NULL.
* @return On success, a new s3eSocket handle for the connection, otherwise s3eSocketAccept() returns NULL
* - @ref S3E_RESULT_SUCCESS if no error occurred.
* - @ref S3E_RESULT_ERROR if the operation failed.\n
*         Call s3eSocketGetError() to retrieve the error code.
*   - @ref S3E_SOCKET_ERR_WOULDBLOCK there are no new connections waiting to be accepted.
*   - @ref S3E_SOCKET_ERR_PARAM if @e s is not a valid socket handle, or
*         the @e s is not a listening socket.
* @par Required Header Files
* s3eSocket.h
*/
s3eSocket* s3eSocketAccept(s3eSocket* s, s3eInetAddress* addr, s3eSocketCallbackFn callback, void* userdata);

/**
* Schedule a callback to be called when the socket becomes readable. This is a
* one-shot callback.  Setting to NULL will cancel any existing callback.
* @param s The Socket.
* @param readable Callback. The systemData passed to this callback will be of
* type s3eSocket*, and will be equal to @e s. The @e userData passed to the
* callback
* will be the @e userData passed here
* @param userData callback parameter.
* @par Required Header Files
* s3eSocket.h
*/
s3eResult s3eSocketReadable(s3eSocket* s, s3eSocketCallbackFn readable, void* userData);

/**
* Schedule a callback to be called when the socket becomes writable. This is a
* one-shot callback. Setting to NULL will cancel any existing callback.
* @param s The Socket.
* @param writable Callback. The systemData passed to this callback will be of
* type s3eSocket*, and will be equal to @e s. the @e userData passed to the
* callback will be the @e data passed here.
* @param data Callback parameter.
* @par Required Header Files
* s3eSocket.h
*/
s3eResult s3eSocketWritable(s3eSocket* s, s3eSocketCallbackFn writable, void* data);

/** @} */
/** @} */

#endif /* !S3E_SOCKET_H */
