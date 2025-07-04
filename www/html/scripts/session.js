function getCookie(name)
{
	const value = `; ${document.cookie}`;
	const parts = value.split(`; ${name}=`);
	if (parts.length === 2) return parts.pop().split(';').shift();
	return null;
}

window.addEventListener('DOMContentLoaded', () =>
{
	const session = getCookie("PHPSESSID");
	if (!session)
    {
		const script = document.createElement('script');
		script.src = "/cgi/create_session.php";
		document.head.appendChild(script);
	}
});