document.addEventListener("DOMContentLoaded", function ()
{
	const statusMessage = document.getElementById("pwd");
	const params = new URLSearchParams(window.location.search);
	const pwd = params.get("pwd");

	if (pwd)
    {
		statusMessage.textContent = "Mot de passe genere : " + decodeURIComponent(pwd);
		statusMessage.style.fontWeight = "bold";
		statusMessage.style.color = "green";
	}
    else
    {
		statusMessage.textContent = "Pour generer votre mot de passe, utilisez le formulaire ci-dessus.";
	}
});