/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 06:55:53 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/05/12 13:13:25 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Token.hpp"

Token::Token( Type type, const std::string& value ) : _type(type), _value(value), _next(NULL)
{
	return ;
}

Token::Token( const Token& src_obj ) : _type(src_obj._type), _value(src_obj._value), _next(NULL)
{
	if (src_obj._next)
		this->_next = new Token(*src_obj._next);
	return ;
}

Token::~Token( void )
{
	delete this->_next;
	return ;
}

Token&		Token::operator=( const Token& src_obj )
{
	if (this != &src_obj)
	{
		this->_type = src_obj._type;
		this->_value = src_obj._value;
		
		Token*		next = NULL;
		if (src_obj._next)
			next = new Token(*src_obj._next);
		delete this->_next;
		this->_next = next;
	}
	return (*this);
}

void		Token::deleteChain( Token* head )
{
	while (head)
	{
		Token*		tmp = head;

		head = head->_next;
		tmp->_next = NULL;
		delete tmp;
	}
	return ;
}

void			Token::setNextToNull( void )
{
	this->_next = NULL;
	return ;
}

int				Token::getType( void ) const { return (this->_type); }

std::string		Token::getValue( void ) const { return (this->_value); }

std::string		Token::getTypeName( void ) const
{
	static const char*	typeNames[] = {
			BLUE "SERVER" RESET,
			BLUE "SER_BLK_S" RESET,
			BLUE "SER_BLK_E" RESET,
			RED "ERROR_PAGE" RESET,
			RED "ERR_BLK_S" RESET,
			RED "ERR_BLK_E" RESET,
			YELLOW "LOCATION" RESET,
			YELLOW "LOC_BLK_S" RESET,
			YELLOW "LOC_BLK_E" RESET,
			"HTTP_K", "HTTP_V", "DIR_K", "DIR_V", "SEMICOLON"
	};
	
	if (this->_type >= SERVER && this->_type <= SEMICOLON)
		return (typeNames[this->_type - SERVER]);
	return ("UNKNOWN_TYPE");
}

Token*		Token::getNext( void ) const { return (this->_next); }

void		Token::printToken( bool isNext ) const
{
	if (!isNext)
		std::cout << "\t";
	std::cout << "Token [" << getTypeName() << "] - Value: " << this->_value << std::endl;
	if (this->_next)
	{
		std::cout << "Next -> ";
		this->_next->printToken(true);
	}
	return ;
}

/*
 *	List of valid key
 */
static const std::string	directiveKeys[] = {
	"listen", "server_name", "root", "index", "max_connection_client",
	"client_max_body_size", "return", "autoindex"
};

/*
 *	Check if the key is a valid key
 */
bool		Token::isDirectiveKey( const std::string& word )
{
	for (size_t i = 0; i < sizeof(directiveKeys) / sizeof(*directiveKeys); ++i)
		if (word == directiveKeys[i])
			return true;
	return (false);
}

/*
 *	Gestion des directives
 */
Token*		Token::createDirective(	std::istringstream& iss, const std::string& word,
									Token*& head, Token*& current)
{
	Token*		dirKey = new Token(Token::DIR_K, word);

	attachToken(head, current, dirKey);

	std::string		valueWord;
	std::string		semiCheck;
	
	if (!(iss >> valueWord))
		throw ParserServerConfig::ParsingError("Missing value after directive '" + word + "'");
	
	Token*		dirVal = new Token(Token::DIR_V, valueWord);

	attachToken(head, current, dirVal);
	if (!(iss >> semiCheck) || semiCheck != ";")
		throw ParserServerConfig::ParsingError("Expected ';' after directive value for '" + word + "'");

	Token*		semi = new Token(Token::SEMICOLON, ";");

	attachToken(head, current, semi);
	return (current);
}

/*
 *	Reliage des Tokens
 */
void		Token::attachToken( Token*& head, Token*& current, Token* newToken )
{
	if (!head)
		head = newToken;
	else
		current->_next = newToken;
	current = newToken;
	return ;
}



/*
 *	Create a Location Token
 */
Token*		Token::createLocation(	std::istringstream& iss, Token*& head, 
									Token*& current, int& braceCount,
									bool& inLocation )
{
	std::string		path;
	std::string		brace;
	std::string		token;

	if (!(iss >> path))
		throw ParserServerConfig::ParsingError("Expected path after 'location'");

	Token*		locKey = new Token(Token::LOCATION, "location " + path);

	attachToken(head, current, locKey);
	if (!(iss >> brace) || brace != "{")
		throw ParserServerConfig::ParsingError("Expected '{' after location path");
	braceCount++;

	Token*		locStart = new Token(Token::LOC_BLK_S, "{");

	attachToken(head, current, locStart);
	inLocation = true;
	while (iss >> token && token != "}")
	{
		if (token == "allow")
		{
			std::string		method;

			attachToken(head, current, new Token(Token::HTTP_K, token));
			while (iss >> method && method != ";")
				attachToken(head, current, new Token(Token::HTTP_V, method));
			if (method != ";")
				throw ParserServerConfig::ParsingError("Missing ';' after allow");
			attachToken(head, current, new Token(Token::SEMICOLON, ";"));
		}
		else if (isDirectiveKey(token))
			createDirective(iss, token, head, current);
		else
			throw ParserServerConfig::ParsingError("Unknown directive inside location block: " + token);
	}
	if (token != "}")
		throw ParserServerConfig::ParsingError("Missing closing '}' after location block");

	Token*		locEnd = new Token(Token::LOC_BLK_E, "}");
	
	attachToken(head, current, locEnd);
	inLocation = false;
	braceCount--;
	return (current);
}

/*
 *	Create an Error Token
 */
Token*		Token::createErrorPage(	std::istringstream& iss,
									std::string word,
									Token*& head,
									Token*& current,
									int& braceCount,
									bool& inErrorBlk )
{
	Token*			errorStart = new Token(Token::ERROR_PAGE, word);
	std::string		next;
    std::string		code;
	std::string		path;
	std::string		semi;

	attachToken(head, current, errorStart);
	if (!(iss >> next) || next != "{")
		throw ParserServerConfig::ParsingError("Expected '{' after error_page");
	braceCount++;

	Token*			errBraceStart = new Token(Token::ERR_BLK_S, "{");

	attachToken(head, current, errBraceStart);
	inErrorBlk = true;
	while (iss >> code && code != "}")
	{
		if (!(iss >> path))
			throw ParserServerConfig::ParsingError("Missing path after error code '" + code + "'");
		if (!(iss >> semi) || semi != ";")
			throw ParserServerConfig::ParsingError("Missing ';' after error_page value");
		attachToken(head, current, new Token(Token::DIR_K, code));
		attachToken(head, current, new Token(Token::DIR_V, path));
		attachToken(head, current, new Token(Token::SEMICOLON, ";"));
	}
	if (code != "}")
		throw ParserServerConfig::ParsingError("Missing closing '}' after error_page block");
	
	Token*			errBraceEnd = new Token(Token::ERR_BLK_E, code);
	
	attachToken(head, current, errBraceEnd);
	inErrorBlk = false;
	braceCount--;
	return (current);
}


/*
 *	Gestion des braces { et }
 */
Token*		Token::createBrace(	const std::string& word, Token*& head, Token*& current,
								int& braceCount, bool& inLocation, bool& inErrorBlk,
								bool& inServer)
{
	Token*		blk = new Token(word == "{" ? Token::SER_BLK_S : Token::SER_BLK_E, word);

	attachToken(head, current, blk);
	if (word == "{")
	{
		braceCount++;
		if (inServer)
			return (current);
		!inErrorBlk ? inErrorBlk = true : 
		!inLocation ? inLocation = true : 
		throw ParserServerConfig::ParsingError("Unexpected '{' inside a block");
	}
	else 
	{
		braceCount--;
		inLocation ? inLocation = false :
		inErrorBlk ? inErrorBlk = false :
		inServer ? inServer = false :
		throw ParserServerConfig::ParsingError("Unexpected '}' inside a block");
	}
	return (current);
}

/*
 *	Gestion du semicolon
 */
Token*		Token::createSemicolon(	const std::string& word, Token*& head,
									Token*& current, bool& inHTTP)
{
    Token*		semi = new Token(Token::SEMICOLON, word);

    attachToken(head, current, semi);
    inHTTP = false;
    return (current);
}

Token*		Token::tokenize( const std::string& input )
{
	std::istringstream		iss(input);
	std::string				word;
	Token*					head = NULL;
	Token*					current = NULL;
	int						braceCount = 0;
	bool					inServer = false;
	bool					inLocation = false;
	bool					inErrorBlk = false;
	bool					inHTTP = false;

	try
	{
		while (iss >> word)
		{
			if (word == "{" || word == "}")
				current = createBrace(word, head, current, braceCount, inLocation, inErrorBlk, inServer);
			else if (word == "server")
			{
				Token*		serverTok = new Token(Token::SERVER, word);
				
				attachToken(head, current, serverTok);
				inServer = true;
			}
			else if (!inServer && word != "server" && word != "}")
				throw ParserServerConfig::ParsingError("Unexpected data outside server block");
			else if (word == "location")
				current = createLocation(iss, head, current, braceCount, inLocation);
			else if (word == "error_page")
				current = createErrorPage(iss, word, head, current, braceCount, inErrorBlk);
			else if (word == ";")
				current = createSemicolon(word, head, current, inHTTP);
			else if (isDirectiveKey(word))
				current = createDirective(iss, word, head, current);
			else
				throw ParserServerConfig::ParsingError("Unknown directive: " + word);
		}

		if (braceCount != 0)
			throw ParserServerConfig::ParsingError("Mismatched braces: some '{' or '}' are not closed properly");
		if (inLocation || inErrorBlk || inHTTP || inServer)
			throw ParserServerConfig::ParsingError("Unclosed block.");
	}
	catch ( const std::exception& e )
	{
		deleteChain(head);
		throw ;
	}
	return (head);
}

#ifdef TEST

int main( void )
{
	try
	{
		std::string		config = "{ listen 8080 ; server_name localhost ; \
									root ./www/html ; index index.html ; \
									max_connection_client 10 ; client_max_body_size 5M ; \
									error_page { 403 ./errors/403.html ; \
									404 ./errors/404.html ; 405 ./errors/405.html ; \
									409 ./errors/409.html ; 413 ./errors/413.html ; \
									418 ./errors/418.html ; 500 ./errors/500.html ; } \
									location / { autoindex off ; allow GET POST DELETE HEAD ; } } ";
		
		Token*			tokens = Token::tokenize(config);
		
		std::cout << "Pointeur de HEAD: " << tokens << std::endl;
		tokens->printToken();
		
		delete tokens;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);
	}
	return (0);
}

#endif