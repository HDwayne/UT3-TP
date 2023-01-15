package bataille;

import java.util.LinkedList;
import java.util.List;
import java.util.ListIterator;

import protagoniste.EtreVivant;

public class Camp<T extends EtreVivant> implements Iterable<T> {
	List<T> liste = new LinkedList<>();
	// ListIterator<T> iterateur = liste.listIterator();

	void ajouter(T etreVivant) {
		if (!liste.contains(etreVivant)) {
			liste.add(etreVivant);
		}
	}

	void eliminer(T etreVivant) {
		liste.remove(etreVivant);
	}
	
	public String toString() {
		return liste.toString();
	}
	
	public ListIterator<T> iterator() {
		return liste.listIterator();
	}
}
