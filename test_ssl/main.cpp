#include <pistache/endpoint.h>

using namespace Pistache;

struct HelloHandler : public Http::Handler {
    HTTP_PROTOTYPE(HelloHandler)

    void onRequest(const Http::Request& request, Http::ResponseWriter writer) {
        writer.send(Http::Code::Ok, "Hello, World!");
    }
};

int main(void) {
    Pistache::Address   addr;
    auto opts = Http::Endpoint::options().threads(1);

    addr = Pistache::Address(Pistache::Ipv4::any(), Pistache::Port(9080));

    Http::Endpoint server(addr);
    server.init(opts);
    server.setHandler(std::make_shared<HelloHandler>());
    server.useSSL("domain.crt", "domain.key");

    server.serve();
    return 0;
}
