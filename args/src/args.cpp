

#include "args/option.h"
#include "args/args.h"

#include "cxxopts.hpp"

#include <functional>


Args::Args(std::string_view programName, std::string_view description /*= ""*/)
{
    mParser = new cxxopts::Options(std::string(programName), std::string(description));

    mParser->positional_help("[optional args]")
        .show_positional_help();

    mParser->add_option("", "?", "help", "Show this message and exit.", ::cxxopts::value<bool>(), "");



    mParser->add_options("Group")
        ("c,compile", "compile")
        ("i,input", "Input", cxxopts::value<std::string>())
        ("o,output", "Output file", cxxopts::value<std::string>()
            ->default_value("a.out")->implicit_value("b.def"), "BIN")
        ("positional",
            "Positional arguments: these are the arguments that are entered "
            "without an option", cxxopts::value<std::vector<std::string>>())
        ("d,drop", "drop", cxxopts::value<std::vector<std::string>>());

    mParser->parse_positional({ "input", "output", "positional" });

    //AddOption(Option("help", "Show this message and exit.", '?').Callback([&] { std::cout << *mParser << std::endl; }));
}

Args::~Args()
{
    delete mParser;
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
        type, "\0");

    /*
    po::option &popt = mParser->operator[](std::string(option.argument));

    popt.description(std::string(option.description));

    if (option.abbreviation.has_value())
    {
        popt.abbreviation(option.abbreviation.value());
    }

    if (!std::holds_alternative<std::monostate>(option.callback))
    {
        if (std::holds_alternative<std::function<void()>>(option.callback))
        {
            std::function<void(void)> callback = std::get<std::function<void()>>(option.callback);
            popt.callback([callback] { callback(); });
        }
        else if (std::holds_alternative<Option::fi32>(option.callback))
        {
            Option::fi32 callback = std::get<Option::fi32>(option.callback);
            popt.type(po::i32);
            popt.callback([callback](po::i32_t u) { callback(u); });
        }
        else if (std::holds_alternative<Option::fi64>(option.callback))
        {
            Option::fi64 callback = std::get<Option::fi64>(option.callback);
            popt.type(po::i64);
            popt.callback([callback](po::i64_t u) { callback(u); });
        }
        else if (std::holds_alternative<Option::fu32>(option.callback))
        {
            Option::fu32 callback = std::get<Option::fu32>(option.callback);
            popt.type(po::u32);
            popt.callback([callback](po::u32_t u) { callback(u); });
        }
        else if (std::holds_alternative<Option::fi64>(option.callback))
        {
            Option::fi64 callback = std::get<Option::fi64>(option.callback);
            popt.type(po::u64);
            popt.callback([callback](po::i64_t u) { callback(u); });
        }
        else if (std::holds_alternative<Option::ff32>(option.callback))
        {
            Option::ff32 callback = std::get<Option::ff32>(option.callback);
            popt.type(po::f32);
            popt.callback([callback](po::f32_t u) { callback(u); });
        }
        else if (std::holds_alternative<Option::ff64>(option.callback))
        {
            Option::ff64 callback = std::get<Option::ff64>(option.callback);
            popt.type(po::f64);
            popt.callback([callback](po::f64_t u) { callback(u); });
        }
    }

    mOptions.insert_or_assign(option.argument, option);
    */
    return true;
}

void Args::Parse(int int_argc, char **argv)
{
    auto result = mParser->parse(int_argc, argv);
    if (result.count("help"))
    {
        std::cout << mParser->help({ "", "Group" }) << std::endl;
    }
}

// bool Args::IsVerbose() const
// {
//     return mParser->is_verbose();
// }
// 
// bool Args::IsSilent() const
// {
//     return mParser->is_silent();
// }
// 
// bool Args::IsValid() const
// {
//     return mParser->wellformed();
// }
// 
// void Args::SetSilent()
// {
//     mParser->silent();
// }
// 
// void Args::SetVerbose(std::ostream &destination)
// {
//     mParser->verbose(destination);
// }
// 
// const Option & Args::GetOption(std::string_view argument) const
// {
//     return mOptions.find(argument)->second;
// }