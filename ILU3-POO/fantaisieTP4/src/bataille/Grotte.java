package bataille;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Random;

import protagoniste.Monstre;
import protagoniste.ZoneDeCombat;

public class Grotte {
	private LinkedHashMap<Salle, List<Salle>> planGrotte = new LinkedHashMap<>();
	private HashMap<Salle, Bataille> batailles = new HashMap<>();
	private HashSet<Salle> sallesExplorees = new HashSet<>();
	private int numeroSalleDecisive;
	
	public void ajouterSalle(ZoneDeCombat zone, Monstre<?>... monstres) {
		Salle salle = new Salle(planGrotte.size()+1, zone);
		Bataille bataille = new Bataille();
		
		for (Monstre<?> monstre : monstres) {
			bataille.ajouter(monstre);
		}
		
		planGrotte.put(salle, new ArrayList<Salle>());
		batailles.put(salle, bataille);
	}

	public String afficherPlanGrotte() {
	  StringBuilder affichage = new StringBuilder();
	  for (Map.Entry<Salle, List<Salle>> entry : planGrotte.entrySet()) {
	   Salle salle = entry.getKey();
	   List<Salle> acces = planGrotte.get(salle);
	   affichage.append("La " + salle + ".\nelle possede " + acces.size() + " acces : ");
	   for (Salle access : acces) {
	    affichage.append(" vers la salle " + access);
	   }
	   Bataille bataille = batailles.get(salle);
	   Camp<Monstre<?>> camp = bataille.getCampMonstres();
	   Monstre<?> monstre = camp.selectionner();
	   if (camp.nbCombattants() > 1) {
	    affichage.append("\n" + camp.nbCombattants() + " monstres de type ");
	   } else {
	    affichage.append("\nUn monstre de type ");
	   }
	   affichage.append(monstre.getNom() + " la protege.\n");
	   if (salle.getNumeroSalle() == numeroSalleDecisive) {
	    affichage.append("C'est dans cette salle que se trouve la pierre de sang.\n");
	   }
	   affichage.append("\n");
	  }
	  return affichage.toString();
	}
	
	private Salle trouverSalle(int numeroSalle) {
		for (Map.Entry<Salle, List<Salle>> i : planGrotte.entrySet()) {
	       if (i.getKey().getNumeroSalle() == numeroSalle) {
			return i.getKey();
	       }
		}
		return null;
	}
	
	public void configurerAcces(int NumSalleOrigine, int... NumSallesAccessibles) {
		Salle salle = trouverSalle(NumSalleOrigine);
		
		List<Salle> salleliees = planGrotte.get(salle);
		for (int num : NumSallesAccessibles) {
			salleliees.add(trouverSalle(num));
		}
	}

	/**
	 * @param numeroSalleDecisive the numeroSalleDecisive to set
	 */
	public void setNumeroSalleDecisive(int numeroSalleDecisive) {
		this.numeroSalleDecisive = numeroSalleDecisive;
	}
	
	public boolean salleDecisive(Salle salle) {
		return salle.getNumeroSalle() == numeroSalleDecisive;
	}
	
	public Salle premiereSalle() {
		Salle salle = trouverSalle(1);
		sallesExplorees.add(salle);
		return salle;
	}
	
	public Salle salleSuivante(Salle salle) {
		List<Salle> sallesAccessibles = new ArrayList<>();

		for (Salle salle2 : planGrotte.get(salle)) {
			sallesAccessibles.add(salle2);
		}
		
		sallesAccessibles.removeAll(sallesExplorees);
		
		if (sallesAccessibles.isEmpty()) {
			System.out.println("ouiiii");
			sallesAccessibles = planGrotte.get(salle);
		}
		
		Random r = new Random();
		Salle s = sallesAccessibles.get(r.nextInt(sallesAccessibles.size()));
		sallesExplorees.add(s);
		return s;
	}
}
