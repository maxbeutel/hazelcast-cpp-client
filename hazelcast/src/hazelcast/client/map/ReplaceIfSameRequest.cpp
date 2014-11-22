//
// Created by sancar koyunlu on 9/4/13.
// Copyright (c) 2013 hazelcast. All rights reserved.


#include "hazelcast/client/map/ReplaceIfSameRequest.h"
#include "hazelcast/client/map/PortableHook.h"
#include "hazelcast/client/serialization/PortableWriter.h"


namespace hazelcast {
    namespace client {
        namespace map {
            ReplaceIfSameRequest::ReplaceIfSameRequest(const std::string& name, const serialization::pimpl::Data& key, const serialization::pimpl::Data& testValue, const serialization::pimpl::Data& value, long threadId)
            : name(name)
            , key(key)
            , value(value)
            , testValue(testValue)
            , threadId(threadId) {

            }

            int ReplaceIfSameRequest::getFactoryId() const {
                return PortableHook::F_ID;
            }

            int ReplaceIfSameRequest::getClassId() const {
                return PortableHook::REPLACE_IF_SAME;
            }

            void ReplaceIfSameRequest::write(serialization::PortableWriter& writer) const {
                writer.writeUTF("n", name);
                writer.writeLong("t", threadId);
                writer.writeLong("ttl", -1);
                writer.writeBoolean("a", false);
                serialization::ObjectDataOutput& out = writer.getRawDataOutput();
                out.writeData(&key);
                out.writeData(&value);
                out.writeData(&testValue);
            }
        }
    }
}


