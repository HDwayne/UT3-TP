package livre;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.NavigableSet;
import java.util.TreeSet;

import attaque.Feu;
import attaque.Glace;
import attaque.Lave;
import attaque.Pouvoir;
import attaque.Tranchant;
import bataille.Bataille;
import protagoniste.Domaine;
import protagoniste.Heros;
import protagoniste.Homme;
import protagoniste.Monstre;
import protagoniste.MonstreDomaineComparator;
import protagoniste.MonstreZoneComparator;
import protagoniste.ZoneDeCombat;

public class AideEcrivain {
	private Bataille bataille;
	List<Homme> listeTriee = new LinkedList<>();
	NavigableSet<Monstre<?>> monstreDomaineSet = new TreeSet<>(new MonstreDomaineComparator());
	NavigableSet<Monstre<?>> monstreZoneSet = new TreeSet<>(new MonstreZoneComparator());
	NavigableSet<Monstre<?>> monstresDeFeu;
	NavigableSet<Monstre<?>> monstreDeGlace;
	NavigableSet<Monstre<?>> monstreTranchant;
	
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
		return listeTriee.toString();
	}
	
	public String ordreNaturelMonstre() {
		TreeSet<Monstre<?>> set = new TreeSet<>();
		String text = "";
		
		for (Iterator<Monstre<?>> iterator = bataille.getCampMonstres().iterator(); iterator.hasNext();) {
			Monstre<?> monstre = iterator.next();
			set.add(monstre);
		}
		
		for (Monstre<?> monstre : set) {
			text += monstre.getNom() + ", ";
		}
		return text;
	}
	
	public void updateMonstresDomaine() {
		for (Iterator<Monstre<? extends Pouvoir>> iterator = bataille.getCampMonstres().iterator(); iterator.hasNext();) {
			Monstre<? extends Pouvoir> monstre = iterator.next();
			monstreDomaineSet.add(monstre);
		}
	}
	
	public void updateMonstresZone() {
		for (Iterator<Monstre<?>> iterator = bataille.getCampMonstres().iterator(); iterator.hasNext();) {
			Monstre<?> monstre = iterator.next();
			monstreZoneSet.add(monstre);
		}
	}
	
	public String ordreMonstreDomaine() {
		List<String> list = new ArrayList<>();
		list.add("FEU :");
		list.add("GLACE :");
		list.add("TRANCHANT:");
		
		updateMonstresDomaine();
		
		int i = 0;
		String string = list.get(i) + "\n";
		Monstre<? extends Pouvoir> previous = null;
		
		for (Monstre<? extends Pouvoir> monstre : monstreDomaineSet) {
			if (previous == null || previous.getDomaine().equals(monstre.getDomaine())) {
				string += monstre.getNom() + ", ";
			} else {
				i++;
				string += "\n" + list.get(i) + "\n" + monstre.getNom() + ", ";
			}
			previous = monstre;			
		}
		return string;
	}
	
	public String ordreMonstreZone() {
		List<String> list = new ArrayList<>();
		list.add("AERIEN :");
		list.add("AQUATIQUE :");
		list.add("TERRESTRE :");
		
		updateMonstresZone();
		
		int i = 0;
		String string = list.get(i) + "\n";
		Monstre<?> previous = null;
		
		for (Monstre<?> monstre : monstreZoneSet) {
			if (previous == null || previous.getZoneDeCombat().equals(monstre.getZoneDeCombat())) {
				string += monstre.getNom() + " : " + monstre.getForceDeVie() + ", ";
			} else {
				i++;
				string += "\n" + list.get(i) + "\n" + monstre.getNom() + " : " + monstre.getForceDeVie() + ", ";
			}
			previous = monstre;			
		}
		return string;
	}
	
//	public Monstre<?> firstMonstreDomaine(Domaine domaine){
//		for (Monstre<?> monstre : monstreDomaineSet) {
//			if (monstre.getDomaine().equals(domaine)) {
//				return monstre;
//			}
//		}
//		return null;
//	}
//	
//	public void initMonstresDeFeu() {
//		Monstre<?> firstDiffFeu = firstMonstreDomaine(Domaine.GLACE);
//		monstresDeFeu = monstreDomaineSet.headSet(firstDiffFeu, false);
//	}
	
	public void initMonstresDeFeu() {
		monstresDeFeu = monstreDomaineSet.headSet(new Monstre<>("aaaaaaaaaa", 1, ZoneDeCombat.AQUATIQUE, Domaine.GLACE, new Lave(5)), false);
	}
	
	public void initMonstresDeGlace() {
		monstreDeGlace = monstreDomaineSet.subSet(
			new Monstre<>("zzzzzzzzzz", 1, ZoneDeCombat.AQUATIQUE, Domaine.FEU, new Lave(5)), 
			false,
			new Monstre<>("aaaaaaaaaa", 1, ZoneDeCombat.TERRESTRE, Domaine.TRANCHANT, new Lave(5)),
			false
		);
	}
	
	public void initMonstresTranchant() {
		monstreTranchant = monstreDomaineSet.tailSet(new Monstre<>("zzzzzzzzzz", 1, ZoneDeCombat.AQUATIQUE, Domaine.GLACE, new Lave(5)), false);
	}
	
	
	public NavigableSet<Monstre<?>> getMonstresDeFeu() {
		updateMonstresDomaine();
		return monstresDeFeu;
	}	
	
	public NavigableSet<Monstre<?>> getMonstresDeGlace() {
		updateMonstresDomaine();
		return monstreDeGlace;
	}	
	
	public NavigableSet<Monstre<?>> getMonstresTranchants() {
		updateMonstresDomaine();
		return monstreTranchant;
	}	
}
