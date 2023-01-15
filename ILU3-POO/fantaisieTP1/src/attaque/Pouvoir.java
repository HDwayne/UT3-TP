package attaque;

public class Pouvoir extends ForceDeCombat {
	private int nbUtilisationPouvoir;
	private int nbUtilisationPouvoirInitial;
	
	/**
	 * @param pointDeDegat
	 * @param nom
	 * @param nbUtilisationPouvoir
	 */
	public Pouvoir(int pointDeDegat, String nom, int nbUtilisationPouvoir) {
		super(pointDeDegat, nom);
		this.nbUtilisationPouvoir = nbUtilisationPouvoir;
		this.nbUtilisationPouvoirInitial = nbUtilisationPouvoir;
	}
	
	public void regenererPouvoir() {
		this.nbUtilisationPouvoir = nbUtilisationPouvoirInitial;
	}
	
	public int utiliser() {
		if (isOperationnel()) {
			nbUtilisationPouvoir--;
			if (nbUtilisationPouvoir == 0)
				operationnel = false;
			return getPointDeDegat();
		}
		return 0;
	}
}
