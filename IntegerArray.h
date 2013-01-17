//
//  IntegerArray.h
//  cppClient
//
//  Created by sancar koyunlu on 1/14/13.
//  Copyright (c) 2013 sancar koyunlu. All rights reserved.
//

#ifndef __cppClient__IntegerArray__
#define __cppClient__IntegerArray__

class IntegerArray{
public:
    IntegerArray(int len):len(0){
        this->len = len;
        buffer = new int[len];
    };
    IntegerArray(const IntegerArray& rhs){
        len = rhs.len;
        delete [] buffer;
        buffer = new int[len];
        for(int i = 0; i < len; i++){
            buffer[i] = rhs.buffer[i];
        }
    };
    ~IntegerArray(){
        delete [] buffer;
    };
    int& operator[](int i){
        return buffer[i];
    };
    
    int length(){ return len; };
private:
    int len;
    int* buffer;
};

#endif /* defined(__cppClient__IntegerArray__) */
