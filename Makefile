project:
	$(MAKE) -C 1_philosophes all
	$(MAKE) -C 2_producteurs_consommateurs all
	$(MAKE) -C 3_lecteurs_ecrivains all

clean:
	$(MAKE) -C 1_philosophes clean
	$(MAKE) -C 2_producteurs_consommateurs clean
	$(MAKE) -C 3_lecteurs_ecrivains clean