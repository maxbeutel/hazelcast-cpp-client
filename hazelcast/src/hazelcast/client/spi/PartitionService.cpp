//
// Created by sancar koyunlu on 6/3/13.
// Copyright (c) 2013 hazelcast. All rights reserved.


#include "hazelcast/client/Address.h"
#include "hazelcast/client/impl/GetPartitionsRequest.h"
#include "hazelcast/client/impl/PartitionsResponse.h"
#include "hazelcast/client/spi/PartitionService.h"
#include "hazelcast/client/spi/ClusterService.h"
#include <boost/thread.hpp>

namespace hazelcast {
    namespace client {
        namespace spi {
            PartitionService::PartitionService(ClusterService & clusterService, serialization::SerializationService & serializationService)
            :partitionCount(0)
            , clusterService(clusterService)
            , serializationService(serializationService) {

            };


            void PartitionService::start() {
                getInitialPartitions();
                boost::thread partitionListener(boost::bind(&PartitionService::runListener, this));
            };


            void PartitionService::refreshPartitions() {
                boost::thread partitionListener(boost::bind(&PartitionService::runRefresher, this));
            };

            Address *PartitionService::getPartitionOwner(int partitionId) {
                return partitions.get(partitionId);
            };

            int PartitionService::getPartitionId(serialization::Data & key) {
                const int pc = partitionCount;
                int hash = key.getPartitionHash();
                return (hash == INT_MIN) ? 0 : abs(hash) % pc;
            };


            void PartitionService::runListener() {
                while (true) {
                    boost::this_thread::sleep(boost::posix_time::seconds(10));
                    impl::PartitionsResponse partitionResponse;
                    auto_ptr<Address> ptr = clusterService.getMasterAddress();
                    if (ptr.get() == NULL) {
                        partitionResponse = getPartitionsFrom();
                    } else {
                        partitionResponse = getPartitionsFrom(*ptr.get());
                    }
                    if (!partitionResponse.isEmpty()) {
                        processPartitionResponse(partitionResponse);
                    }
                }
            };


            void PartitionService::runRefresher() {
                impl::PartitionsResponse partitionResponse;
                auto_ptr<Address> ptr = clusterService.getMasterAddress();
                if (ptr.get() == NULL) {
                    partitionResponse = getPartitionsFrom();
                } else {
                    partitionResponse = getPartitionsFrom(*ptr.get());
                }
                if (!partitionResponse.isEmpty()) {
                    processPartitionResponse(partitionResponse);
                }
            };

            impl::PartitionsResponse PartitionService::getPartitionsFrom(const Address  & address) {
                impl::GetPartitionsRequest getPartitionsRequest;
                impl::PartitionsResponse partitionResponse;
                try{
                    partitionResponse = clusterService.sendAndReceive<impl::PartitionsResponse>(address, getPartitionsRequest);
                }catch(exception::IOException& e){
                    std::cerr << e.what() << std::endl;
                }
                return partitionResponse;
            };


            impl::PartitionsResponse PartitionService::getPartitionsFrom() {
                impl::GetPartitionsRequest getPartitionsRequest;
                impl::PartitionsResponse partitionResponse;
                try{
                    partitionResponse = clusterService.sendAndReceive<impl::PartitionsResponse>(getPartitionsRequest);
                }catch(exception::IOException& e){
                    std::cerr << e.what() << std::endl;
                }
                return partitionResponse;
            }

            void PartitionService::processPartitionResponse(impl::PartitionsResponse & response) {
                vector<Address> members = response.getMembers();
                vector<int> ownerIndexes = response.getOwnerIndexes();
                if (partitionCount == 0) {
                    partitionCount = ownerIndexes.size();
                }
                for (int partitionId = 0; partitionId < partitionCount; ++partitionId) {
                    int ownerIndex = ownerIndexes[partitionId];
                    if (ownerIndex > -1) {
                        Address *address = new Address(members[ownerIndex]);
                        Address *pAddress = partitions.put(partitionId, address);
                        if (pAddress) delete pAddress;
                    }
                }
            };

            void PartitionService::getInitialPartitions() {
                vector<connection::Member> memberList = clusterService.getMemberList();
                for (vector<connection::Member>::iterator it = memberList.begin(); it < memberList.end(); ++it) {
                    Address target = (*it).getAddress();
                    impl::PartitionsResponse response = getPartitionsFrom(target);
                    if (!response.isEmpty()) {
                        processPartitionResponse(response);
                        return;
                    }
                }
                throw exception::IException("PartitionService::getInitialPartitions", " Cannot get initial partitions!");
            };


        }
    }
}