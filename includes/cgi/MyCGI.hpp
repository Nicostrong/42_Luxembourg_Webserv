/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyCGI.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:58:27 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/06/26 15:43:12 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYCGI
# define MYCGI

# include "../lib.hpp"
# include "../utils/Uri.hpp"
# include "../utils/Pipe.hpp"
# include "../utils/Buffer.hpp"
# include "../server/Location.hpp"
# include "../networking/Body.hpp"
# include "../events/IEventHandler.hpp"
# include "../events/EventMonitoring.hpp"

# define BUFF_SIZE 1024

class	Socket;

class	MyCGI:	public IEventHandler
{

	public:

		typedef std::map<std::string, std::string>	Map;

	private:

		std::string		_scriptPath;	//	path complet of the script to execute
		std::string		_binaryExec;	//	path of binary to exec the script
		std::string		_query;			//	querry parameters
		size_t			_byteRead;		//	number of bytes read
		char**			_params;		//	parameters of execution
		char**			_aEnv;			//	env variables
		Pipe			_toCGI;			//	to send data to CGI
		Pipe			_fromCGI;		//	response from the CGI
		Buffer			_txBuffer;		//	transmit buffer
		Buffer			_rxBuffer;		//	receive buffer
		Socket*			_socket;		//	socket of communication
		Map				_mEnv;			//	map of environnement variable
		pid_t			_pid;			//	pid parent
		bool			_isFinish;		//	if the CGI has finished
		bool			_endWrite;		//	if the parent has finish to write on the pipe

		MyCGI( void );
		MyCGI( const MyCGI& );

		MyCGI&			operator=( const MyCGI & );

		void			setMap( void );
		void			setEnv( void );
		void			initMap( void );
		void			checkCGI( void );
		void			setParams( void );

	public:

		MyCGI( Socket& socket );
		~MyCGI( void );

		/*	GETTER	*/
		std::string&	getScriptPath( void );
		std::string&	getBinaryPath( void );
		std::string&	getQuery( void );

		size_t			getByteRead( void );

		char**			getParams( void );
		char**			getEnv( void );

		Pipe&			getPipeToCGI( void );
		Pipe&			getPipeFromCGI( void );

		Buffer&			getTxBuffer( void );
		Buffer&			getRxBuffer( void );

		Socket&			getSocket( void );

		Map&			getMapEnv( void );

		pid_t			getPid( void );

		bool			getIsFinish( void );
		bool			getEndWrite( void );

		/*	SETTER	*/
		void			setPid( pid_t pid );
		void			resetByteRead( void );
		void			setByteRead( size_t bytes );
		void			setIsFinish( bool value = true );
		void			setEndWrite( bool value = true );

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
};

std::ostream	&operator<<( std::ostream &out, MyCGI& src_object );

#endif