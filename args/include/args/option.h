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

    static Type<bool> Boolean;
    static Type<uint32_t> U32;
    static Type<uint64_t> U64;
    static Type<int32_t> S32;
    static Type<int64_t> S64;
    static Type<float> F32;
    static Type<double> F64;
    static Type<std::string> String;

    static Type<std::vector<bool>> BooleanList;
    static Type<std::vector<uint32_t>> U32List;
    static Type<std::vector<uint64_t>> U64List;
    static Type<std::vector<int32_t>> S32List;
    static Type<std::vector<int64_t>> S64List;
    static Type<std::vector<float>> F32List;
    static Type<std::vector<double>> F64List;
    static Type<std::vector<std::string>> StringList;

    static Type<std::optional<bool>> OptionalBoolean;
    static Type<std::optional<uint32_t>> OptionalU32;
    static Type<std::optional<uint64_t>> OptionalU64;
    static Type<std::optional<int32_t>> OptionalS32;
    static Type<std::optional<int64_t>> OptionalS64;
    static Type<std::optional<float>> OptionalF32;
    static Type<std::optional<double>> OptionalF64;
    static Type<std::optional<std::string>> OptionalString;

    static Type<std::optional<std::vector<bool>>> OptionalBooleanList;
    static Type<std::optional<std::vector<uint32_t>>> OptionalU32List;
    static Type<std::optional<std::vector<uint64_t>>> OptionalU64List;
    static Type<std::optional<std::vector<int32_t>>> OptionalS32List;
    static Type<std::optional<std::vector<int64_t>>> OptionalS64List;
    static Type<std::optional<std::vector<float>>> OptionalF32List;
    static Type<std::optional<std::vector<double>>> OptionalF64List;
    static Type<std::optional<std::vector<std::string>>> OptionalStringList;

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