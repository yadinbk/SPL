package bgu.spl.mics;

import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.LinkedBlockingQueue;

/**
 * The {@link MessageBrokerImpl class is the implementation of the MessageBroker interface.
 * Write your implementation here!
 * Only private fields and methods can be added to this class.
 */
public class MessageBrokerImpl implements MessageBroker {

	//register
	private Map<Subscriber , LinkedBlockingQueue<Message>> subBlockingQueueMap;
	//subscribeEvent
	private Map<Class<? extends Event>, ConcurrentLinkedQueue<Subscriber>> subEventListMap;
	//subscribeBroadcast
	private Map<Class<? extends Broadcast>, ConcurrentLinkedQueue<Subscriber>> subBroadcastListMap;
	//complete
	private Map<Event, Future> eventFutureMap;

	private static class MessageBrokerImplHolder{
		private static MessageBrokerImpl instance = new MessageBrokerImpl();
	}

	private MessageBrokerImpl(){
		subBlockingQueueMap = new HashMap<>();
		subEventListMap = new HashMap<>();
		subBroadcastListMap = new HashMap<>();
		eventFutureMap = new HashMap<>();
	}

	/**
	 * Retrieves the single instance of this class.
	 */

	public static MessageBroker getInstance() {
		return MessageBrokerImplHolder.instance;
	}

		@Override
	public <T> void subscribeEvent(Class<? extends Event<T>> type, Subscriber m) {
		if (subEventListMap.containsKey(type) && true){
			subEventListMap.get(type).add(m);
		}
		else {
			ConcurrentLinkedQueue<Subscriber> toAdd1 = new ConcurrentLinkedQueue<>();
			toAdd1.add(m);
			subEventListMap.put(type, toAdd1);
		}
	}

	@Override
	public synchronized void subscribeBroadcast(Class<? extends Broadcast> type, Subscriber m) {
		if (subBroadcastListMap.containsKey(type)){
			subBroadcastListMap.get(type).add(m);
		}
		else {
			ConcurrentLinkedQueue<Subscriber> toAdd = new ConcurrentLinkedQueue<>();
			toAdd.add(m);
			subBroadcastListMap.put(type, toAdd);

		}
	}

	@Override
	public synchronized  <T> void complete(Event<T> e, T result) {
		eventFutureMap.get(e).resolve(result);
	}

	@Override
	public synchronized  void sendBroadcast(Broadcast b) {
		if(subBroadcastListMap.get(b.getClass()) != null) {
			ConcurrentLinkedQueue<Subscriber> l = subBroadcastListMap.get(b.getClass());
			for (Subscriber s : l) {
				subBlockingQueueMap.get(s).add(b);
			}
		}
	}

	@Override
	public synchronized  <T> Future<T> sendEvent(Event<T> e) {
			ConcurrentLinkedQueue<Subscriber> q = subEventListMap.get(e.getClass());
			if(!q.isEmpty()) {
		     	Subscriber subscriber = q.poll();
				subBlockingQueueMap.get(subscriber).add(e);
				q.add(subscriber);
				///maybe not a good implement
				Future future = new Future();
				eventFutureMap.put(e, future);
				return future;
			}else return null;

	}

	@Override
	public synchronized void register(Subscriber m) {
		LinkedBlockingQueue<Message> temp = new LinkedBlockingQueue<Message>();
		subBlockingQueueMap.put(m, temp);
	}

	@Override
	public synchronized void unregister(Subscriber m) {
		for (Class<? extends Event> e : subEventListMap.keySet()){
			if (subEventListMap.get(e).contains(m)){
				subEventListMap.get(e).remove(m);
			}

		}
		for (Class<? extends Broadcast> e : subBroadcastListMap.keySet()){
			if (subBroadcastListMap.get(e).contains(m)){
				subBroadcastListMap.get(e).remove(m);
			}

		}

		for(int i = 0 ; i < subBroadcastListMap.size() ; i++) {
			try {
				if(!subBlockingQueueMap.get(m).isEmpty()) {
					Message mes = subBlockingQueueMap.get(m).take();
					eventFutureMap.get(mes).resolve(false);
				}
			} catch (InterruptedException e) {
				e.printStackTrace();
			}

		}
		subBlockingQueueMap.get(m).clear();



	}

	@Override
	public Message awaitMessage(Subscriber m) throws InterruptedException {
		Message message = subBlockingQueueMap.get(m).take();
		return message;
	}



}
