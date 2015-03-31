//
// Created by sancar koyunlu on 5/10/13.
// Copyright (c) 2013 sancar koyunlu. All rights reserved.


#include <hazelcast/client/serialization/pimpl/Packet.h>
#include <hazelcast/client/exception/IllegalArgumentException.h>
#include "hazelcast/client/connection/InputSocketStream.h"
#include "hazelcast/client/serialization/pimpl/PortableContext.h"
#include "hazelcast/client/Socket.h"
#include "hazelcast/client/serialization/pimpl/Data.h"
#include "hazelcast/util/Bits.h"

namespace hazelcast {
    namespace client {
        namespace connection {

            InputSocketStream::InputSocketStream(Socket& socket)
            : socket(socket)
            , context(NULL) {
            }

            void InputSocketStream::setPortableContext(serialization::pimpl::PortableContext *context) {
                this->context = context;
            }

            void InputSocketStream::readFully(std::vector<byte>& bytes) {
                socket.receive(&(bytes[0]), bytes.size(), MSG_WAITALL);
            }

            int InputSocketStream::readInt() {
                byte s[4];
                socket.receive(s, sizeof(byte) * 4, MSG_WAITALL);
                return (0xff000000 & (s[0] << 24)) |
                (0x00ff0000 & (s[1] << 16)) |
                (0x0000ff00 & (s[2] << 8)) |
                (0x000000ff & s[3]);
            }


            int InputSocketStream::readShort() {
                byte s[2];
                socket.receive(s, sizeof(byte) * 2, MSG_WAITALL);
                return (0xff00 & (s[0] << 8)) |
                (0x00ff & s[1]);
            }


            int InputSocketStream::readByte() {
                byte s;
                socket.receive(&s, sizeof(byte), MSG_WAITALL);
                return s;
            }


            void InputSocketStream::readPacket(serialization::pimpl::Packet& packet) {
                int version = readByte();
                if(version != serialization::pimpl::Packet::VERSION){
                    std::stringstream stringstream;
                    stringstream << "Packet versions are not matching! This -> "
                    << serialization::pimpl::Packet::VERSION << ", Incoming -> " << version;
                    throw exception::IllegalArgumentException("Packet::readFrom", stringstream.str());
                }
                packet.setHeader(readShort());
                packet.setPartitionId(readInt());

                readValue(packet.getDataAsModifiable());
            }

            void InputSocketStream::readValue(serialization::pimpl::Data &data) {
                size_t size = (size_t)readInt();
                if (size > 0) {
                    serialization::pimpl::Data::BufferType &buffer =  data.toByteArray();
                    buffer.resize(size);
                    readFully(buffer);
                }
                
            }

            bool InputSocketStream::readBoolean() {
                return (bool)readByte();
            }
        }
    }
}

