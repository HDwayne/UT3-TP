package protagoniste;

import java.util.Comparator;

public class MonstreZoneComparator implements Comparator<Monstre<?>>{
	public int compare(Monstre<?> m1, Monstre<?> m2) {
		if (m1.getZoneDeCombat().equals(m2.getZoneDeCombat())) {
			return m1.compareTo(m2);
		}
		return m1.getZoneDeCombat().compareTo(m2.getZoneDeCombat());
	}
}
