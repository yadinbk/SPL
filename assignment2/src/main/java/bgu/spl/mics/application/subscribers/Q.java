package bgu.spl.mics.application.subscribers;

import bgu.spl.mics.Callback;
import bgu.spl.mics.Subscriber;
import bgu.spl.mics.application.messages.GadgetAvailableEvent;
import bgu.spl.mics.application.messages.TickBroadcast;
import bgu.spl.mics.application.passiveObjects.Inventory;

/**
 * Q is the only Subscriber\Publisher that has access to the {@link bgu.spl.mics.application.passiveObjects.Inventory}.
 *
 * You can add private fields and public methods to this class.
 * You MAY change constructor signatures and even add new public constructors.
 */
public class Q extends Subscriber {

	private Inventory inventory;
	private String gadget;
	private int time;

	public Q() {
		super("Q");
		time = 0;
		inventory = Inventory.getInstance();
		this.gadget = gadget;
	}

	@Override
	protected void initialize() {

		Callback<GadgetAvailableEvent> gadgetCallback = new Callback<GadgetAvailableEvent>(){
			@Override
			public void call(GadgetAvailableEvent e) {
				gadget = e.getGadget();
				boolean gotGadget = inventory.getItem(gadget);
				complete(e ,gotGadget);
				e.setQTime(time);
			}

		};
		Callback<TickBroadcast> ticCallback = new Callback<TickBroadcast>(){
			@Override
			public void call(TickBroadcast e) {
				if(e.isTimeout())
					terminate();
				else
					time = e.getCurrTime();
			}
		};

		subscribeEvent(GadgetAvailableEvent.class, gadgetCallback);
		subscribeBroadcast(TickBroadcast.class , ticCallback);

	}

}
