<?php
http_response_code(200);
header("Content-Type: text/html; charset=utf-8");

$html = '
<html>
<head>
	<title>WEBSERVER - Hello World PHP - WEBSERVER</title>
	<link rel="stylesheet" href="http://localhost:8080/styles/style.css">
	<link rel="icon" href="http://localhost:8080/images/favicon.png" type="image/png">
</head>
<body>
	<header class="header">
			<a href="http://localhost:8080/index.html" class="banner-link">
				<h1>Welcome on the WebServer of GneugneuTeam.</h1>
			</a>
		</header>
		<nav class="navbar">
			<a	href="http://localhost:8080/upload.html">Upload</a>
			<a	href="http://localhost:8080/download.html">Download</a>
			<a	href="http://localhost:8080/delete.html">Delete</a>
			<a  href="http://localhost:8080/new.html">New</a>
			<a	href="http://localhost:8080/cgi/hello_world.py">Hello World Python</a>
			<a	href="http://localhost:8080/cgi/hello_world.php">Hello World PHP</a>
		</nav>
	<h1>Hello World in PHP !</h1>
</body>
</html>
';

echo $html;
?>