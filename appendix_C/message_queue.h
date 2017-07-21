#ifndef __MESSAGE_QUEUE__H__
#define __MESSAGE_QUEUE__H__

#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>

namespace messaging {
    // message base class
    struct message_base {
        virtual ~message_base() {}
    };

    // message type 
    template<typename Msg>
        struct wrapped_message: message_base {
            Msg contents;

            explicit wrapped_message(const Msg& _contents): contents(_contents) {}
        };

    // message queue
    class queue {
        private :
            std::mutex m;
            std::condition_variable c;
            std::queue<std::shared_ptr<message_base> > q;
        public :
            template<typename T>
                void push(const T& msg) {
                    std::lock_guard<std::mutex> lk(m);
                    q.push(std::make_shared<wrapped_message<T> >(msg));
                    c.notify_all();
                }

            std::shared_ptr<message_base> wait_and_pop() {
                std::unique_lock<std::mutex> lk(m);
                c.wait(lk, [&](){ return !q.empty(); });
                auto res = q.front();
                q.pop();
                return res;
            }
    };

}

#endif
