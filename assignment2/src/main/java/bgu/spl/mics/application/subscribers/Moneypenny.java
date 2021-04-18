package bgu.spl.mics.application.subscribers;

import bgu.spl.mics.Callback;
import bgu.spl.mics.Subscriber;
import bgu.spl.mics.application.messages.AgentsAvailableEvent;
import bgu.spl.mics.application.messages.TickBroadcast;
import bgu.spl.mics.application.passiveObjects.Squad;

import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

/**
 * Only this type of Subscriber can access the squad.
 * Three are several Moneypenny-instances - each of them holds a unique serial number that will later be printed on the report.
 *
 * You can add private fields and public methods to this class.
 * You MAY change constructor signatures and even add new public constructors.
 */
public class Moneypenny extends Subscriber {

	private Squad squad;
	private List<String> serials;
	private int ID;
	private int time;

	public Moneypenny(int id) {
		super("Moneypenny");
		squad = Squad.getInstance();
		serials = new CopyOnWriteArrayList<>();
		ID = id;
		this.time = 0;
	}

	@Override
	protected void initialize() {

		Callback<AgentsAvailableEvent> agentCallback = new Callback<AgentsAvailableEvent>(){
			@Override
			public void call(AgentsAvailableEvent e) {
				serials = e.getAgentSerials();
				e.setID(ID);
				e.setAgentNames(squad.getAgentsNames(serials));


				boolean agentsAvailable = squad.getAgents(e.getAgentSerials());

				if (agentsAvailable){
					complete(e, true);
					if(e.isActiveMission())
						squad.sendAgents(serials , e.getDuration());
					else
						squad.releaseAgents(serials);
				}
				else {
					complete(e, false);
				}
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

		subscribeBroadcast(TickBroadcast.class , ticCallback);
		subscribeEvent(AgentsAvailableEvent.class, agentCallback);
	}

}

////צריך שהאיוונט שין עד שאיזרליסד יהיה אמת - איסקה