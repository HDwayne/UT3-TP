CC  = gcc
SYS = -Wall -pedantic -DUNIX -std=gnu99
INC = -I.

# ============================= #
NOM_ETU = HERZBERG_DWAYNE
# ============================= #

SRCDIR = src
BINDIR = bin
FILESDIR = fichiers

OBJ_COMMON = config.o services_reseau.o couche_transport.o
OBJ_APP_NC = appli_non_connectee.o
OBJ_APP_C  = appli_connectee.o

OBJ_TDD0_E = proto_tdd_v0_emetteur.o
OBJ_TDD0_R = proto_tdd_v0_recepteur.o

OBJ_TDD1_E = proto_tdd_v1_emetteur.o
OBJ_TDD1_R = proto_tdd_v1_recepteur.o

OBJ_TDD2_E = proto_tdd_v2_emetteur.o
OBJ_TDD2_R = proto_tdd_v2_recepteur.o

OBJ_TDD3_E = proto_tdd_v3_emetteur.o
OBJ_TDD3_R = proto_tdd_v3_recepteur.o

OBJ_TDD4_E = proto_tdd_v4_emetteur.o
OBJ_TDD4_R = proto_tdd_v4_recepteur.o

# TDD v0
# -------
tdd0: $(OBJ_COMMON) $(OBJ_APP_NC) $(OBJ_TDD0_E) $(OBJ_TDD0_R) $(BINDIR)
	$(CC) -o $(BINDIR)/emetteur $(OBJ_COMMON) $(OBJ_APP_NC) $(OBJ_TDD0_E)
	$(CC) -o $(BINDIR)/recepteur $(OBJ_COMMON) $(OBJ_APP_NC) $(OBJ_TDD0_R)

# TDD v1
# -------
tdd1: $(OBJ_COMMON) $(OBJ_APP_NC) $(OBJ_TDD1_E) $(OBJ_TDD1_R)
	$(CC) -o $(BINDIR)/emetteur $(OBJ_COMMON) $(OBJ_APP_NC) $(OBJ_TDD1_E)
	$(CC) -o $(BINDIR)/recepteur $(OBJ_COMMON) $(OBJ_APP_NC) $(OBJ_TDD1_R)

# TDD v2
# -------
tdd2: $(OBJ_COMMON) $(OBJ_APP_NC) $(OBJ_TDD2_E) $(OBJ_TDD2_R)
	$(CC) -o $(BINDIR)/emetteur $(OBJ_COMMON) $(OBJ_APP_NC) $(OBJ_TDD2_E)
	$(CC) -o $(BINDIR)/recepteur $(OBJ_COMMON) $(OBJ_APP_NC) $(OBJ_TDD2_R)

# TDD v3
# -------
tdd3: $(OBJ_COMMON) $(OBJ_APP_C) $(OBJ_TDD3_E) $(OBJ_TDD3_R)
	$(CC) -o $(BINDIR)/emetteur $(OBJ_COMMON) $(OBJ_APP_C) $(OBJ_TDD3_E)
	$(CC) -o $(BINDIR)/recepteur $(OBJ_COMMON) $(OBJ_APP_C) $(OBJ_TDD3_R)

# TDD v4
# -------
tdd4: $(OBJ_COMMON) $(OBJ_APP_C) $(OBJ_TDD4_E) $(OBJ_TDD4_R)
	$(CC) -o $(BINDIR)/emetteur $(OBJ_COMMON) $(OBJ_APP_C) $(OBJ_TDD4_E)
	$(CC) -o $(BINDIR)/recepteur $(OBJ_COMMON) $(OBJ_APP_C) $(OBJ_TDD4_R)

# '%' matches filename
# $@  for the pattern-matched target
# $<  for the pattern-matched dependency
%.o: $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(SYS) $(INC)

$(BINDIR):
	if [ ! -d "./$(BINDIR)" ]; then mkdir $(BINDIR); fi

clean:
	rm -f *.o
	rm -f $(BINDIR)/* $(FILESDIR)/out.*

deliver:
	mkdir $(NOM_ETU)
	cp -r src $(NOM_ETU)
	cp README.txt $(NOM_ETU)
	zip -r $(NOM_ETU).zip $(NOM_ETU)
	rm -rf $(NOM_ETU)
	@echo " "
	@echo "=================================================="
	@echo "Vous devez maintenant déposer l'archive $(NOM_ETU).zip sur Moodle."
	@echo "=================================================="
