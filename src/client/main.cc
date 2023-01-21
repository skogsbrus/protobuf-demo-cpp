#include <stdio.h>
#include <unistd.h>

#include <string>
#include <zmq.hpp>

#include "message.pb.h"

int main(int argc, char** argv) {
    zmq::context_t context{1};
    zmq::socket_t socket{context, zmq::socket_type::req};

    socket.connect("tcp://127.0.0.1:5555");

    const std::string data{"ping"};
    uint64_t id = 0;
    for (;; id++) {
        pb_demo::Payload payload;
        payload.set_id(id);
        payload.set_data(data);

        socket.send(zmq::buffer(payload.SerializeAsString()),
                    zmq::send_flags::none);


        // Wait for ACK before next message
        zmq::message_t reply{};
        socket.recv(reply, zmq::recv_flags::none);
        sleep(1);
    }
}
