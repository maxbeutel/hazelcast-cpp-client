//
// Created by sancar koyunlu on 31/12/13.
//


#ifndef HAZELCAST_ByteBuffer
#define HAZELCAST_ByteBuffer

#include "hazelcast/util/HazelcastDll.h"
#include <vector>
#include <cstdlib>

namespace hazelcast {
    namespace client {
        class Socket;
    }
    namespace util {
        class HAZELCAST_API ByteBuffer {
        public:
            ByteBuffer(char* buffer, size_t size);

            ByteBuffer &flip();

            ByteBuffer &compact();

            ByteBuffer &clear();

            size_t remaining() const;

            bool hasRemaining() const;

            size_t position() const;

            void position(size_t );

            size_t readFrom(const client::Socket &socket, int flag = 0);

            void writeTo(const client::Socket &socket);

            int readInt();

            int readShort();

            void writeInt(int v);

            void writeShort(int v);

            size_t writeTo(std::vector<byte> &destination, size_t offset);

            void writeTo(std::vector<byte> &destination);

            void readFrom(std::vector<byte> const &source);

            size_t readFrom(std::vector<byte> const &source, size_t offset);

            void skip(int l);

            char readByte();

            size_t limit() const;

            void writeByte(char c);
        private:

            void *ix() const;

            size_t minimum(size_t a, size_t b) const;

            void safeIncrementPosition(size_t );

            size_t pos;
            size_t lim;
            size_t capacity;
            char *buffer;
        };
    }
}

#endif //HAZELCAST_ByteBuffer

