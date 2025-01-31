#define MS_CLASS "RTC::UdpSocket"
// #define MS_LOG_DEV

#include "RTC/UdpSocket.hpp"
#include "Logger.hpp"
#include "RTC/PortManager.hpp"
#include <string>

namespace RTC
{
	/* Instance methods. */

	UdpSocket::UdpSocket(Listener* listener, std::string& ip)
	  : // This may throw.
	    ::UdpSocket::UdpSocket(PortManager::BindUdp(ip)), listener(listener)
	{
		MS_TRACE();
	}

	UdpSocket::~UdpSocket()
	{
		MS_TRACE();

		PortManager::UnbindUdp(this->localIp, this->localPort);
	}

	void UdpSocket::UserOnUdpDatagramRecv(const uint8_t* data, size_t len, const struct sockaddr* addr)
	{
		MS_TRACE();

		if (this->listener == nullptr)
		{
			MS_ERROR("no listener set");

			return;
		}

		// Notify the reader.
		this->listener->OnPacketRecv(this, data, len, addr);
	}
} // namespace RTC
