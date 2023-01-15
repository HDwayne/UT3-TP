package protagoniste;

import bataille.Bataille;

public class Homme extends EtreVivant {

	/**
	 * @param nom
	 */
	public Homme(String nom) {
		super(nom, 70);
	}
	
	/**
	 * @param nom
	 * @param forceDeVie
	 */
	public Homme(String nom, int forceDeVie) {
		super(nom, forceDeVie);
	}
	
	//TODO
	public void rejointBataille(Bataille bataille) {
		bataille.ajouter(this);
	}

	@Override
	public void mourrir() {
		bataille.eliminer(this);
	}

	@Override
	public String toString() {
		return "Homme " + super.toString();
	}

	
	
	
}
