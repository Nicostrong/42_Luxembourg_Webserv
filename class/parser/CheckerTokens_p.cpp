/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckerTokens_p.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:26:39 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/07/08 13:42:46 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser/CheckerTokens.hpp"

/*******************************************************************************
 *							Private Method									   *
 ******************************************************************************/

/*
 *	Call all the check function
 */
void		CheckerTokens::validateTokens( void )
{
	checkBracesAndBlocks();
	checkHTTPKeyValuePairs();
	checkDirectiveKeyValuePairs();
	checkSemicolonAfterDirectiveValue();
	checkSemicolonAfterHTTPValue();
	checkSemicolonBeforeBlockEnd();
	checkUnexpectedSemicolons();
	checkDuplicatedKeysInScope();
	//checkpath();
	checkValue();
	checkMethodHTTP();
	checkUniqValue();
	checkListen();
	checkReturn();
	assertFinalState();
	return ;
}

/*
 *	Check the number of brace and the localisation of block
 */
void		CheckerTokens::checkBracesAndBlocks( void )
{
	const Token*		current = this->_head;

	while (current)
	{
		checkServerTokens(current);
		checkLocationTokens(current);
		checkErrorPageTokens(current);
		checkCGITokens(current);
		current = current->getNext();
	}
	return ;
}

/*
 *	Check the brace and the localisation of block SERVER
 */
void		CheckerTokens::checkServerTokens( const Token* current )
{
	if (current->getType() == Token::SERVER)
	{
		if (this->_inServer || this->_inErrorBlk || this->_inLocation || this->_inCGI)
			throw CheckerError("Server block not allowed in this scope");
	}
	else if (current->getType() == Token::SER_BLK_S)
	{
		if (this->_inServer || this->_inLocation || this->_inErrorBlk || this->_inCGI)
			throw CheckerError("Server block not allowed in this scope");
		this->_inServer = true;
		++this->_braceCount;
	}
	else if (current->getType() == Token::SER_BLK_E)
	{
		--this->_braceCount;
		if (this->_braceCount != 0 || this->_inLocation || this->_inErrorBlk || this->_inCGI)
			throw CheckerError("Unexpected closing brace");
		if (this->_inServer)
			this->_inServer = false;
		else
			throw CheckerError("Unexpected closing brace");
	}
	return ;
}

/*
 *	Check the brace and the localisation of block ERROR_PAGE
 */
void		CheckerTokens::checkErrorPageTokens( const Token* current )
{
	if (current->getType() == Token::ERROR_PAGE)
	{
		if (!this->_inServer || this->_inErrorBlk || this->_inLocation || this->_inCGI)
			throw CheckerError("Nested error block not allowed");
	}
	else if (current->getType() == Token::ERR_BLK_S)
	{
		++this->_braceCount;
		if (!this->_inServer)
			throw CheckerError("Error_page block not allowed outside server");
		if (this->_inErrorBlk || this->_inLocation || this->_inCGI)
			throw CheckerError("Error_page block not allowed in this scope");
		this->_inErrorBlk = true;
	}
	else if (current->getType() == Token::ERR_BLK_E)
	{
		--this->_braceCount;
		if (this->_braceCount < 0)
			throw CheckerError("Too many closing braces ERROR " + current->getValue());
		if (!this->_inServer || this->_inLocation || this->_inCGI)
			throw CheckerError("Unexpected closing brace");
		if (this->_inErrorBlk)
			this->_inErrorBlk = false;
		else
			throw CheckerError("Unexpected closing brace");
	}
}

/*
 *	Check the brace and the localisation of block LOCATION
 */
void		CheckerTokens::checkLocationTokens( const Token* current )
{
	if (current->getType() == Token::LOCATION)
	{
		if (!this->_inServer || this->_inErrorBlk || this->_inLocation || this->_inCGI)
			throw CheckerError("Location block not allowed in this scope");
	}
	else if (current->getType() == Token::LOC_BLK_S)
	{
		++this->_braceCount;
		if (!this->_inServer)
			throw CheckerError("Location block not allowed outside server");
		if (this->_inErrorBlk || this->_inLocation || this->_inCGI)
			throw CheckerError("Location block not allowed in this scope");
		this->_inLocation = true;
	}
	else if (current->getType() == Token::LOC_BLK_E)
	{
		--this->_braceCount;
		if (this->_braceCount < 0)
			throw CheckerError("Too many closing braces LOCATION " + current->getValue());
		if (this->_inErrorBlk || this->_inCGI)
			throw CheckerError("Unexpected closing brace");
		if (this->_inLocation)
			this->_inLocation = false;
		else
			throw CheckerError("Unexpected closing brace");
	}
}

/*
 *	Check the brace and the localisation of block CGI
 */
void CheckerTokens::checkCGITokens( const Token* current )
{
	if (current->getType() == Token::CGI)
	{
		if (!this->_inServer)
			throw CheckerError("CGI block not allowed outside server");
		if (this->_inErrorBlk || !this->_inLocation )
			throw CheckerError("CGI block not allowed in this scope");
	}
	else if (current->getType() == Token::CGI_BLK_S)
	{
		++this->_braceCount;
		if (!this->_inServer)
			throw CheckerError("CGI block not allowed outside server");
		if (!this->_inLocation)
			throw CheckerError("CGI block outside location");
		if (this->_inErrorBlk)
			throw CheckerError("CGI block not allowed in error block");
		this->_inCGI = true;
	}
	else if (current->getType() == Token::CGI_BLK_E)
	{
		--this->_braceCount;
		if (this->_braceCount < 0)
			throw CheckerError("Too many closing braces CGI " + current->getValue());
		if (!this->_inServer || this->_inErrorBlk || !this->_inLocation)
			throw CheckerError("Unexpected closing brace");
		if (this->_inCGI)
			this->_inCGI = false;
		else
			throw CheckerError("Unexpected closing brace");
	}
}

/*
 *	Check if a HTTP key is next by a HTTP value
 */
void		CheckerTokens::checkHTTPKeyValuePairs( void )
{
	const Token*		current = this->_head;

	while (current && current->getNext() && current->getNext()->getNext())
	{
		if (current->getType() == Token::HTTP_K)
		{
			Token*			next = current->getNext();

			if (next->getType() != Token::HTTP_V)
				throw CheckerError("Expected HTTP value after key " + current->getValue());
		}
		current = current->getNext();
	}
	return ;
}

/*
 *	Check if a directive key is next by one or more directive values
 */
void		CheckerTokens::checkDirectiveKeyValuePairs(void)
{
	const Token*		current = this->_head;

	while (current)
	{
		if (current->getType() == Token::DIR_K)
		{
			Token*		next = current->getNext();

			if (!next)
				throw CheckerError("Missing value after directive key " + current->getValue());
			while (next && (next->getType() == Token::DIR_V))
				next = next->getNext();
			if (!next || next->getType() != Token::SEMICOLON)
				throw CheckerError("Expected ';' after directive key-value(s) for " + current->getValue());
			current = next;
		}
		current = current->getNext();
	}
	return ;
}

/*
 *	Check semicolon after directive value
 */
void		CheckerTokens::checkSemicolonAfterDirectiveValue( void )
{
	const Token*		current = this->_head;

	while (current && current->getNext())
	{
		if (current->getType() == Token::DIR_V && current->getNext()->getType() != Token::DIR_V)
			if (current->getNext()->getType() != Token::SEMICOLON)
				throw CheckerError("Expected ';' after " + current->getValue());
		current = current->getNext();
	}
	return ;
}

/*
 *	Check semicolon after HTTP value
 */
void		CheckerTokens::checkSemicolonAfterHTTPValue( void )
{
	const Token*		current = this->_head;

	while (current && current->getNext())
	{
		if (current->getType() == Token::HTTP_V && current->getNext()->getType() != Token::HTTP_V)
			if (current->getNext()->getType() != Token::SEMICOLON)
				throw CheckerError("Expected ';' after " + current->getValue());
		current = current->getNext();
	}
	return ;
}

/*
 *	Check semicolon before block end
 */
void		CheckerTokens::checkSemicolonBeforeBlockEnd( void )
{
	const Token*		current = this->_head;

	while (current && current->getNext())
	{
		if ((current->getType() == Token::LOC_BLK_E || 
			current->getType() == Token::ERR_BLK_E) &&
			current != this->_head)
		{
			const Token*		prev = this->_head;

			while (prev->getNext()->getType() != current->getType())
				prev = prev->getNext();
			if (prev->getType() != Token::SEMICOLON)
				throw CheckerError("Expected ';' after value: " + current->getValue());
		}
		current = current->getNext();
	}
	return ;
}

/*
 *	Check unexpected semicolon
 */
void		CheckerTokens::checkUnexpectedSemicolons( void )
{
	const Token*		current = this->_head;
	const Token*		prev = NULL;

	while (current)
	{
		if (current->getType() == Token::SEMICOLON)
		{
			if (!prev || !current->getNext())
				throw CheckerError("Unexpected ';' at start or end");

			if (prev->getType() == Token::SEMICOLON)
				throw CheckerError("Unexpected consecutive ';'");

			if (!(prev->getType() == Token::DIR_V ||
				prev->getType() == Token::HTTP_V ||
				prev->getType() == Token::CGI_V ))
				throw CheckerError("Unexpected ';' after block declaration: " + prev->getValue());
		}
		prev = current;
		current = current->getNext();
	}
	return ;
}

/*
 *	Check duplicated keys in the same scope
 */
void		CheckerTokens::checkDuplicatedKeysInScope( void )
{
	std::set<std::string>		seenKeys;
	const Token*				current = this->_head;

	while (current)
	{
		if (current->getType() == Token::SERVER || 
			current->getType() == Token::LOC_BLK_S || 
			current->getType() == Token::ERR_BLK_S)
			seenKeys.clear();
		if (current->getType() == Token::DIR_K)
		{
			if (seenKeys.find(current->getValue()) != seenKeys.end())
				throw CheckerError("Duplicate directive: " + current->getValue());
			seenKeys.insert(current->getValue());
		}
		current = current->getNext();
	}
	return ;
}

/*
 *	Check the value of the directive
 */
void		CheckerTokens::checkValue( void )
{
	const Token*		current = this->_head;

	while (current && current->getNext())
	{
		if (current->getValue() == "autoindex")
		{
			std::string		val = current->getNext()->getValue();

			if (val != "on" && val != "off")
				throw CheckerError("value of \"autoindex\" not correct.");
			if (current->getNext()->getNext()->getType() != Token::SEMICOLON)
				throw CheckerError("Only one value on directive \"autoindex\".");
		}
		current = current->getNext();
	}
	return ;
}

/*
 *	Check the method HTTP
 */
void		CheckerTokens::checkMethodHTTP( void )
{
	const Token*		current = this->_head;
	
	while (current)
	{
		if (current->getType() == Token::HTTP_V)
			if (!MethodHTTP::isMethod(current->getValue()) && current->getValue() != "all")
				throw CheckerError("Method HTTP not valide: " + current->getValue());
		current = current->getNext();
	}
	return ;	
}

/*
 *	Check the final state of the tokens
 */
void		CheckerTokens::assertFinalState( void ) const
{
	if (this->_braceCount != 0)
		throw CheckerError("Mismatched braces");
	if (this->_inServer || this->_inLocation || this->_inErrorBlk)
		throw CheckerError("Unclosed block detected");
	return ;
}

/*
 *	Check if the path is a directory
 */
bool		CheckerTokens::is_valid_dir( const std::string& path )
{
	struct stat		sb;

	return (access(path.c_str(), F_OK) == 0 && stat(path.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode));
}

/*
 *	Check if the path is a file
 */
bool		CheckerTokens::is_valid_file( const std::string& path )
{
	struct stat		sb;

	return (access(path.c_str(), F_OK) == 0 && stat(path.c_str(), &sb) == 0 && S_ISREG(sb.st_mode));
}

/*
 *	Check if the path is a executable file (for cgi)
 */
bool		CheckerTokens::is_executable_file( const std::string& path )
{
	struct stat		sb;

	return (access(path.c_str(), X_OK) == 0 &&
		stat(path.c_str(), &sb) == 0 &&
		S_ISREG(sb.st_mode));
}

/*
 *	Check if the path is valid for root
 */
void		CheckerTokens::validate_root( const Token* current )
{
	const Token*		next = current->getNext();

	if (!next || !is_valid_dir(next->getValue()))
		throw CheckerError("Invalid root path: " + (next ? next->getValue() : "<missing>"));
	return ;
}

/*
 *	Check if the path is valid for index
 */
void		CheckerTokens::validate_index( const Token* current )
{
	const Token*			next = current->getNext();
	const std::string&		val = next->getValue();

	if (!(val.find("./") == 0 || (val[0] == '/' && isalnum(val[1]))))
		throw CheckerError("Invalid index path: " + val);
	return ;
}

/*
 *	Check if the path is valid for return
 */
void		CheckerTokens::validate_return( const Token* current )
{
	const Token*			next = current->getNext();
	const std::string&		val = next->getValue();

	if (val.find("http://") != 0 && access(val.c_str(), R_OK) != 0)
		throw CheckerError("Return path not readable: " + val);
	return ;
}

/*
 *	Check if the path is valid for location
 */
void		CheckerTokens::validate_location( const Token* current )
{
	const std::string&		val = current->getValue();

	if (!(val == "/" || (val[0] == '/' && isalnum(val[1]))))
		throw CheckerError("Invalid LOCATION value: " + val);
	return ;
}

/*
 *	Check if the path is valid for all value in error block
 */
const Token*		CheckerTokens::validate_error_block( const Token* current )
{
	while (current && current->getType() != Token::ERR_BLK_E)
	{
		if (current->getType() == Token::DIR_K)
		{
			const Token*		next = current->getNext();
			
			if (next && next->getType() == Token::DIR_V && !is_valid_file(next->getValue()))
				throw CheckerError("Invalid path in ERR_BLK: " + next->getValue());
			current = next;
		}
		current = current->getNext();
	}
	return (current);
}

/*
 *	Check if the path is valid for all value in token list
 */
/*void		CheckerTokens::checkpath(void)
{
	const Token*		current = this->_head;
	char				cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
		LOG_DEB("Current working directory: " << cwd);

	while (current)
	{
		if (current->getType() == Token::CGI_V)
		{
			if (!is_executable_file(current->getValue()))
				throw CheckerError("Invalid CGI_V path: " + current->getValue());
		}
		else if (current->getType() == Token::DIR_K)
		{
			if (current->getValue() == "root")
			{
				validate_root(current);
				current = current->getNext();
			}
			else if (current->getValue() == "index")
			{
				validate_index(current);
				current = current->getNext();
			}
		}
		else if (current->getType() == Token::DIR_V)
		{
			if (current->getValue() == "return")
			{
				validate_return(current);
				current = current->getNext();
			}
		}
		else if (current->getType() ==  Token::LOCATION)
			validate_location(current);
		else if (current->getType() == Token::ERR_BLK_S)
			current = validate_error_block(current->getNext());
		current = current->getNext();
	}
	return ;
}*/

void		CheckerTokens::checkUniqValue( void )
{
	const Token*		current = this->_head;

	while (current && current->getNext())
	{
		if (current->getType() == Token::DIR_K)
		{
			if (current->getValue() == "listen" ||
				current->getValue() == "root" ||
				current->getValue() == "index" ||
				current->getValue() == "max_connection_client" ||
				current->getValue() == "client_max_body_size" ||
				current->getValue() == "autoindex")
				if (current->getNext()->getNext()->getType() != Token::SEMICOLON)
					throw CheckerError("Only one value on directive " + current->getValue());
		}
		if (current->getType() == Token::CGI_K)
			if (current->getNext()->getNext()->getType() != Token::SEMICOLON)
				throw CheckerError("Only one value on CGI directive " + current->getValue());
		current = current->getNext();
	}
	return ;
}

void		CheckerTokens::checkListen( void )
{
	const Token*		current = this->_head;
	int					port;

	while (current && current->getNext() && current->getValue() != "listen")
		current = current->getNext();
	if (!current || !current->getNext())
		throw CheckerError("Missing or malformed 'listen' directive.");
	
	const std::string&		strPort = current->getNext()->getValue();
	std::istringstream		iss(strPort); 

	if (!(iss >> port) || !iss.eof())
		throw CheckerError("Port is not a valid integer.");
	if (port <= 0 || port > 65535)
		throw CheckerError("Value of port not valid.");
	return ;
}

bool		CheckerTokens::validCode( std::string code )
{
	size_t					intCode = 0;
	std::istringstream		iss(code);

	if (!code.empty() && code.size() != 3)
		return (false);
	if (!(iss >> intCode) || !iss.eof())
	{
		LOG_DEB(intCode);
		return (false);
	}
	if (intCode < 300 || intCode >= 400)
		return (false);
	return (true);
}

void		CheckerTokens::checkReturn( void )
{
	const Token*		current = this->_head;

	while (current && current->getNext())
	{
		if (current->getType() == Token::DIR_K && current->getValue() == "return")
		{
			current = current->getNext();
			if (!validCode(current->getValue()))
				throw CheckerError("Code return not valid: " + current->getValue());
			current = current->getNext();
			if (current->getNext() && current->getNext()->getType() != Token::SEMICOLON)
				throw CheckerError("Extra value on return directive: " + current->getNext()->getValue());
		}
		current = current->getNext();
	}
	return ;	
}