package attaque;

public class Arc extends Arme{
	private int nbFlechesRestantes;

	/**
	 * @param pointDeDegat
	 * @param nom
	 */
	public Arc(int nbFlechesRestantes) {
		super(50, "Arc");
		this.nbFlechesRestantes = nbFlechesRestantes;
	}
	
	public int utiliser() {
		if (isOperationnel()) {
			nbFlechesRestantes--;
			if (nbFlechesRestantes == 0)
				operationnel = false;
			return getPointDeDegat();
		}
		return 0;
	}
}
