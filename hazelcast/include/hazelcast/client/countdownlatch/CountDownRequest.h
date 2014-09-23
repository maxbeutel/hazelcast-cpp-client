//
// Created by sancar koyunlu on 6/25/13.
// Copyright (c) 2013 hazelcast. All rights reserved.



#ifndef HAZELCAST_CountDownRequest
#define HAZELCAST_CountDownRequest


#include "hazelcast/client/impl/ClientRequest.h"
#include <string>

namespace hazelcast {
    namespace client {
        namespace serialization{
            class PortableWriter;
        }

        namespace countdownlatch {
            class HAZELCAST_API CountDownRequest : public impl::ClientRequest {
            public:
                CountDownRequest(const std::string& instanceName);

                int getFactoryId() const;

                int getClassId() const;

                void write(serialization::PortableWriter& writer) const;

            private:

                std::string instanceName;
            };
        }
    }
}
#endif //HAZELCAST_CountDownRequest

