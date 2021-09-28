// Copied from gen-cpp/MultiplicationService_server.skeleton.cpp and implemented

#include "MultiplicationService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include <iostream>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using namespace  ::example;

class MultiplicationServiceHandler : virtual public MultiplicationServiceIf {
public:
    MultiplicationServiceHandler() {
        // Your initialization goes here
    }

    int32_t multiply(const int32_t n1, const int32_t n2) {
        std::cout << "Received request " << n1  << "*" << n2 << std::endl;
        auto result = n1 * n2;
        std::cout << "Sending back result " << result << std::endl;
        return result;
    }

};

int main(){
    int port = 9090;
    ::std::shared_ptr<MultiplicationServiceHandler> handler(new MultiplicationServiceHandler());
    ::std::shared_ptr<TProcessor> processor(new MultiplicationServiceProcessor(handler));
    ::std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
    ::std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    ::std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

    TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
    server.serve();
}

