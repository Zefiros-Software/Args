

#include "args/option.h"
#include "args/args.h"

#include <ProgramOptions.hxx>

#include <functional>

Args::Args()
{
    mParser = new po::parser();
}

Args::~Args()
{
    delete mParser;
}

bool Args::AddOption(Option &option)
{
    po::option &popt = mParser->operator[]("name");
    if (!std::holds_alternative<std::monostate>(option.callback))
    {
        if (std::holds_alternative<std::function<void()>>(option.callback))
        {
            std::function<void(void)> callback = std::get<std::function<void()>>(option.callback);
            popt.callback([callback] { callback(); });
        }
        else if (std::holds_alternative<std::function<void(uint32_t)>>(option.callback))
        {
            std::function<void(std::uint32_t)> callback = std::get<std::function<void(std::uint32_t)>>(option.callback);
            popt.type(po::u32);
            popt.callback([callback](po::u32_t u) { callback(u); });
        }
    }

    return true;
}

bool Args::Parse(int int_argc, char** argv)
{
    return mParser->operator()(int_argc, argv);
}

bool Args::IsVerbose()
{
    return mParser->is_verbose();
}

bool Args::IsSilent()
{
    return mParser->is_silent();
}

bool Args::IsValid()
{
    return mParser->wellformed();
}

void Args::SetSilent()
{
    mParser->silent();
}

void Args::SetVerbose(std::ostream& destination)
{
    mParser->verbose(destination);
}
