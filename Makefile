# Call tout les fonctions pour vérifier que tout fonction
.PHONY: philo_sol philo_test philo_plot philo_clean

# Run philo & prod/cons & lect/ecriv
all: sol test plot

sol: philo_sol prod_sol lect_sol

test:
	bash ./experiments.sh

plot:
	./1_philosophes/plot.py
	./2_producteurs_consommateurs/plot.py
	./3_lecteurs_ecrivains/plot.py

clean: philo_clean prod_clean lect_clean

#-----------------------Le problème des philosophes ---------------------------

philo_sol:  	# Compile -> solutions.exe
	make -C 1_philosophes sol 

philo_test: 	# Run les 5 threads et stocke les données dans un csv
	make -C 1_philosophes test

philo_plot:  	# Plot le schéma des données stockées
	make -C 1_philosophes plot

philo_clean: 	# Nettoie le dossier compiled
	make -C 1_philosophes clean

philo_all: philo_clean philo_plot

#-------------- Le problème des producteurs et consommateurs ------------------

prod_sol:		# Compile -> solutions.exe 
	make -C 2_producteurs_consommateurs sol

prod_test:		# Run les 5 threads et stocke les données dans un csv
	make -C 2_producteurs_consommateurs test

prod_plot:		# Plot le schéma des données stockées
	make -C 2_producteurs_consommateurs plot

prod_clean: 	# Nettoie le dossier compiled
	make -C 2_producteurs_consommateurs clean

prod_all: prod_clean prod_plot

#-------------- Le problème des producteurs et consommateurs ------------------

lect_sol:		# Compile -> solutions.exe 
	make -C 3_lecteurs_ecrivains sol

lect_test:		# Run les 5 threads et stocke les données dans un csv
	make -C 3_lecteurs_ecrivains test

lect_plot:		# Plot le schéma des données stockées
	make -C 3_lecteurs_ecrivains plot

lect_clean:		# Nettoie le dossier compiled
	make -C 3_lecteurs_ecrivains clean

lect_all: lect_clean lect_plot

#-----------------------------------FIN----------------------------------------
