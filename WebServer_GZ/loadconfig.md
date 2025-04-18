So far Nice wants:

a map <str, map<str, str>>
he wants like
listen					127.0.0.1:8080;

location /
{
		autoindex			off;
		limit_except 		GET POST DELETE HEAD {
			deny			all;
		}
	}