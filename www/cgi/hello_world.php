<?php
http_response_code(200);
header("Content-Type: text/html; charset=utf-8");

$html = '
<html>
<head>
    <meta charset="UTF-8">
    <title>WEBSERVER - upload - WEBSERVER</title>
    <link rel="stylesheet" href="http://localhost:8080/styles/style.css">
    <link rel="icon" href="http://localhost:8080/images/favicon.png" type="image/png">
</head>
<body>
	<div class="header">
		<h1>Welcone on the WebServer of GneugneuTeam.</h1>
	</div>
    <div class="navbar">
        <a href="/index.html">Index</a>
    </div>
    <h1>Hello World !</h1>
</body>
</html>
';

echo $html;
?>