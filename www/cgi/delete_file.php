<?php
header('Content-Type: application/json');
header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Methods: POST');
header('Access-Control-Allow-Headers: Content-Type');

// Vérifier que c'est une requête POST
if ($_SERVER['REQUEST_METHOD'] !== 'POST') {
    echo json_encode([
        'success' => false,
        'message' => 'Méthode non autorisée'
    ]);
    exit;
}

$directory = 'deleteable';
$response = ['success' => false, 'message' => ''];

try {
    // Vérifier que le nom du fichier est fourni
    if (!isset($_POST['filename']) || empty($_POST['filename'])) {
        throw new Exception('Nom du fichier manquant');
    }
    
    $filename = $_POST['filename'];
    $filePath = $directory . '/' . $filename;
    
    // Vérifications de sécurité
    if (strpos($filename, '..') !== false || strpos($filename, '/') !== false || strpos($filename, '\\') !== false) {
        throw new Exception('Nom de fichier non autorisé');
    }
    
    // Vérifier que le fichier existe
    if (!file_exists($filePath)) {
        throw new Exception('Fichier non trouvé');
    }
    
    // Vérifier que c'est bien un fichier (pas un répertoire)
    if (!is_file($filePath)) {
        throw new Exception('L\'élément spécifié n\'est pas un fichier');
    }
    
    // Vérifier que le fichier est dans le bon répertoire (sécurité)
    $realFilePath = realpath($filePath);
    $realDirectory = realpath($directory);
    
    if (!$realFilePath || !$realDirectory || strpos($realFilePath, $realDirectory) !== 0) {
        throw new Exception('Accès non autorisé au fichier');
    }
    
    // Tenter la suppression
    if (unlink($filePath)) {
        $response = [
            'success' => true,
            'message' => 'Fichier supprimé avec succès',
            'filename' => $filename
        ];
        
        // Log de la suppression (optionnel)
        error_log("Fichier supprimé: $filePath par " . ($_SERVER['REMOTE_ADDR'] ?? 'IP inconnue'));
        
    } else {
        throw new Exception('Impossible de supprimer le fichier');
    }
    
} catch (Exception $e) {
    $response = [
        'success' => false,
        'message' => $e->getMessage()
    ];
    
    // Log des erreurs
    error_log("Erreur suppression fichier: " . $e->getMessage());
}

echo json_encode($response);
?>