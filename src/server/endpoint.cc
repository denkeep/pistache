/* endpoint.cc
   Mathieu Stefani, 22 janvier 2016

   Implementation of the http endpoint
*/


#include <pistache/endpoint.h>
#include <pistache/tcp.h>
#include <pistache/peer.h>

namespace Pistache {
namespace Http {

Endpoint::Options::Options()
    : threads_(1)
{ }

Endpoint::Options&
Endpoint::Options::threads(int val) {
    threads_ = val;
    return *this;
}

Endpoint::Options&
Endpoint::Options::flags(Flags<Tcp::Options> flags) {
    flags_ = flags;
    return *this;
}

Endpoint::Options&
Endpoint::Options::backlog(int val) {
    backlog_ = val;
    return *this;
}

Endpoint::Endpoint()
{ }

Endpoint::Endpoint(const Address& addr)
    : listener(addr)
{ }

void
Endpoint::init(const Endpoint::Options& options) {
    listener.init(options.threads_, options.flags_);
}

void
Endpoint::setHandler(const std::shared_ptr<Handler>& handler) {
    handler_ = handler;
}

void
Endpoint::bind() {
    listener.bind();
}

void
Endpoint::bind(const Address& addr) {
    listener.bind(addr);
}

void
Endpoint::serve()
{
    serveImpl(&Tcp::Listener::run);
}

void
Endpoint::serveThreaded()
{
    serveImpl(&Tcp::Listener::runThreaded);
}

void
Endpoint::shutdown()
{
    listener.shutdown();
}

void
Endpoint::useSSL(std::string cert, std::string key)
{
#ifndef PISTACHE_USE_SSL
    throw std::runtime_error("Pistache is not compiled with SSL support.");
#else
    listener.setupSSL(cert, key);
#endif /* PISTACHE_USE_SSL */
}

Async::Promise<Tcp::Listener::Load>
Endpoint::requestLoad(const Tcp::Listener::Load& old) {
    return listener.requestLoad(old);
}

Endpoint::Options
Endpoint::options() {
    return Options();
}

} // namespace Http
} // namespace Pistache
