package bgu.spl.mics.application.subscribers;

import bgu.spl.mics.Callback;
import bgu.spl.mics.Future;
import bgu.spl.mics.Subscriber;
import bgu.spl.mics.application.messages.AgentsAvailableEvent;
import bgu.spl.mics.application.messages.GadgetAvailableEvent;
import bgu.spl.mics.application.messages.MissionReceivedEvent;
import bgu.spl.mics.application.messages.TickBroadcast;
import bgu.spl.mics.application.passiveObjects.Diary;
import bgu.spl.mics.application.passiveObjects.Report;

/**
 * M handles ReadyEvent - fills a report and sends agents to mission.
 *
 * You can add private fields and public methods to this class.
 * You MAY change constructor signatures and even add new public constructors.
 */
public class M extends Subscriber {

	private int time;
	private Diary diary;
	private int ID;


	public M(int id) {
		super("M");
		time = 0;
		diary = Diary.getInstance();
		ID = id;
	}

	@Override
	protected void initialize() {

		Callback<MissionReceivedEvent> missionReceivedEventCallback = new Callback<MissionReceivedEvent>(){
			@Override
			public void call(MissionReceivedEvent e) {
				diary.increment();
				boolean missionCompleted = false;
				AgentsAvailableEvent agentsAvailableEvent = new AgentsAvailableEvent(e.getAgentsSerial(), e.getDuration());
				Future agentFuture = getSimplePublisher().sendEvent(agentsAvailableEvent);
				if(agentFuture != null && agentFuture.get().equals(true)) {

					GadgetAvailableEvent gadgetAvailableEvent = new GadgetAvailableEvent(e.getGadget());
					Future gadgetFuture = getSimplePublisher().sendEvent(gadgetAvailableEvent);

					if(gadgetFuture != null && gadgetFuture.get().equals(true)) {
						Report report = new Report(e.getMissionName(), ID, agentsAvailableEvent.getID(), e.getAgentsSerial(), agentsAvailableEvent.getAgentNames(), e.getGadget(), e.getTimeIssued(), gadgetAvailableEvent.getQTime(), time);
						if ((e.getTimeExpired() >= gadgetAvailableEvent.getQTime())) {
							diary.addReport(report);
							missionCompleted = true;
							agentsAvailableEvent.setActiveMission(true);
							complete(e, true);
						}
					}
				}
				if(!missionCompleted){
					complete(e , false);
					agentsAvailableEvent.setActiveMission(false);
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

		subscribeEvent(MissionReceivedEvent.class, missionReceivedEventCallback);
		subscribeBroadcast(TickBroadcast.class , ticCallback);
	}

}
