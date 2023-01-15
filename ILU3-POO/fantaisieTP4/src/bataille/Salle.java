package bataille;

import protagoniste.ZoneDeCombat;

public class Salle {
	private int numeroSalle;
	private ZoneDeCombat zoneDeCombat;
	
	/**
	 * @param numSalle
	 * @param zoneDeCombat
	 */
	public Salle(int numeroSalle, ZoneDeCombat zoneDeCombat) {
		this.numeroSalle = numeroSalle;
		this.zoneDeCombat = zoneDeCombat;
	}

	/**
	 * @return the numSalle
	 */
	public int getNumeroSalle() {
		return numeroSalle;
	}

	/**
	 * @return the zoneDeCombat
	 */
	public ZoneDeCombat getZoneDeCombat() {
		return zoneDeCombat;
	}

	@Override
	public String toString() {
		return "Salle n°" + numeroSalle + " de type combat " + zoneDeCombat;
	}
}
