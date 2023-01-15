package protagoniste;
import java.util.Arrays;
import java.util.Iterator;
import java.util.Random;

import attaque.Pouvoir;
import bataille.Bataille;

public class Monstre<P extends Pouvoir> extends EtreVivant{
	private P[] attaques;
	private ZoneDeCombat zoneDeCombat;
	private Domaine domaine;
	private GestionAttaque gestionAttaque;
	
	/**
	 * @param nom
	 * @param forceDeVie
	 * @param zoneDeCombat
	 */
	@SafeVarargs
	public Monstre(String nom, int forceDeVie, ZoneDeCombat zoneDeCombat, Domaine domaine, P... attaques) {
		super(nom, forceDeVie);
		this.zoneDeCombat = zoneDeCombat;
		this.domaine = domaine;
		this.attaques = attaques;
	}
	
	public ZoneDeCombat getZoneDeCombat() {
		return zoneDeCombat;
	}
	
	public Domaine getDomaine() {
		return domaine;
	}

	
	
	@Override
	public String toString() {
		return "Monstre [getNom()=" + this.getNom() + ", attaques=" + Arrays.toString(attaques) + ", zoneDeCombat=" + zoneDeCombat + ", getForceDeVie()=" + this.getForceDeVie() + "]";
	}

	public void entreEnCombat() {
		for (int i = 0; i < attaques.length; i++) {
			attaques[i].regenererPouvoir();
		}
		gestionAttaque = new GestionAttaque();
	}
	
	public void rejointBataille(Bataille bataille) {
		bataille.ajouter(this);
	}
	
	@Override
	public void mourrir() {
		bataille.eliminer(this);
	}
	
	public P attaque() {
		if (gestionAttaque.hasNext()) {
			return gestionAttaque.next();
		}
		return null;
	}
	
	private class GestionAttaque implements Iterator<P>{
		private P[] attaquesPossibles = attaques;
		private int nbAttaquePossible = attaques.length;
		
		
		public GestionAttaque() {
		}

		@Override
		public boolean hasNext() {
			for (int i = 0; i < nbAttaquePossible; i++) {
				if (!attaques[i].isOperationnel()) {
					attaques[i] = attaques[nbAttaquePossible-1];
					nbAttaquePossible--;
				}
			}
			return nbAttaquePossible != 0;
		}

		@Override
		public P next() {
			Random random = new Random();
			return attaques[random.nextInt(nbAttaquePossible)];
		}
	}
}
