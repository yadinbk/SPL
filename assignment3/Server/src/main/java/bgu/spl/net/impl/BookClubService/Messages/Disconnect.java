package bgu.spl.net.impl.BookClubService.Messages;

import bgu.spl.net.impl.BookClubService.StompFrame;

public class Disconnect {

    private String receiptId;

    public Disconnect(StompFrame frame) {
        this.receiptId = frame.getHeader().get("receipt");
    }

    public String getReceiptId() {
        return receiptId;
    }
}
