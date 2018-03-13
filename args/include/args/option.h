#pragma once
#ifndef __OPTIONS_H__
#define __OPTIONS_H__

#include <functional>
#include <optional>
#include <variant>
#include <any>

#define CXXOPTS_HAS_OPTIONAL
#include "cxxopts.hpp"



struct OptionValue
{
    OptionValue(const cxxopts::OptionValue &val)
        : mValue(val)
    {
    }

    OptionValue(const OptionValue &other)
        : mValue(other.mValue)
    {
    }

    size_t Count() const
    {
        return mValue.count();
    }

    template<typename tT>
    const tT& Get() const
    {
        return mValue.as<tT>();
    }

private:


    const cxxopts::OptionValue &mValue;
};

struct Option
{
public:

    template<typename tT>
    struct Type
    {
        auto operator()() const
        {
            return cxxopts::value<tT>();
        }
    };

    static std::shared_ptr<cxxopts::Value> Boolean() { return Type<bool>()();};
    static std::shared_ptr<cxxopts::Value> U32() { return Type<uint32_t>()();};
    static std::shared_ptr<cxxopts::Value> U64() { return Type<uint64_t>()();};
    static std::shared_ptr<cxxopts::Value> S32() { return Type<int32_t>()();};
    static std::shared_ptr<cxxopts::Value> S64() { return Type<int64_t>()();};
    static std::shared_ptr<cxxopts::Value> F32() { return Type<float>()();};
    static std::shared_ptr<cxxopts::Value> F64() { return Type<double>()();};
    static std::shared_ptr<cxxopts::Value> String() { return Type<std::string>()();};

    static std::shared_ptr<cxxopts::Value> BooleanList() { return Type<std::vector<bool>>()();};
    static std::shared_ptr<cxxopts::Value> U32List() { return Type<std::vector<uint32_t>>()();};
    static std::shared_ptr<cxxopts::Value> U64List() { return Type<std::vector<uint64_t>>()();};
    static std::shared_ptr<cxxopts::Value> S32List() { return Type<std::vector<int32_t>>()();};
    static std::shared_ptr<cxxopts::Value> S64List() { return Type<std::vector<int64_t>>()();};
    static std::shared_ptr<cxxopts::Value> F32List() { return Type<std::vector<float>>()();};
    static std::shared_ptr<cxxopts::Value> F64List() { return Type<std::vector<double>>()();};
    static std::shared_ptr<cxxopts::Value> StringList() { return Type<std::vector<std::string>>()();};

    /*
    static std::shared_ptr<cxxopts::Value> OptionalBoolean() { return Type<std::optional<bool>>()();};
    static std::shared_ptr<cxxopts::Value> OptionalU32() { return Type<std::optional<uint32_t>>()();};
    static std::shared_ptr<cxxopts::Value> OptionalU64() { return Type<std::optional<uint64_t>>()();};
    static std::shared_ptr<cxxopts::Value> OptionalS32() { return Type<std::optional<int32_t>>()();};
    static std::shared_ptr<cxxopts::Value> OptionalS64() { return Type<std::optional<int64_t>>()();};
    static std::shared_ptr<cxxopts::Value> OptionalF32() { return Type<std::optional<float>>()();};
    static std::shared_ptr<cxxopts::Value> OptionalF64() { return Type<std::optional<double>>()();};
    static std::shared_ptr<cxxopts::Value> OptionalString() { return Type<std::optional<std::string>>()();};

    static std::shared_ptr<cxxopts::Value> OptionalBooleanList() { return Type<std::optional<std::vector<bool>>>()();};
    static std::shared_ptr<cxxopts::Value> OptionalU32List() { return Type<std::optional<std::vector<uint32_t>>>()();};
    static std::shared_ptr<cxxopts::Value> OptionalU64List() { return Type<std::optional<std::vector<uint64_t>>>()();};
    static std::shared_ptr<cxxopts::Value> OptionalS32List() { return Type<std::optional<std::vector<int32_t>>>()();};
    static std::shared_ptr<cxxopts::Value> OptionalS64List() { return Type<std::optional<std::vector<int64_t>>>()();};
    static std::shared_ptr<cxxopts::Value> OptionalF32List() { return Type<std::optional<std::vector<float>>>()();};
    static std::shared_ptr<cxxopts::Value> OptionalF64List() { return Type<std::optional<std::vector<double>>>()();};
    static std::shared_ptr<cxxopts::Value> OptionalStringList() { return Type<std::optional<std::vector<std::string>>>()();};
    */

    using ArgumentName = std::variant<std::string_view, std::pair<std::string_view, std::string_view>>;

    std::string_view argument;
    std::string_view description;
    std::optional<std::string_view> argHelp;
    std::optional<std::string_view> abbreviation;


    std::optional<std::string_view> implicitValue;
    std::optional<std::string_view> defaultValue;

    std::any fallback;
    std::shared_ptr<cxxopts::Value> type;

    Option(std::string_view argument, std::string_view description, std::shared_ptr<cxxopts::Value> type = nullptr, std::optional<std::string_view> defaultValue = {}, std::optional<std::string_view> implicitValue = {})
        : argument(argument),
        description(description),
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
        description(description),
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

    Option(std::string_view argument, std::string_view description, std::string_view argHelp, std::shared_ptr<cxxopts::Value> type = nullptr, std::optional<std::string_view> defaultValue = {}, std::optional<std::string_view> implicitValue = {})
        : argument(argument),
        description(description),
        argHelp(argHelp),
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

    Option(std::pair<std::string_view, std::string_view> argument, std::string_view description, std::string_view argHelp, std::shared_ptr<cxxopts::Value> type = nullptr, std::optional<std::string_view> defaultValue = {}, std::optional<std::string_view> implicitValue = {})
        : argument(argument.second),
        description(description),
        argHelp(argHelp),
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
};

#endif