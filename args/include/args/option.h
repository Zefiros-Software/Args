#pragma once
#ifndef __OPTIONS_H__
#define __OPTIONS_H__

#include <functional>
#include <optional>
#include <variant>
#include <any>

struct Option
{
public:

    std::variant<std::function<void()>, std::function<void(uint32_t)>, std::monostate> callback;
    std::any fallback;
    std::any type;
};

#endif