package protagoniste;

import bataille.Bataille;

public abstract class EtreVivant {
	private String nom;
	private int forceDeVie;
	protected Bataille bataille;
	
		
	/**
	 * @param nom
	 * @param forceDeVie
	 */
	public EtreVivant(String nom, int forceDeVie) {
		this.nom = nom;
		this.forceDeVie = forceDeVie;
	}

	public String getNom() {
		return nom;
	}
	
	public int getForceDeVie() {
		return forceDeVie;
	}

	@Override
	public String toString() {
		return "[nom=" + nom + ", forceDeVie=" + forceDeVie + "]";
	}

	public void rejointBataille(Bataille bataille) {
		this.bataille = bataille;
	}
	
	public abstract void mourrir();
}
