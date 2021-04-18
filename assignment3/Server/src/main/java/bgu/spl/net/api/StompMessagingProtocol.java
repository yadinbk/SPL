package bgu.spl.net.api;

import bgu.spl.net.impl.BookClubService.Frame;
import bgu.spl.net.srv.Connections;

public interface StompMessagingProtocol  {
	/**
	 * Used to initiate the current client protocol with it's personal connection ID and the connections implementation
	**/
    void start(int connectionId, Connections<Frame> connections);
    
    void process(String message);
	
	/**
     * @return true if the connection should be terminated
     */
    boolean shouldTerminate();
}
