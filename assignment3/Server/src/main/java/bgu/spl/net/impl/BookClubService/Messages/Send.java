package bgu.spl.net.impl.BookClubService.Messages;

import bgu.spl.net.impl.BookClubService.StompFrame;

public class Send {

    private String genre;
    private String msg;
    private StompFrame frame;


    public Send(StompFrame frame) {
        this.frame = frame;
        this.genre = frame.getHeader().get("destination");
    }

    public String getGenre() {
        return genre;
    }

    public String getMsg() {
        return msg;
    }
}
