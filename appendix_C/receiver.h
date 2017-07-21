#ifndef __RECEIVER_H__
#define __RECEIVER_H__

#include "message_queue.h"
#include "sender.h"
#include "dispatcher.h"

namespace messaging {
    class receiver {
        private :
            queue q;
        public :
            operator sender() {
                return sender(&q);
            }
            dispatcher wait() {
                return dispatcher(&q);
            }
    };
}

#endif
