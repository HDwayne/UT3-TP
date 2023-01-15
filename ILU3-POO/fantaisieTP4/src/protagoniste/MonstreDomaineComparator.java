package protagoniste;

import java.util.Comparator;

import attaque.Pouvoir;

public class MonstreDomaineComparator implements Comparator<Monstre<?>> {
	public int compare(Monstre<?> m1, Monstre<?> m2) {
		if (m1.getDomaine().equals(m2.getDomaine())) {
			return m1.compareTo(m2);
		}
		return m1.getDomaine().compareTo(m2.getDomaine());
	}
}