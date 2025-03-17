# Minishell

# Créer la branche "Luc"
git branch Luc
# Se place sur la branche "Luc"
git checkout Luc  
# Ou en une seule commande plus moderne :
git switch -c Luc

# Ajoute tous les fichiers modifiés
git add .
git commit -m "Message clair sur le travail effectué"

# La première fois
git push -u origin Luc
# Les fois suivantes
git push

# Fusionner les changement sur la branche main

# Basculer sur la branche principale
git checkout main
# Récupérer les dernières mises à jour
git pull origin main
# Fusionner ma branche avec la main
git merge Luc
# Envoyer les modifications fusionnées vers le repo distant
git push origin main

# Supprimer la branche à la fin

# Supprime la branche localement
git branch -d Luc
# Supprime la branche sur le repo distant
git push origin --delete Luc

# Il faut fusionner régulièrement avec le main pour éviter au maximum les conflits
git checkout Luc
# Récupérer les dernières modifs de main
git pull origin main
# Fusionner main dans ta branche Luc
git merge main
