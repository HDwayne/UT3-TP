package livre;

import java.util.LinkedList;
import java.util.List;
import bataille.Bataille;
import protagoniste.Heros;
import protagoniste.Homme;

public class AideEcrivain {
	private Bataille bataille;
	List<Homme> listeTriee = new LinkedList<>();

	/**
	 * @param bataille
	 */
	public AideEcrivain(Bataille bataille) {
		this.bataille = bataille;
	}
	
	public String visualiserForcesHumaines() {
		int i=0;
		for (Homme homme : bataille.getCampHumains()) {
			if (!(homme instanceof Heros)) {
				listeTriee.add(homme);
			} else {
				listeTriee.add(i, homme);
				i++;
			}
		}
			
//		for (ListIterator<Homme> iterator = bataille.getCampHumains().iterator(); iterator.hasNext();) {
//		 	Homme homme = iterator.next();
//		 	//TODO	
//		}
		return listeTriee.toString();
	}
}
