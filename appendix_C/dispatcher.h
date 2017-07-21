#ifndef __DISPATCHER_H__
#define __DISPATCHER_H__

#include "message_queue.h"
#include "TemplateDispatcher.h"

namespace messaging {
    class close_queue {};

    class dispatcher {
        private :
            queue* q;
            bool chained;
            dispatcher(const dispatcher& )=delete;
            dispatcher& operator=(const dispatcher& )=delete;

            template<typename Dispatcher, typename Msg, typename Func>
                friend class TemplateDispatcher;

            void wait_and_dispatch() {
                for(;;) {
                    auto msg = q->wait_and_pop();
                    dispatch(msg);
                }
            }

            bool dispatch(const std::shared_ptr<message_base>& msg) {
                if(dynamic_cast<wrapped_message<close_queue>*>(msg.get())) {
                    throw close_queue();
                }
                return false;
            }
        public :
            dispatcher(dispatcher&& other): q(other.q), chained(other.chained) {
                other.chained=true;
            }
            explicit dispatcher(queue* _q): q(_q), chained(false) {}
            template<typename Message, typename Func>
                TemplateDispatcher<dispatcher, Message, Func> handle(Func&& f) {
                    return TemplateDispatcher<dispatcher, Message, Func>(q, this, std::forward<Func>(f));
                }

            ~dispatcher() noexcept(false) {
                if(!chained) {
                    wait_and_dispatch();
                }
            }
    };
}

#endif
