#ifndef BASE_RCON_H
#define BASE_RCON_H

#include "tier1/NetAdr.h"
#include "tier2/socketcreator.h"
#include "protobuf/message_lite.h"

class CNetConBase
{
public:
	CNetConBase(void)
	{}

	virtual bool Encode(google::protobuf::MessageLite* pMsg, char* pMsgBuf, size_t nMsgLen) const;
	virtual bool Decode(google::protobuf::MessageLite* pMsg, const char* pMsgBuf, size_t nMsgLen) const;

	virtual bool Connect(const char* pHostAdr, const int nHostPort = -1);
	virtual void Disconnect(const char* szReason = nullptr) { NOTE_UNUSED(szReason); };

	virtual bool Send(const SocketHandle_t hSocket, const char* pMsgBuf, int nMsgLen) const;
	virtual void Recv(CConnectedNetConsoleData* pData, const int nMaxLen = -1);

	virtual bool ProcessBuffer(CConnectedNetConsoleData* pData, const char* pRecvBuf, int nRecvLen, int nMaxLen = -1);
	virtual bool ProcessMessage(const char* /*pMsgBuf*/, int /*nMsgLen*/) { return true; };

	CSocketCreator* GetSocketCreator(void) { return &m_Socket; }
	netadr_t* GetNetAddress(void) { return &m_Address; }

protected:
	CSocketCreator m_Socket;
	netadr_t m_Address;
};

#endif // BASE_RCON_H