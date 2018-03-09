

#include "args/option.h"
#include "args/args.h"

#include <functional>


Args::Args(std::string_view programName, std::string_view description /*= ""*/)
    : mResults(nullptr)
{
    mParser = new cxxopts::Options(std::string(programName), std::string(description));

    mParser->add_option("", "?", "help", "Show this message and exit.", ::cxxopts::value<bool>(), "");
}

Args::~Args()
{
    delete mParser;
    delete mResults;
}

bool Args::AddOptions(std::string_view group, std::vector<Option> &&options)
{
    for (auto opt : options)
    {
        AddOption(opt, group);
    }

    return true;
}

bool Args::AddOptions(std::vector<Option> &&options)
{
    return AddOptions("", std::move(options));
}

bool Args::AddOption(Option &option, std::string_view group /*= ""*/)
{
    auto type = option.type ? option.type : ::cxxopts::value<bool>();
    if (option.implicitValue)
    {
        type->default_value(std::string(*option.implicitValue));
    }
    if (option.defaultValue)
    {
        type->implicit_value(std::string(*option.defaultValue));
    }

    mParser->add_option(std::string(group), 
        std::string(option.abbreviation.value_or("")), 
        std::string(option.argument), 
        std::string(option.description), 
        type, std::string(option.argHelp.value_or("\0")));
    return true;
}

void Args::SetPositional(std::vector<std::string> &&positional, std::optional<std::string_view> positionalHelp /*= std::nullopt*/)
{
    mParser->parse_positional(std::move(positional));


    if (positionalHelp.has_value())
    {
        mParser->positional_help(std::string(positionalHelp.value()))
            .show_positional_help();
    }
}

void Args::Parse(int& argc, char**& argv)
{
    mResults = new cxxopts::ParseResult(mParser->parse(argc, argv));
    if (mResults->count("help"))
    {
        std::cout << mParser->help() << std::endl;
    }
}

OptionValue Args::GetOption(std::string_view argument) const
{
    return mResults->operator[](std::string(argument));
}

std::vector< std::pair< std::string_view, OptionValue > > Args::GetArguments()
{
    std::vector< std::pair< std::string_view, OptionValue > > result;

    for (auto kv : mResults->arguments())
    {
        result.emplace_back(std::make_pair(std::string_view(kv.key()), mResults->operator[](std::string(kv.key()))));
    }

    return result;
}
