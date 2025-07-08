/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:58:27 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/07/08 15:52:56 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
# define CGI_HPP

# include "../lib.hpp"
# include "../utils/Fd.hpp"
# include "../utils/Uri.hpp"
# include "../utils/Pipe.hpp"
# include "../utils/Buffer.hpp"
# include "../server/Location.hpp"
# include "../networking/Body.hpp"
# include "../events/IEventHandler.hpp"
# include "../events/EventMonitoring.hpp"

# define BUFF_SIZE 1024

class	Socket;

class	CGI:	public IEventHandler
{

	public:

		typedef std::map<std::string, std::string>	Map;

	private:

		std::string		_scriptPath;	//	path complet of the script to execute
		std::string		_binaryExec;	//	path of binary to exec the script
		std::string		_query;			//	querry parameters
		size_t			_byteRead;		//	number of bytes read
		size_t			_byteSend;		//	number of bytes send
		char**			_params;		//	parameters of execution
		char**			_aEnv;			//	env variables
		Pipe			_toCGI;			//	to send data to CGI
		Pipe			_fromCGI;		//	response from the CGI
		Buffer			_txBuffer;		//	transmit buffer
		Buffer			_rxBuffer;		//	receive buffer
		Socket*			_socket;		//	socket of communication
		Map				_mEnv;			//	map of environnement variable
		pid_t			_pid;			//	pid parent
		int				_exitCode;		//	Exit code
		
		// To know if CGI execution is finished
		bool			_isCloseEvent;
		bool			_isReadEvent;
		bool			_isTransferFinished;
		bool			_isExited;		//	Does the cgi is finished


		CGI( void );
		CGI( const CGI& );

		CGI&			operator=( const CGI & );

		void			setMap( void );
		void			setEnv( void );
		void			initMap( void );
		void			checkCGI( void );
		void			setParams( void );

		std::string		normalizePath( const std::string& path );

		void			onCgiError(EventMonitoring& em);
		void			onEndOutput(EventMonitoring& em);
		void			onEndInput(EventMonitoring& em);

	public:

		CGI( Socket& socket );
		~CGI( void );

		/*	GETTER	*/
		std::string&	getScriptPath( void );
		std::string&	getBinaryPath( void );
		std::string&	getQuery( void );

		size_t			getByteRead( void );
		size_t			getByteSend( void );

		char**			getParams( void );
		char**			getEnv( void );

		Pipe&			getPipeToCGI( void );
		Pipe&			getPipeFromCGI( void );

		Buffer&			getTxBuffer( void );
		Buffer&			getRxBuffer( void );

		Socket&			getSocket( void );

		Map&			getMapEnv( void );

		pid_t			getPid( void );
		bool			isCgiFinished() const;
		bool			isOutputFinished() const;

		/*	SETTER	*/
		void			setPid( pid_t pid );
		void			resetByteRead( void );
		void			resetByteSend( void );
		void			setByteRead( size_t bytes );
		void			setByteSend( size_t bytes );

		/*	METHODS	*/
		void			execCGI( void );

		/*	EVENT	*/
		void			onReadEvent( int fd, EventMonitoring& em );
		void			onWriteEvent( int fd, EventMonitoring& em );
		void			onCloseEvent( int fd, EventMonitoring& em );
		void			onTickEvent( int fd, EventMonitoring& em );

		class	CGIError: public std::exception
		{

			private:

				std::string		_msg;

			public:

				CGIError( const std::string &error ) throw();
				virtual ~CGIError( void ) throw();
				virtual const char*		what() const throw();
		
		};

		class	CGIExit: public std::exception
		{
			private:
				std::string		_msg;
			public:
				CGIExit() throw();
				virtual ~CGIExit( void ) throw();
				const char*		what() const throw();
		};
};

std::ostream	&operator<<( std::ostream &out, CGI& src_object );

#endif