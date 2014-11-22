//
// Created by sancar koyunlu on 9/12/13.
// Copyright (c) 2013 hazelcast. All rights reserved.


#include "hazelcast/client/collection/CollectionCompareAndRemoveRequest.h"
#include "hazelcast/client/serialization/PortableWriter.h"
#include "hazelcast/client/collection/CollectionPortableHook.h"

namespace hazelcast {
    namespace client {
        namespace collection {
            CollectionCompareAndRemoveRequest::CollectionCompareAndRemoveRequest(const std::string& name, const std::string& serviceName, const std::vector<serialization::pimpl::Data>& valueSet, bool retain)
            : CollectionRequest(name, serviceName)
            , valueSet(valueSet)
            , retain(retain) {

            }

            int CollectionCompareAndRemoveRequest::getClassId() const {
                return CollectionPortableHook::COLLECTION_COMPARE_AND_REMOVE;
            }

            void CollectionCompareAndRemoveRequest::write(serialization::PortableWriter& writer) const {
                CollectionRequest::write(writer);
                writer.writeBoolean("r", retain);
                serialization::ObjectDataOutput& output = writer.getRawDataOutput();
                int size = valueSet.size();
                output.writeInt(size);
                for (int i = 0; i < size; i++) {
                    output.writeData(&(valueSet[i]));
                }

            }


        }
    }
}

