package protagoniste;

import java.util.List;

import bataille.Bataille;

public abstract class EtreVivant implements Comparable<EtreVivant> {
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
	
	public int compareTo(EtreVivant EtreToCompare) {
		return nom.compareTo(EtreToCompare.getNom());
	}
	
	public boolean equals(Object obj) {
		if (obj instanceof EtreVivant) {
			EtreVivant etreVivant = (EtreVivant) obj;
			return nom.equals(etreVivant.getNom());
		}
		return false;
	}
}
