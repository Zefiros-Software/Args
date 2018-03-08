#pragma once
#ifndef __OPTIONS_H__
#define __OPTIONS_H__

#include "cxxopts.hpp"

#include <functional>
#include <optional>
#include <variant>
#include <any>


// namespace OptionType
// {
//     template<typename tT>
//     struct Value
//     {
//         static auto GetType()
//         {
//             return cxxopts::value<tT>();
//         }
//     };
// 
//     Value<uint32_t> U32;
//     Value<uint64_t> U64;
//     Value<std::string> String;
// }

struct Option
{
public:

    template<typename tT>
    struct Type
    {
        auto operator()()
        {
            return cxxopts::value<tT>();
        }
    };

    static Type<uint32_t> U32;
    static Type<uint64_t> U64;
    static Type<int32_t> S32;
    static Type<int64_t> S64;
    static Type<float> F32;
    static Type<double> F64;
    static Type<std::string> String;

//     using fvoid = std::function<void()>;
//     using fi32 = std::function<void(std::int32_t)>;
//     using fi64 = std::function<void(std::int64_t)>;
//     using fu32 = std::function<void(std::uint32_t)>;
//     using fu64 = std::function<void(std::uint64_t)>;
//     using ff32 = std::function<void(float)>;
//     using ff64 = std::function<void(double)>;

    using ArgumentName = std::variant<std::string_view, std::pair<std::string_view, std::string_view>>;

    //std::shared_ptr<cxxopts::Value> type;
    std::string_view argument;
    std::string_view description;
    std::optional<std::string_view> abbreviation;


    std::optional<std::string_view> implicitValue;
    std::optional<std::string_view> defaultValue;

    //std::variant<std::monostate, fvoid, fi32, fi64, fu32, fu64, ff32, ff64> callback;
    std::any fallback;
    std::shared_ptr<cxxopts::Value> type;
    
    Option(std::string_view argument, std::string_view description, std::shared_ptr<cxxopts::Value> type = nullptr, std::optional<std::string_view> defaultValue = {}, std::optional<std::string_view> implicitValue = {})
        : argument(argument),
        abbreviation(std::nullopt),
        type(type)
    {
        if (defaultValue.has_value())
        {
            this->defaultValue = defaultValue.value();
        }
        if (implicitValue.has_value())
        {
            this->implicitValue = implicitValue.value();
        }
    }

    Option(std::pair<std::string_view, std::string_view> argument, std::string_view description, std::shared_ptr<cxxopts::Value> type = nullptr, std::optional<std::string_view> defaultValue = {}, std::optional<std::string_view> implicitValue = {})
        : argument(argument.second),
        abbreviation(argument.first),
        type(type)
    {
        if (defaultValue.has_value())
        {
            this->defaultValue = defaultValue.value();
        }
        if (implicitValue.has_value())
        {
            this->implicitValue = implicitValue.value();
        }
    }
    
//     template<typename tT>
//     Option &Callback(tT callback)
//     {
//         this->callback = LambdaToFunction(callback);
//         return *this;
//     }
// 
// private:
// 
//     template<typename T>
//     struct memfun_type
//     {
//         using type = void;
//     };
// 
//     template<typename Ret, typename Class, typename... Args>
//     struct memfun_type<Ret(Class::*)(Args...) const>
//     {
//         using type = std::function<Ret(Args...)>;
//     };
// 
//     template<typename F>
//     typename memfun_type<decltype(&F::operator())>::type
//         LambdaToFunction(F const &func)
//     {
//         return func;
//     }
};

#endif