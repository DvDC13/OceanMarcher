#pragma once

#include <iostream>
#include <string>
#include <boost/program_options.hpp>

namespace Utils
{
    class CommandLineOptions
    {
    public:
        enum class Status
        {
            SUCCESS,
            VERSION,
            HELP,
            ERROR
        };

        CommandLineOptions();
        ~CommandLineOptions();

        Status parse(int argc, char **argv);

    protected:
        void setup();
        bool validateFiles();

    private:
        boost::program_options::options_description m_options;
    };
} // namespace Utils