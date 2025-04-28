/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzenner <gzenner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:28:11 by gzenner           #+#    #+#             */
/*   Updated: 2025/04/28 12:04:55 by gzenner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include <map>

class Class1
{
	private:
		std::map<std::string, std::string> map1;
	public:
		Class1();
		std::map<std::string, std::string> getMap1();
};

std::map<std::string, std::string> Class1::getMap1()
{
	return map1;
}

Class1::Class1()
{
	map1["key1"] = "value1";
}


class Class2
{
	private:
		std::map<std::string, std::string> map1;
	public:
		Class2();
		std::map<std::string, std::string> getMap1();
};

std::map<std::string, std::string> Class2::getMap1()
{
	return map1;
}

Class2::Class2()
{
	Class1 c1;
	map1 = c1.getMap1();
	std::map<std::string, std::string>::iterator it = map1.begin();
	while(it != map1.end())
	{
		std::cout << "[debugging][key] " << it->first << "[value]" << it->second << "\n";
		it++;
	}
}

int main()
{
	Class2 c2;
	return 0;
}