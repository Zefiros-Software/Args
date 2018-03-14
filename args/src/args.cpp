/**
 * @cond ___LICENSE___
 *
 * Copyright (c) 2016-2018 Zefiros Software.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @endcond
 */


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

void Args::Parse(int argc, const char **argv, bool exitOnHelp /*= true*/)
{
    // @todo: remove the const_cast once the new cxxopts is released
    mResults = new cxxopts::ParseResult(mParser->parse(argc, const_cast<char ** &>(argv)));

    if (mResults->count("help"))
    {
        Help();

        if (exitOnHelp)
        {
            exit(EXIT_SUCCESS);
        }
    }
}

void Args::Parse(int argc, char **argv, bool exitOnHelp /*= true*/)
{
    Parse(argc, (const char **)argv, exitOnHelp);
}

void Args::Help() const
{
    std::cout << mParser->help() << std::endl;
}

OptionValue Args::GetOption(std::string_view argument) const
{
    return OptionValue(mResults->operator[](std::string(argument)), *this);
}

std::vector< std::pair< std::string_view, OptionValue >> Args::GetArguments() const
{
    std::vector< std::pair< std::string_view, OptionValue >> result;

    for (const auto &kv : mResults->arguments())
    {
        result.emplace_back(std::string_view(kv.key()), OptionValue{ mResults->operator[](std::string(kv.key())), *this });
    }

    return result;
}
