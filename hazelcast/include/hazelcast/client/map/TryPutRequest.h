//
// Created by sancar koyunlu on 5/23/13.
// Copyright (c) 2013 hazelcast. All rights reserved.
#ifndef HAZELCAST_MAP_TRY_PUT_REQUEST
#define HAZELCAST_MAP_TRY_PUT_REQUEST

#include "hazelcast/client/impl/ClientRequest.h"
#include "hazelcast/client/serialization/pimpl/Data.h"
#include <string>

namespace hazelcast {
    namespace client {
        namespace map {
            class HAZELCAST_API TryPutRequest : public impl::ClientRequest {
            public:
                TryPutRequest(const std::string &name, serialization::pimpl::Data &key, serialization::pimpl::Data &value, long threadId, long timeout);

                int getFactoryId() const;

                int getClassId() const;

                void write(serialization::PortableWriter &writer) const;

            private:
                std::string name;
                serialization::pimpl::Data key;
                serialization::pimpl::Data value;
                long threadId;
                long ttl;
                long timeout;
                bool async;
            };
        }
    }
}

#endif //HAZELCAST_MAP_PUT_REQUEST

