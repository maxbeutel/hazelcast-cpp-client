/*
 * Copyright (c) 2008-2015, Hazelcast, Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
//
// Created by sancar koyunlu on 02/04/14.
//


#ifndef HAZELCAST_ThreadArgs
#define HAZELCAST_ThreadArgs

#include <string>

namespace hazelcast {
    namespace util {

        class Thread;

        class ThreadArgs {
        public:
            void *arg0;
            void *arg1;
            void *arg2;
            void *arg3;
            Thread* currentThread;
            void (*func)(ThreadArgs &);
        } ;

    }
}


#endif //HAZELCAST_ThreadArgs

