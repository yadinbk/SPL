package bgu.spl.mics.application.passiveObjects;

import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 *  That's where Q holds his gadget (e.g. an explosive pen was used in GoldenEye, a geiger counter in Dr. No, etc).
 * <p>
 * This class must be implemented safely as a thread-safe singleton.
 * You must not alter any of the given public methods of this class.
 * <p>
 * You can add ONLY private fields and methods to this class as you see fit.
 */
public class Inventory {
	private List<String> gadgets;
	private static class InventoryHolder {
		private static Inventory instance = new Inventory();
	}

	/**
	 * Constructors.
	 */
	private Inventory(){
		gadgets = new ArrayList<>();
	}

	public Inventory(String[] gadgets){
		List<String> gadgetsList = Arrays.asList(gadgets);
		this.gadgets = gadgetsList;
	}

	/**
	 * Retrieves the single instance of this class.
	 */
	public static Inventory getInstance() {
		return InventoryHolder.instance;
	}

	/**
	 * Initializes the inventory. This method adds all the items given to the gadget
	 * inventory.
	 * <p>
	 * @param inventory 	Data structure containing all data necessary for initialization
	 * 						of the inventory.
	 */
	public void load (String[] inventory) {
		if (inventory != null) {
			for (String s : inventory) {
				gadgets.add(s);
			}
		}
	}

	/**
	 * acquires a gadget and returns 'true' if it exists.
	 * <p>
	 * @param gadget 		Name of the gadget to check if available
	 * @return 	â€˜falseâ€™ if the gadget is missing, and â€˜trueâ€™ otherwise
	 */
	public boolean getItem(String gadget){
		boolean b = gadgets.contains(gadget);
		if (b) gadgets.remove(gadget);
		return b;
	}

	/**
	 *
	 * <p>
	 * Prints to a file name @filename a serialized object List<Gadget> which is a
	 * List of all the reports in the diary.
	 * This method is called by the main method in order to generate the output.
	 */
	public void printToFile(String filename){
		try (FileWriter fileWriter = new FileWriter(filename)) {
			String s = "";
			for(String gadget : gadgets){
				s += "\"" + gadget + "\",";
			}
			s ="["+s.substring(0, s.length()-1)+"]";
			fileWriter.write(s);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}






}
