// Function pour obtenir la valeur d'un cookie
function getCookie(name)
{
	const value = `; ${document.cookie}`;
	const parts = value.split(`; ${name}=`);
	if (parts.length === 2) return parts.pop().split(';').shift();
	return null;
}

// Function pour définir un cookie
function setCookie(name, value, days = 30)
{
	const date = new Date();
	date.setTime(date.getTime() + (days * 24 * 60 * 60 * 1000));
	const expires = `expires=${date.toUTCString()}`;
	document.cookie = `${name}=${value};${expires};path=/`;
}

// Function pour supprimer un cookie
function deleteCookie(name)
{
	document.cookie = `${name}=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;`;
}

// Function pour afficher le formulaire de saisie du pseudo
function showPseudoForm()
{
	const mainContent = document.getElementById('mainContent');
	mainContent.innerHTML = `
		<p>Veuillez entrer votre pseudo pour continuer :</p>
		<div class="form-container">
			<input type="text" id="pseudoInput" placeholder="Votre pseudo" maxlength="50">
			<button onclick="savePseudo()">Valider</button>
		</div>
		<div id="errorMessage" class="error"></div>
	`;
	
	// Focus sur le champ de saisie
	document.getElementById('pseudoInput').focus();
	
	// Permettre la validation avec Enter
	document.getElementById('pseudoInput').addEventListener('keypress', function(e) {
		if (e.key === 'Enter') {
			savePseudo();
		}
	});
}

// Function pour afficher le message de bienvenue
function showWelcomeMessage(pseudo)
{
	const mainContent = document.getElementById('mainContent');
	mainContent.innerHTML = `
		<div class="welcome-message">
			Bienvenu "${pseudo}" sur le site
		</div>
		<p>Vous êtes maintenant connecté avec le pseudo : <strong>${pseudo}</strong></p>
		<button class="logout-btn" onclick="logout()">Changer de pseudo</button>
	`;
}

// Function pour sauvegarder le pseudo
function savePseudo()
{
	const pseudoInput = document.getElementById('pseudoInput');
	const pseudo = pseudoInput.value.trim();
	const errorDiv = document.getElementById('errorMessage');
	
	// Validation du pseudo
	if (pseudo === '') {
		errorDiv.textContent = 'Veuillez entrer un pseudo valide.';
		pseudoInput.focus();
		return;
	}
	
	if (pseudo.length < 2) {
		errorDiv.textContent = 'Le pseudo doit contenir au moins 2 caractères.';
		pseudoInput.focus();
		return;
	}
	
	setCookie('pseudo', pseudo);
	
	showWelcomeMessage(pseudo);
}

// Function pour se déconnecter (supprimer le cookie)
function logout()
{
	deleteCookie('pseudo');
	showPseudoForm();
}

// Function principale pour initialiser la page
function initializePage()
{
	const pseudo = getCookie('pseudo');
	
	if (pseudo && pseudo.trim() !== '')
	{
		// Le cookie pseudo existe, afficher le message de bienvenue
		showWelcomeMessage(pseudo);
	}
	else
	{
		// Le cookie pseudo n'existe pas, afficher le formulaire
		showPseudoForm();
	}
}

// Initialiser la page au chargement
document.addEventListener('DOMContentLoaded', initializePage);