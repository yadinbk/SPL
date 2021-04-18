package bgu.spl.mics.application.publishers;
import bgu.spl.mics.Publisher;
import bgu.spl.mics.application.messages.TickBroadcast;

import java.util.Timer;
import java.util.TimerTask;

/**
 * TimeService is the global system timer There is only one instance of this Publisher.
 * It keeps track of the amount of ticks passed since initialization and notifies
 * all other subscribers about the current time tick using {@link Tick Broadcast}.
 * This class may not hold references for objects which it is not responsible for.
 * 
 * You can add private fields and public methods to this class.
 * You MAY change constructor signatures and even add new public constructors.
 */
public class TimeService extends Publisher {

	int duration;
	int currTime;

	public TimeService( int duration) {
		super("TimeService");
		this.duration = duration;
		this.currTime = 0;
	}

	@Override
	protected void initialize() {
		run();

	}

	@Override
	public void run() {

		Timer timer = new Timer();
		TimerTask timerTask = new TimerTask() {
			@Override
			public void run() {

				if (currTime < duration){
					currTime++;
					TickBroadcast tb = new TickBroadcast(currTime);
					getSimplePublisher().sendBroadcast(tb);
				}
				else {
					TickBroadcast tickBroadcast = new TickBroadcast(currTime);
					tickBroadcast.setTimeOut(true);
					getSimplePublisher().sendBroadcast(tickBroadcast);
					timer.cancel();
					timer.purge();
					//Thread.currentThread().sleep();

				}
			}
		};
		timer.schedule(timerTask , 0, 100 );
	}

	public int getCurrTime() {
		return currTime;
	}
}
