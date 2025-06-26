<?php

$_SERVER['REDIRECT_STATUS'] = '200';

header('Content-Type: application/json');
header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Methods: GET, POST');
header('Access-Control-Allow-Headers: Content-Type');

$directory = 'files';

try {
    // Créer le répertoire s'il n'existe pas
    if (!file_exists($directory)) {
        mkdir($directory, 0755, true);
    }

    $files = [];
    
    if (is_dir($directory)) {
        $items = scandir($directory);
        
        foreach ($items as $item) {
            if ($item != '.' && $item != '..' && is_file($directory . '/' . $item)) {
                $filePath = $directory . '/' . $item;
                $pathInfo = pathinfo($item);
                
                $files[] = [
                    'name' => $item,
                    'size' => filesize($filePath),
                    'modified' => filemtime($filePath),
                    'extension' => isset($pathInfo['extension']) ? $pathInfo['extension'] : '',
                    'type' => mime_content_type($filePath) ?: 'application/octet-stream'
                ];
            }
        }
        
        // Trier par nom
        usort($files, function($a, $b) {
            return strcasecmp($a['name'], $b['name']);
        });
    }
    
    echo json_encode([
        'success' => true,
        'files' => $files,
        'directory' => $directory,
        'count' => count($files)
    ]);
    
} catch (Exception $e) {
    echo json_encode([
        'success' => false,
        'message' => $e->getMessage(),
        'files' => []
    ]);
}
?>