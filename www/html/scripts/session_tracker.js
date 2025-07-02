/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session_tracker.js                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:11:09 by nfordoxc          #+#    #+#             */
/*   Updated: 2025/07/02 15:16:12 by nfordoxc         ###   Luxembourg.lu     */
/*                                                                            */
/* ************************************************************************** */

class SessionTracker
{
    constructor()
    {
        this.sessionData = null;
    }
    
    async initSession()
    {
        try
        {
            const response = await fetch('/cgi/session_manager.py');
            this.sessionData = await response.json();
            
            if (this.sessionData.success)
                {
                console.log('Session initialisee:', this.sessionData);
                this.updateDisplay();
                return true;
            }
            else
            {
                console.error('Erreur session:', this.sessionData.error);
                return false;
            }
        }
        catch (error)
        {
            console.error('Erreur lors de l\'initialisation de session:', error);
            return false;
        }
    }
    
    updateDisplay()
    {
        if (!this.sessionData) return;
        
        // Mettre à jour le message de statut
        const statusMessage = document.getElementById('status-message');
        if (statusMessage)
            {
            const pagesCount = this.sessionData.visited_pages.length;
            const visitsCount = this.sessionData.total_visits;
            statusMessage.textContent = `Session active - ${pagesCount} page(s) visitee(s) - ${visitsCount} visite(s) totale(s)`;
        }
        
        // Ajouter les informations de session
        this.addSessionInfo();
    }
    
    addSessionInfo()
    {
        let sessionInfo = document.getElementById('session-info');
        if (!sessionInfo)
        {
            sessionInfo = document.createElement('div');
            sessionInfo.id = 'session-info';
            sessionInfo.style.cssText = `
                margin-top: 15px; 
                padding: 10px; 
                background: #f5f5f5; 
                border-radius: 5px; 
                font-size: 12px; 
                color: #666;
            `;
            
            const container = document.querySelector('.container');
            if (container)
                container.appendChild(sessionInfo);
        }
        
        const duration = this.calculateSessionDuration();
        
        sessionInfo.innerHTML = `
            <strong>Informations de Session</strong><br>
            <strong>ID:</strong> ${this.sessionData.session_id}<br>
            <strong>Nouvelle session:</strong> ${this.sessionData.new_session ? 'Oui' : 'Non'}<br>
            <strong>Pages visitees:</strong> ${this.sessionData.visited_pages.join(', ')}<br>
            <strong>Nombre total de visites:</strong> ${this.sessionData.total_visits}<br>
            <strong>Duree de session:</strong> ${duration}
        `;
    }
    
    calculateSessionDuration()
    {
        // Cette fonction sera améliorée quand on aura les timestamps
        return "Calcule cote client";
    }
}

// Initialiser la session au chargement de la page
const sessionTracker = new SessionTracker();

// Appeler la session ET votre code existant
document.addEventListener('DOMContentLoaded', async function()
{
    await sessionTracker.initSession();
});