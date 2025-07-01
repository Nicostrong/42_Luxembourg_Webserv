// Fonction pour lire un cookie spécifique
function getCookie(name)
{
    const value = `; ${document.cookie}`;
    const parts = value.split(`; ${name}=`);
    if (parts.length === 2)
		{
        return decodeURIComponent(parts.pop().split(';').shift());
    }
    return null;
}

// Fonction pour mettre à jour l'affichage du statut
function updateStatusDisplay()
{
    const pseudo = getCookie('pseudo') || 'Unknown';
    const statusMessage = document.getElementById('status-message');
    
    if (statusMessage)
	{
        if (pseudo === 'Unknown')
		{
            statusMessage.textContent = 'Vous naviguez en mode anonyme';
        }
		else
		{
            statusMessage.textContent = `Connecte en tant que: ${pseudo}`;
        }
    }
}

// Fonction pour mettre à jour tous les éléments avec le pseudo
function updateAllPseudoElements()
{
    const pseudo = getCookie('pseudo') || 'Unknown';
    
    // Liste des IDs d'éléments à mettre à jour
    const pseudoElements =
	[
        'pseudo-display',
        'pseudo-guest', 
        'pseudo-user',
        'pseudo-welcome',
        'pseudo-footer',
        'current-user',
        'user-name'
    ];
    
    pseudoElements.forEach(id =>
	{
        const element = document.getElementById(id);
        if (element) {
            element.textContent = pseudo;
        }
    });
    
    // Mettre à jour le statut
    updateStatusDisplay();
}

// Initialiser au chargement de la page
document.addEventListener('DOMContentLoaded', function()
{
    updateAllPseudoElements();
});

// Vérifier les changements de cookies périodiquement
setInterval(updateAllPseudoElements, 1000);

// Fonction utilitaire pour débugger les cookies
function debugCookies()
{
    console.log('Tous les cookies:', document.cookie);
    console.log('Cookie pseudo:', getCookie('pseudo'));
}