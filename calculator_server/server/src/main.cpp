#include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include <iostream>
#include <stdexcept>

#include "lib_calculator_api/generated/Calculator.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::concurrency;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

using namespace tutorial;

class CalculatorHandler : public CalculatorIf {
public:
    CalculatorHandler() {}

    void ping() {
        cout << "ping()" << endl;
    }

    int32_t add(const int32_t n1, const int32_t n2) {
        cout << "add(" << n1 << ", " << n2 << ")" << endl;
        return n1 + n2;
    }

    int32_t calculate(const Work& work) {
        cout << "calculate(" << work << ")" << endl;
        int32_t val;

        switch (work.op) {
        case Operation::ADD:
            val = work.num1 + work.num2;
            break;
        case Operation::SUBTRACT:
            val = work.num1 - work.num2;
            break;
        case Operation::MULTIPLY:
            val = work.num1 * work.num2;
            break;
        case Operation::DIVIDE:
            if (work.num2 == 0) {
                InvalidOperation io;
                io.whatOp = work.op;
                io.why = "Cannot divide by 0";
                throw io;
            }
            val = work.num1 / work.num2;
            break;
        default:
            InvalidOperation io;
            io.whatOp = work.op;
            io.why = "Invalid Operation";
            throw io;
        }

        return val;
    }
};

int main() {
    boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
    boost::shared_ptr<CalculatorHandler> handler(new CalculatorHandler());
    boost::shared_ptr<TProcessor> processor(new CalculatorProcessor(handler));
    boost::shared_ptr<TServerTransport> serverTransport(new TServerSocket(9098));
    boost::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());

    TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);

    cout << "Starting the server..." << endl;
    server.serve();
    cout << "Done." << endl;
    return 0;
}