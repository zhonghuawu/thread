#ifndef __TEMPLATE_DISPATCHER_H__
#define __TEMPLATE_DISPATCHER_H__

namespace messaging {
    template<typename PreviousDispatcher, typename Msg, typename Func>
        class TemplateDispatcher {
            private :
                queue* q;
                PreviousDispatcher* prev;
                Func f;
                bool chained;

                TemplateDispatcher(const TemplateDispatcher&)=delete;
                TemplateDispatcher& operator=(const TemplateDispatcher&)=delete;

                template<typename Dispatcher, typename OtherMsg, typename OtherFunc>
                friend class TemplateDispatcher; //实例之间互为友元

                void wait_and_dispatch() {
                    for(;;) {
                        auto msg = q->wait_and_pop();
                        if(dispatch(msg))
                            break;
                    }
                }

                bool dispatch(const std::shared_ptr<message_base>& msg) {
                    if(wrapped_message<Msg>* wrapper=dynamic_cast<wrapped_message<Msg>*>(msg.get())) {
                        f(wrapper->contents);
                        return true;
                    }
                    else {
                        return prev->dispatch(msg);
                    }
                }
            public :
                TemplateDispatcher(TemplateDispatcher&& other):
                    q(other.q), prev(other.prev), f(std::move(other.f)), chained(other.chained) {
                        other.chained=true;
                    }
                TemplateDispatcher(queue* _q, PreviousDispatcher* _prev, Func&& _f):
                    q(_q), prev(_prev), f(std::forward<Func>(_f)), chained(false) {
                        _prev->chained=true;
                    }
                template<typename OtherMsg, typename OtherFunc>
                    TemplateDispatcher<TemplateDispatcher, OtherMsg, OtherFunc>
                    handle(OtherFunc&& of) {
                        return TemplateDispatcher<TemplateDispatcher, OtherMsg, OtherFunc>(q, this, std::forward<OtherFunc>(of));
                    }
                ~TemplateDispatcher() noexcept(false) {
                    if(!chained) {
                        wait_and_dispatch();
                    }
                }
        };
}

#endif
