#ifndef __SENDER_H__
#define __SENDER_H__

#include "message_queue.h"

namespace messaging {
    class sender {
        private :
            queue* q;
        public :
            sender(): q(nullptr) {}
            explicit sender(queue* _q): q(_q) {}
            template<typename Message>
                void send(const Message& msg) {
                    if(q) {
                        q->push(msg);
                    }
                }
    };
}

#endif
