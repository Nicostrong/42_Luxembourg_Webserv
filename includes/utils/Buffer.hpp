/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Buffer.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:05:10 by fdehan            #+#    #+#             */
/*   Updated: 2025/07/08 15:40:05 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_HPP
# define BUFFER_HPP

# include "../lib.hpp"

class	Buffer
{
    public:

		class NoSpaceAvailable : public std::exception {
			public:
				const char * what () const throw();
		};

        Buffer(size_t bufferSize);
        Buffer(const Buffer& obj);
        ~Buffer();

        Buffer&						operator=(const Buffer& obj);

		std::vector<char>&			getVector();
		const std::vector<char>&	getVector() const;
		char*						getData();
		const char*					getData() const;
		char*						getDataUnused();
		char*						getDataUnread();
		size_t						getBufferUsed() const;
		size_t						getBufferRead() const;
		size_t						getBufferUnused() const;
		size_t						getBufferUnread() const;
		size_t						getBufferSize()	const;
		void						setBufferRead(size_t n);
		void						setBufferUsed(size_t n);
		bool						isBufferFull() const;
		bool						isBufferRead() const;
		std::vector<char>::iterator	beginUnused();
		std::vector<char>::iterator	beginUnread();
		void						copyFrom(Buffer& buff, size_t pos = 0, size_t n = std::string::npos);
		void						copyFrom(const std::string& buff, size_t pos = 0, size_t n = std::string::npos);
		size_t						find(const char& c, size_t pos = 0,
											size_t n = std::string::npos) const;
		size_t						find(const std::string& str, size_t pos = 0,
											size_t n = std::string::npos) const;
		size_t						find(const char* str, size_t pos = 0,
											size_t n = std::string::npos) const;
		char&						at(size_t n);
		const char&					at(size_t n) const;
		bool						startWith(const char& c, size_t pos = 0,
											size_t n = std::string::npos);
		bool						startWith(const std::string& str, 
											size_t pos = 0, 
											size_t n = std::string::npos);
		bool						startWith(const char* str, size_t pos = 0,
											size_t n = std::string::npos);
		void 						alignData();
		void 						reset();
		void						resetIfRead();

    private:

        std::vector<char>	_buffer;
        size_t				_bufferSize;
		size_t				_bufferUsed;
		size_t				_bufferRead;
		
};

std::ostream& operator<<(std::ostream& os, const Buffer& obj);

#endif