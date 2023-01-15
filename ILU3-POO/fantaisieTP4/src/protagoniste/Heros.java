package protagoniste;

public class Heros extends Homme {

	/**
	 * @param nom
	 */
	public Heros(String nom) {
		super(nom, 100);
	}

	@Override
	public String toString() {
		return "Heros [nom=" + this.getNom() + ", forceDeVie=" + this.getForceDeVie() + "]";
	}	
}
