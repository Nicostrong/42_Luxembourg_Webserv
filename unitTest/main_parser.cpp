# include "../includes/Nico.hpp"

int		main( int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: ./test_parser \"path_to_config_file\"" << std::endl;
		return (1);
	}
	try
	{
		ParserServerConfig		pc(argv[1]);

		pc.printServers();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}