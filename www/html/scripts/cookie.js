/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cookie.js                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:21:07 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/07/02 15:43:19 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

// === GESTION DES COOKIES ===
class CookieManager
{
    static getCookie(name)
    {
        const value = `; ${document.cookie}`;
        const parts = value.split(`; ${name}=`);
        if (parts.length === 2)
            return decodeURIComponent(parts.pop().split(';').shift());
        return null;
    }
    
    static setCookie(name, value, maxAge = 1800)
    {
        document.cookie = `${name}=${encodeURIComponent(value)}; Path=/; Max-Age=${maxAge}`;
    }
    
    static deleteCookie(name)
    {
        document.cookie = `${name}=; Path=/; Max-Age=0`;
    }
    
    static getAllCookies()
    {
        const cookies = {};
        document.cookie.split(';').forEach(cookie =>
        {
            const [key, value] = cookie.trim().split('=');
            if (key && value)
                cookies[key] = decodeURIComponent(value);
        });
        return cookies;
    }
    
    static debugCookies()
    {
        console.log('=== DEBUG COOKIES ===');
        console.log('Document.cookie:', document.cookie);
        console.log('Tous les cookies:', this.getAllCookies());
        console.log('Cookie pseudo:', this.getCookie('pseudo'));
        console.log('Cookie session_id:', this.getCookie('session_id'));
    }
}

// === GESTION DE L'INTERFACE UTILISATEUR ===
class UIManager
{
    static updateStatusDisplay()
    {
        const pseudo = CookieManager.getCookie('pseudo') || 'Unknown';
        const statusMessage = document.getElementById('status-message');
        
        if (statusMessage)
        {
            if (pseudo === 'Unknown')
                statusMessage.textContent = 'Vous naviguez en mode anonyme';
            else
                statusMessage.textContent = `Connecte en tant que: ${pseudo}`;
        }
    }
    
    static updateSectionVisibility()
    {
        const pseudo = CookieManager.getCookie('pseudo');
        const loginSection = document.getElementById('login-section');
        const userSection = document.getElementById('user-section');
        
        if (pseudo && pseudo !== 'Unknown')
        {
            if (loginSection)
                    loginSection.style.display = 'none';
            if (userSection)
            {
                userSection.style.display = 'block';
                userSection.classList.remove('hidden');
            }
        }
        else
        {
            if (loginSection)
                loginSection.style.display = 'block';
            if (userSection)
            {
                userSection.style.display = 'none';
                userSection.classList.add('hidden');
            }
        }
    }
    
    static updateAllPseudoElements()
    {
        const pseudo = CookieManager.getCookie('pseudo') || 'Unknown';
        
        const pseudoElements = [
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
            if (element)
                element.textContent = pseudo;
        });
        
        this.updateStatusDisplay();
        this.updateSectionVisibility();
        
        window.dispatchEvent(new CustomEvent('pseudoChanged', { 
            detail: { pseudo: pseudo } 
        }));
    }
    
    static init()
    {
        this.updateAllPseudoElements();
        
        setInterval(() =>
        {
            this.updateAllPseudoElements();
        }, 1000);
        
        console.log('CookieManager et UIManager initialises');
    }
}

// === INITIALISATION ===
document.addEventListener('DOMContentLoaded', function()
{
    UIManager.init();
    CookieManager.debugCookies();
});

// === FONCTIONS GLOBALES POUR COMPATIBILITÉ ===
function getCookie(name)
{
    return CookieManager.getCookie(name);
}

function updateAllPseudoElements()
{
    UIManager.updateAllPseudoElements();
}

function debugCookies()
{
    CookieManager.debugCookies();
}