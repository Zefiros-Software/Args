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


#include "args/args.h"
#include "args/option.h"

#include "gtest/gtest.h"

#include <stdlib.h>

TEST(Test, Example)
{
    const char *argv[] = { "program name", "--name", "3", NULL };
    int argc = sizeof(argv) / sizeof(char *) - 1;

    Args args{ "program name" };
    Option opt({"n", "name"}, "", Option::U32()); //.Callback([](std::int32_t u) { std::cout << "world" << u << std::endl; });
    //opt.callback = [] { std::cout << "hello" << std::endl; };
    args.AddOption(opt);

    args.Parse(argc, argv, false);
}

TEST(Test, Example2)
{
    const char *argv[] = { "program name", "--help", NULL };
    int argc = sizeof(argv) / sizeof(char *) - 1;

    Args args("program name");
    //opt.callback = [] { std::cout << "hello" << std::endl; };
    args.AddOptions(
    {
        { "name", "" }
    });

    args.Parse(argc, argv, false);
}

TEST(Test, Example3)
{
    const char *argv[] = { "program name", "--help", NULL };
    int argc = sizeof(argv) / sizeof(char *) - 1;

    Args args("program name");
    Option opt = (Option{ "", "Test positional" });//.Callback([](std::int32_t u) { std::cout << "world" << u << std::endl; });
    //opt.callback = [] { std::cout << "hello" << std::endl; };
    args.AddOption(opt);

    args.Parse(argc, argv, false);
}

TEST(Test, Example4)
{
    const char *argv[] = { "program name", "--help", NULL };
    int argc = sizeof(argv) / sizeof(char *) - 1;

    Args args("program name");
    args.AddOptions(
    {
        { { "f", "name" }, "", Option::U32() }
    });

    args.Parse(argc, argv, false);
}

TEST(Test, Example5)
{
    const char *argv[] = { "program name", "--help", NULL };
    int argc = sizeof(argv) / sizeof(char *) - 1;

    Args args("program name");
    args.AddOptions(
    {
        { { "f", "name" }, "", Option::U32(), "321"}
    });

    args.Parse(argc, argv, false);
}

TEST(Test, Example6)
{
    const char *argv[] = { "program name", "--help", NULL };
    int argc = sizeof(argv) / sizeof(char *) - 1;

    Args args("program name");
    args.AddOptions(
    {
        { { "f", "name" }, "weff wefwef", Option::U32(), std::nullopt, "321" }
    });

    args.Parse(argc, argv, false);
}

TEST(Test, Example7)
{
    const char *argv[] = { "program name", "--help", NULL };
    int argc = sizeof(argv) / sizeof(char *) - 1;

    Args args("program name");
    args.AddOptions(
    {
        { { "f", "name" }, "weff wefwef", "help", Option::U32(), "321" }
    });

    args.Parse(argc, argv, false);
}

TEST(Test, Example8)
{
    const char *argv[] = { "program name", "--name", "42", NULL };
    int argc = sizeof(argv) / sizeof(char *) - 1;

    Args args("program name");
    args.AddOptions(
    {
        { { "f", "name" }, "weff wefwef", "help", Option::U32(), "321" }
    });

    args.Parse(argc, argv, false);

    uint32_t name = args.GetOption("name");
    EXPECT_EQ(name, 42u);
}

TEST(Test, Example9)
{
    const char *argv[] = { "program name", NULL };
    int argc = sizeof(argv) / sizeof(char *) - 1;

    Args args("program name");
    args.AddOptions(
    {
        { { "f", "name" }, "weff wefwef", "help", Option::U32(), "321" }
    });

    args.Parse(argc, argv, false);
    ASSERT_EXIT(args.GetOption("name").Get<uint32_t>(), ::testing::ExitedWithCode(EXIT_FAILURE), "");
}

int main(int argc, char **argv)
{

#ifdef _WIN32
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
    //_crtBreakAlloc = 0;
#endif

    ::testing::InitGoogleTest(&argc, argv);

    int32_t result = ::testing::UnitTest::GetInstance()->Run();

    return result;
}

