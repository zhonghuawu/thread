#ifndef __ATM_MESSAGE_H__
#define __ATM_MESSAGE_H__

#include <string>
#include "sender.h"

// 取款
struct withdraw {
    std::string account;
    unsigned amount;
    mutable messaging::sender atm_queue;
    withdraw(const std::string& _account,
            unsigned _amount,
            messaging::sender _atm_queue):
        account(_account), amount(_amount), atm_queue(_atm_queue) {}
};

// 取款成功
struct withdraw_ok {};

// 拒绝取款
struct withdraw_denied {};

// 取消取款
struct cancel_withdrawal {
    std::string account;
    unsigned amount;
    cancel_withdrawal(const std::string& _account,
            unsigned _amount):
        account(_account), amount(_amount) {}
};

// 处理取款
struct withdrawal_processed {
    std::string account;
    unsigned amount;
    withdrawal_processed(const std::string& _account,
            unsigned _amount):
        account(_account), amount(_amount) {}
};

// 插入卡
struct card_inserted {
    std::string account;
    explicit card_inserted(const std::string& _account):
        account(_account) {}
};

// 按下数字键
struct digit_pressed {
    char digit;

    explicit digit_pressed(char _digit): digit(_digit) {}
};

// 清楚最后一个数字键
struct clear_last_pressed {};

// 取出卡
struct eject_card {};

// 按下取款键
struct withdraw_pressed {
    unsigned amount;
    
    explicit withdraw_pressed(unsigned _amount):
        amount(_amount) {}
};

// 按下取消键
struct cancel_pressed {};

// 提供钞票
struct issue_money {
    unsigned amount;

    issue_money(unsigned _amount):
        amount(_amount) {}
};

// 校验PIN
struct verify_pin {
    std::string account;
    std::string pin;
    mutable messaging::sender atm_queue;

    verify_pin(const std::string& _account,
            const std::string& _pin,
            messaging::sender _atm_queue):
        account(_account), pin(_pin), atm_queue(_atm_queue) {}
};

// PIN正确
struct pin_verified {};

// PIN错误
struct pin_incorrect {};

// 
struct display_enter_pin {};

//
struct display_enter_card {};

//
struct display_insufficient_funds {};

//
struct display_withdrawal_cancelled {};

//
struct display_pin_incorrect_message {};

//
struct display_withdrawal_options {};

//
struct get_balance {
    std::string account;
    mutable messaging::sender atm_queue;

    get_balance(const std::string _account, messaging::sender _atm_queue):
        account(_account), atm_queue(_atm_queue) {}
};

//
struct balance {
    unsigned amount;

    explicit balance(unsigned _amount):
        amount(_amount) {}
};

//
struct display_balance {
    unsigned amount;

    explicit display_balance(unsigned _amount):
        amount(_amount) {}
};

//
struct balance_pressed {};

#endif
