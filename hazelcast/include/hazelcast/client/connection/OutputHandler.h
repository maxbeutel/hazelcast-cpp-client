//
// Created by sancar koyunlu on 25/12/13.
//


#ifndef HAZELCAST_WriteHandler
#define HAZELCAST_WriteHandler

#include "hazelcast/util/ByteBuffer.h"
#include "hazelcast/util/ConcurrentQueue.h"
#include "hazelcast/client/connection/IOHandler.h"
#include <boost/atomic.hpp>

namespace hazelcast {
    namespace client {
        namespace serialization {
            class DataAdapter;

            class Data;
        }
        namespace connection {
            class Connection;

            class OListener;

            class ConnectionManager;

            class HAZELCAST_API OutputHandler : public IOHandler {
            public:
                OutputHandler(Connection &connection, OListener &oListener, int bufferSize);

                void handle();

                void enqueueData(const serialization::Data &data);

                void run();

            private:
                util::ByteBuffer buffer;
                util::ConcurrentQueue<serialization::DataAdapter> writeQueue;
                serialization::DataAdapter *lastData;
                bool initialized;
                bool ready;
                boost::atomic<bool> informSelector;


            };
        }
    }
}


#endif //HAZELCAST_WriteHandler