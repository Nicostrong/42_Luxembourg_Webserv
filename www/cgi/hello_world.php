<?php
http_response_code(200);
header("Content-Type: text/html; charset=utf-8");

$html = '
<html>
	<head>
		<title>WEBSERVER - Hello World PHP - WEBSERVER</title>
		<link rel="stylesheet" href="/styles/style.css">
		<link rel="icon" href="/images/favicon.png" type="image/png">
		<script src="/scripts/cookie.js"></script>
		<script src="/scripts/session.js"></script>
	</head>
	<body>
		<header class="header">
			<a href="/" class="banner-link">
				<h1>Welcome on the WebServer of GneugneuTeam.</h1>
			</a>
		</header>
		<nav class="navbar">
			<a	href="/html/upload.html">Upload</a>
			<a	href="/html/download.html">Download</a>
			<a	href="/html/delete.html">Delete</a>
			<a	href="/html/pwd_generator.html">PWD generator</a>
			<a	href="/cgi/hello_world.py">Hello World Python</a>
			<a	href="/cgi/hello_world.php">Hello World PHP</a>
			<a	href="/cgi/timeout.py">Timeout</a>
			<a	href="/cgi/fish.py">Fish</a>
			<a	href="/cgi/notfound.py">Not Found GET</a>
		</nav>
		<div class="container">
			<h1>Hello World in PHP !</h1>
			<div id="status-section" class="user-status">
				<div class="info">
					<span id="status-message">Chargement...</span>
				</div>
			</div>
		</div>
	</body>
</html>
';

echo $html;
?>