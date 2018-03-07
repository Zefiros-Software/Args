
#include "args/args.h"

#include <ProgramOptions.hxx>

Args::Args()
{
    mParser = new po::parser();
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
