package attaque;

public abstract class Feu extends Pouvoir{

	/**
	 * @param pointDeDegat
	 * @param nom
	 * @param nbUtilisationPouvoir
	 */
	public Feu(int pointDeDegat, String nom, int nbUtilisationPouvoir) {
		super(pointDeDegat, nom, nbUtilisationPouvoir);
	}
}
