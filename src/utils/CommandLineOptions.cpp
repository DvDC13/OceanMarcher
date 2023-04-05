#include "CommandLineOptions.h"

namespace Utils
{
    CommandLineOptions::CommandLineOptions()
        : m_options("")
    {
        setup();
    }

    CommandLineOptions::~CommandLineOptions()
    {}

    void CommandLineOptions::setup()
    {
        m_options.add_options()
            ("help,h", "Print help messages")
            ("version,v", "Print version information");
    }

    CommandLineOptions::Status CommandLineOptions::parse(int argc, char **argv)
    {
        boost::program_options::variables_map vm;
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, m_options), vm);
        boost::program_options::notify(vm);

        if (vm.count("help"))
        {
            std::cout << m_options << std::endl;
            return Status::HELP;
        }

        if (vm.count("version"))
        {
            std::cout << "Version 1.0" << std::endl;
            return Status::VERSION;
        }

        return Status::SUCCESS;
    }
}