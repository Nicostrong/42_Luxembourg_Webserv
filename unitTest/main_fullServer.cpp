/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fullServer.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:28:13 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/04/29 15:46:39 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include "../includes/HandleConfig.hpp"
#include "../includes/Server.hpp"

int	main( void )
{
	try
	{
		HandleConfig		hg("../config/webserver.conf");
		hg.printwebconfMap();
		/*EventMonitoring		em;
		
		Server	s(hg.getwebconfMap(), em);
		std::cout << s << std::endl;

		std::cout << std::endl << "------------ TEST SERVER ----------" << std::endl << std::endl;
		
		assert(s.getPort() == 8080);
		std::cout << "✅ [OK] get Port test passed." << std::endl;
		assert(s.getAdress() == "127.0.0.1");
		std::cout << "✅ [OK] get Adress test passed." << std::endl;
		assert(s.getName() == "localhost");
		std::cout << "✅ [OK] get Name test passed." << std::endl;
		assert(s.getPath() == "./www/html");
		std::cout << "✅ [OK] get Path test passed." << std::endl;
		assert(s.getMaxSizeBody() == 5242880);
		std::cout << "✅ [OK] get MaxSizeBody test passed." << std::endl;
		assert(s.getIndex() == "index.html");
		std::cout << "✅ [OK] get Index test passed." << std::endl;
		std::cout << "✅ [OK] Serverbasic config test passed." << std::endl;

		std::cout << std::endl << "------------ TEST BOOL GIGI ----------" << std::endl << std::endl;
		
		std::cout << "Test checkUri(/) => " << (s.checkUri("/") ? "✅ [OK]" : "❌ [KO]") << std::endl;
		std::cout << "Test checkUri(/blabla) => " << (s.checkUri("/blabla") ? "❌ [OK]" : "✅ [KO]") << std::endl;
		std::cout << "Test checkUri(/images) => " << (s.checkUri("/images") ? "✅ [OK]" : "❌ [KO]") << std::endl;

		std::cout << "Test checkMethod(/, POST) => " << (s.checkMethod("/", "POST") ? "✅ [OK]" : "❌ [KO]") << std::endl;
		std::cout << "Test checkMethod(/blabla, GET) => " << (s.checkMethod("/blabla", "GET") ? "✅ [OK]" : "❌ [KO]") << std::endl;
		std::cout << "Test checkMethod(/images, POST) => " << (s.checkMethod("/images", "POST") ? "❌ [OK]" : "✅  [KO]") << std::endl;
		*/
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	
	return (0);
}