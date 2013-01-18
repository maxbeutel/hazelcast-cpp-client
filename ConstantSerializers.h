//
//  ConstantSerializers.h
//  Server
//
//  Created by sancar koyunlu on 1/10/13.
//  Copyright (c) 2013 sancar koyunlu. All rights reserved.
//

#ifndef Server_ConstantSerializers_h
#define Server_ConstantSerializers_h

using namespace std;
#include "DataInput.h"
#include "DataOutput.h"
#include "SerializationConstants.h"
#include "TypeSerializer.h"
#include "ByteArray.h"
#include "IntegerArray.h"
#include "FloatArray.h"
#include "CharArray.h"
#include "ShortArray.h"
#include "LongArray.h"
#include "DoubleArray.h"

class ConstantSerializers {
public:
    
    class ByteSerializer : public TypeSerializer {
    public:
        
        int getTypeId() {
            return SerializationConstants::CONSTANT_TYPE_BYTE;
        };
        
        byte read(DataInput* dataInput) throw(ios_base::failure){
            return dataInput->readByte();
        };
        
        void write(DataOutput* dataOutput, byte const obj) throw(ios_base::failure){
            dataOutput->writeByte(obj);
        };
    };
    
    class BooleanSerializer : public TypeSerializer {
    public:
        
        int getTypeId() {
            return SerializationConstants::CONSTANT_TYPE_BOOLEAN;
        };
        
        void write(DataOutput* dataOutput, bool obj) throw(ios_base::failure){
            dataOutput->writeBoolean(obj);
        };
        
        bool read(DataInput* dataInput) throw(ios_base::failure){
            return dataInput->readBoolean();
        }
    };
    
    class CharSerializer : public TypeSerializer {
    public:
        
        int getTypeId() {
            return SerializationConstants::CONSTANT_TYPE_CHAR;
        }
        
        char read(DataInput* dataInput) throw(ios_base::failure){
            return dataInput->readChar();
        }
        
        void write(DataOutput* dataOutput, const char obj) throw(ios_base::failure){
            dataOutput->writeChar(obj);
        }
    };
    
    class ShortSerializer : public TypeSerializer {
    public:
        int getTypeId() {
            return SerializationConstants::CONSTANT_TYPE_SHORT;
        }
        
        short read(DataInput* dataInput) throw(ios_base::failure){
            return dataInput->readShort();
        }
        
        void write(DataOutput* dataOutput, const short obj) throw(ios_base::failure){
            dataOutput->writeShort(obj);
        }
    };
    
    class IntegerSerializer : public TypeSerializer {
    public:
        int getTypeId() {
            return SerializationConstants::CONSTANT_TYPE_INTEGER;
        }
        
        int read(DataInput* dataInput) throw(ios_base::failure){
            return dataInput->readInt();
        }
        
        void write(DataOutput* dataOutput, const int obj) throw(ios_base::failure){
            dataOutput->writeInt(obj);
        }
    };
    
    class LongSerializer : public TypeSerializer {
    public:
        int getTypeId() {
            return SerializationConstants::CONSTANT_TYPE_LONG;
        }
        
        long read(DataInput* dataInput) throw(ios_base::failure){
            return dataInput->readLong();
        }
        
        void write(DataOutput* dataOutput, const long obj) throw(ios_base::failure){
            dataOutput->writeLong(obj);
        }
    };
    
    class FloatSerializer : public TypeSerializer {
    public:
        int getTypeId() {
            return SerializationConstants::CONSTANT_TYPE_FLOAT;
        }
        
        float read(DataInput* dataInput) throw(ios_base::failure){
            return dataInput->readFloat();
        }
        
        void write(DataOutput* dataOutput, const float obj) throw(ios_base::failure){
            dataOutput->writeFloat(obj);
        }
    };
    
    class DoubleSerializer : public TypeSerializer {
    public:
        int getTypeId() {
            return SerializationConstants::CONSTANT_TYPE_DOUBLE;
        }
        
        double read(DataInput* dataInput) throw(ios_base::failure){
            return dataInput->readDouble();
        }
        
        void write(DataOutput* dataOutput, const double obj) throw(ios_base::failure){
            dataOutput->writeDouble(obj);
        }
    };
    
    class StringSerializer : public TypeSerializer {
    public:
        int getTypeId() {
            return SerializationConstants::CONSTANT_TYPE_STRING;
        }
        
        string read(DataInput* dataInput) throw(ios_base::failure){
            return dataInput->readUTF();
        }
        
        void write(DataOutput* dataOutput, const string obj) throw(ios_base::failure){
            dataOutput->writeUTF(obj);
        }
    };
    
    class ByteArraySerializer : public TypeSerializer {
    public:
        int getTypeId() {
            return SerializationConstants::CONSTANT_TYPE_BYTE_ARRAY;
        }
        
        ByteArray* read(DataInput* dataInput) throw(ios_base::failure){
            int size = dataInput->readInt();
            if (size == 0) {
                return NULL;
            } else {
                ByteArray* c = new ByteArray(size);
                for (int i = 0; i < size; i++) {
                    (*c)[i] = dataInput->readByte();
                }
                return c;
            }
        }
        
        void write(DataOutput* dataOutput, ByteArray& obj) throw(ios_base::failure){
            int size = obj.length();
            dataOutput->writeInt(size);
            if (size > 0) {
                for(int i = 0; i < size ; i++){
                    dataOutput->writeByte(obj[i]);
                }
            }
        }
    };
    
    class CharArraySerializer : public TypeSerializer {
    public:
        int getTypeId() {
            return SerializationConstants::CONSTANT_TYPE_CHAR_ARRAY;
        }
        
        CharArray* read(DataInput* dataInput) throw(ios_base::failure){
            int size = dataInput->readInt();
            if (size == 0) {
                return NULL;
            } else {
                CharArray* c = new CharArray(size);
                for (int i = 0; i < size; i++) {
                    (*c)[i] = dataInput->readChar();
                }
                return c;
            }
        }
        
        void write(DataOutput* dataOutput, CharArray& obj) throw(ios_base::failure){
            int size = obj.length();
            dataOutput->writeInt(size);
            if (size > 0) {
                for(int i = 0; i < size ; i++){
                    dataOutput->writeChar(obj[i]);
                }
            }
        }
    };
    
    class ShortArraySerializer : public TypeSerializer {
    public:
        int getTypeId() {
            return SerializationConstants::CONSTANT_TYPE_SHORT_ARRAY;
        }
        
        ShortArray* read(DataInput* dataInput) throw(ios_base::failure){
            int size = dataInput->readInt();
            if (size == 0) {
                return NULL;
            } else {
                ShortArray* c = new ShortArray(size);
                for (int i = 0; i < size; i++) {
                    (*c)[i] = dataInput->readShort();
                }
                return c;
            }
        }
        
        void write(DataOutput* dataOutput, ShortArray& obj) throw(ios_base::failure){
            int size = obj.length();
            dataOutput->writeInt(size);
            if (size > 0) {
                for(int i = 0; i < size ; i++){
                    dataOutput->writeShort(obj[i]);
                }
            }
        }
    };
    
    class IntegerArraySerializer : public TypeSerializer {
    public:
        int getTypeId() {
            return SerializationConstants::CONSTANT_TYPE_INTEGER_ARRAY;
        }
        
        IntegerArray* read(DataInput* dataInput) throw(ios_base::failure){
            int size = dataInput->readInt();
            if (size == 0) {
                return NULL;
            } else {
                IntegerArray* c = new IntegerArray(size);
                for (int i = 0; i < size; i++) {
                    (*c)[i] = dataInput->readInt();
                }
                return c;
            }
        }
        
        void write(DataOutput* dataOutput, IntegerArray& obj) throw(ios_base::failure){
            int size = obj.length();
            dataOutput->writeInt(size);
            if (size > 0) {
                for(int i = 0; i < size ; i++){
                    dataOutput->writeInt(obj[i]);
                }
            }
        }
    };
    
    class LongArraySerializer : public TypeSerializer {
    public:
        int getTypeId() {
            return SerializationConstants::CONSTANT_TYPE_LONG_ARRAY;
        }
        
        LongArray* read(DataInput* dataInput) throw(ios_base::failure){
            int size = dataInput->readInt();
            if (size == 0) {
                return NULL;
            } else {
                LongArray* c = new LongArray(size);
                for (int i = 0; i < size; i++) {
                    (*c)[i] = dataInput->readLong();
                }
                return c;
            }
        }
        
        void write(DataOutput* dataOutput, LongArray& obj) throw(ios_base::failure){
            int size = obj.length();
            dataOutput->writeInt(size);
            if (size > 0) {
                for(int i = 0; i < size ; i++){
                    dataOutput->writeLong(obj[i]);
                }
            }
        }
    };
    
    class FloatArraySerializer : public TypeSerializer {
    public:
        int getTypeId() {
            return SerializationConstants::CONSTANT_TYPE_FLOAT_ARRAY;
        }
        
        FloatArray* read(DataInput* dataInput) throw(ios_base::failure){
            int size = dataInput->readInt();
            if (size == 0) {
                return NULL;
            } else {
                FloatArray* c = new FloatArray(size);
                for (int i = 0; i < size; i++) {
                    (*c)[i] = dataInput->readFloat();
                }
                return c;
            }
        }
        
        void write(DataOutput* dataOutput, FloatArray& obj) throw(ios_base::failure){
            int size = obj.length();
            dataOutput->writeInt(size);
            if (size > 0) {
                for(int i = 0; i < size ; i++){
                    dataOutput->writeFloat(obj[i]);
                }
            }
        }
    };
    
    class DoubleArraySerializer : public TypeSerializer {
    public:
        int getTypeId() {
            return SerializationConstants::CONSTANT_TYPE_DOUBLE_ARRAY;
        }
        
        DoubleArray* read(DataInput* dataInput) throw(ios_base::failure){
            int size = dataInput->readInt();
            if (size == 0) {
                return NULL;
            } else {
                DoubleArray* c = new DoubleArray(size);
                for (int i = 0; i < size; i++) {
                    (*c)[i] = dataInput->readDouble();
                }
                return c;
            }
        }
        
        void write(DataOutput* dataOutput, DoubleArray& obj) throw(ios_base::failure){
            int size = obj.length();
            dataOutput->writeInt(size);
            if (size > 0) {
                for(int i = 0; i < size ; i++){
                    dataOutput->writeDouble(obj[i]);
                }
            }
        }
    };
     
private:
    
    
//        ConstantSerializers() {};
};

#endif
