<?php

$_SERVER['REDIRECT_STATUS'] = '200';

header('Content-Type: application/json');
header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Methods: GET, POST');
header('Access-Control-Allow-Headers: Content-Type');

$directory = __DIR__ . '/../files';

try
{
	$directory = realpath($directory);

	$files = [];
	
	if (is_dir($directory))
	{
		$items = scandir($directory);
		
		if ($items === false)
			throw new Exception("Impossible de lire le repertoire : $directory");
		
		foreach ($items as $item)
		{
			if ($item != '.' && $item != '..' && is_file($directory . '/' . $item))
			{
				$filePath = $directory . '/' . $item;
				$pathInfo = pathinfo($item);
				
				if (!is_readable($filePath))
					continue;
				
				$files[] = [
					'name' => $item,
					'size' => filesize($filePath),
					'modified' => filemtime($filePath),
					'extension' => isset($pathInfo['extension']) ? strtolower($pathInfo['extension']) : '',
					'type' => function_exists('mime_content_type') ? 
						(mime_content_type($filePath) ?: 'application/octet-stream') : 
						'application/octet-stream'
				];
			}
		}
		
		// Trier par nom
		usort($files, function($a, $b)
		{
			return strcasecmp($a['name'], $b['name']);
		});
	}
	else
	{
		throw new Exception("Le repertoire n'existe pas ou n'est pas accessible : $directory");
	}
	
	echo json_encode([
		'success' => true,
		'files' => $files,
		'directory' => basename($directory),
		'count' => count($files),
	]);
	echo "";
}
catch (Exception $e)
{
	echo json_encode([
		'success' => false,
		'message' => $e->getMessage(),
		'files' => [],
		'debug_info' => [
			'current_dir' => __DIR__,
			'target_dir' => isset($directory) ? $directory : 'non défini',
			'file_exists' => isset($directory) ? file_exists($directory) : false,
			'is_dir' => isset($directory) ? is_dir($directory) : false,
			'is_readable' => isset($directory) ? is_readable($directory) : false
		]
	]);
}
?>