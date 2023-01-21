#include <inttypes.h>
#include <stdio.h>

#include <iostream>
#include <string>
#include <zmq.hpp>

#include <unistd.h>

#include "message.pb.h"

int main(int argc, char** argv) {
    zmq::context_t context{1};
    zmq::socket_t socket{context, zmq::socket_type::rep};

    socket.bind("tcp://127.0.0.1:5555");

    printf("Listening ...\n");
    for (;;) {
        zmq::message_t request;

        socket.recv(request, zmq::recv_flags::none);

        // ZMQ requires receiver to ACK a message
        // before sender can send next message
        socket.send(zmq::buffer("ACK"), zmq::send_flags::none);

        std::string req = request.to_string();

        pb_demo::Payload payload;
        payload.ParseFromString(request.to_string());

        std::cout << "Received message with ID " << payload.id() << ": "
                  << payload.data() << "\n";
    }

    return 0;
}
