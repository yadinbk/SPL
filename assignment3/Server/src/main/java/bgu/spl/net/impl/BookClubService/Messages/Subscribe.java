package bgu.spl.net.impl.BookClubService.Messages;

import bgu.spl.net.impl.BookClubService.StompFrame;

public class Subscribe {
    private String subId;
    private String genre;
    private String receipt;
    private StompFrame frame;

    public Subscribe(StompFrame frame) {
        this.frame = frame;
        this.subId = frame.getHeader().get("id");
        this.genre = frame.getHeader().get("destination");
        this.receipt = frame.getHeader().get("receipt");
    }

    public String getSubId() {
        return subId;
    }

    public String getGenre() {
        return genre;
    }

    public String getReceipt() {
        return receipt;
    }
}
