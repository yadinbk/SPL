package bgu.spl.net.impl.BookClubService.Messages;

import bgu.spl.net.impl.BookClubService.StompFrame;

public class Unsubscribe {

    private StompFrame frame;
    private String subId ;

    public Unsubscribe(StompFrame frame) {
        this.frame = frame;
        this.subId = frame.getHeader().get("id");
    }

    public String getSubId() {
        return subId;
    }

}
