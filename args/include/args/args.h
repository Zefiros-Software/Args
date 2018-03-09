/**
 * @cond ___LICENSE___
 *
 * Copyright (c) 2018 Zefiros Software.
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
 *
 */

#pragma once
#ifndef __ARGS_H__
#define __ARGS_H__

#include "args/option.h"

#include <unordered_map>
#include <string_view>
#include <iosfwd>

namespace cxxopts
{
    class Options;
}


class Args
{
public:

    Args(std::string_view programName, std::string_view description = "");

    virtual ~Args();

    bool AddOptions(std::string_view group, std::vector<Option> &&options);

    bool AddOptions(std::vector<Option> &&options);

    bool AddOption(Option &option, std::string_view group = "");

    void SetPositional(std::vector<std::string> &&positional, std::optional<std::string_view> positionalHelp = std::nullopt);

    void Parse(int argc, char **argv);

    void Parse(int argc, const char **argv);

    OptionValue GetOption(std::string_view argument) const;

    std::vector< std::pair< std::string_view, OptionValue > > GetArguments() const;

private:
    cxxopts::Options *mParser;
    cxxopts::ParseResult *mResults;
};


#endif