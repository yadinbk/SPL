package bgu.spl.mics.application.subscribers;

import bgu.spl.mics.Callback;
import bgu.spl.mics.Subscriber;
import bgu.spl.mics.application.messages.MissionReceivedEvent;
import bgu.spl.mics.application.messages.TickBroadcast;
import bgu.spl.mics.application.passiveObjects.MissionInfo;

import java.util.ArrayList;
import java.util.List;

/**
 * A Publisher\Subscriber.
 * Holds a list of Info objects and sends them
 *
 * You can add private fields and public methods to this class.
 * You MAY change constructor signatures and even add new public constructors.
 */
public class Intelligence extends Subscriber {

	private List<MissionInfo> missionInfosArr;
	private  int ID;
	private int time;

	public Intelligence(ArrayList<MissionInfo> missionInfosArr, int ID) {
		super("Intelligence");
		this.missionInfosArr = missionInfosArr;
		this.ID = ID;
		time = 0;
	}

	@Override
	protected void initialize() {

		Callback<TickBroadcast> ticCallback = new Callback<TickBroadcast>(){
			@Override
			public void call(TickBroadcast e) {
				if(e.isTimeout())
					terminate();
				else {
					time = e.getCurrTime();
					for (MissionInfo mission : missionInfosArr) {
						if (time == mission.getTimeIssued()) {
							MissionReceivedEvent missionReceivedEvent = new MissionReceivedEvent(mission.getMissionName());
							missionReceivedEvent.setAgentsSerial(mission.getSerialAgentsNumbers());
							missionReceivedEvent.setGadget(mission.getGadget());
							missionReceivedEvent.setTimeIssued(mission.getTimeIssued());
							missionReceivedEvent.setTimeExpired(mission.getTimeExpired());
							missionReceivedEvent.setDuration(mission.getDuration());
							getSimplePublisher().sendEvent(missionReceivedEvent);


						}
					}
				}
			}
		};

		subscribeBroadcast(TickBroadcast.class , ticCallback);
	}
}
