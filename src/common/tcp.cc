/* tcp.cc
   Mathieu Stefani, 05 novembre 2015

   TCP
*/

#include <pistache/tcp.h>
#include <pistache/peer.h>

namespace Pistache {
namespace Tcp {

Handler::Handler()
    : transport_(nullptr)
{ }

Handler::~Handler()
{ }

void
Handler::associateTransport(Transport* transport) {
    transport_ = transport;
}

void
Handler::onConnection(const std::shared_ptr<Tcp::Peer>&) {
}

void
Handler::onDisconnection(const std::shared_ptr<Tcp::Peer>&) {
}

} // namespace Tcp
} // namespace Pistache
