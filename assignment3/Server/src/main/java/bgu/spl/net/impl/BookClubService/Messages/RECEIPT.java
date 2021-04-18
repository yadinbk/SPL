package bgu.spl.net.impl.BookClubService.Messages;

import bgu.spl.net.impl.BookClubService.Frame;
import bgu.spl.net.impl.BookClubService.StompFrame;

import java.util.HashMap;
import java.util.Map;

public class RECEIPT implements Frame {

    private String receipt;

    public RECEIPT(String receipt) {
        this.receipt = receipt;
    }

    @Override
    public int getOperationCode() {
        return -2;
    }

    @Override
    public StompFrame getBuiltFrame() {
        StompFrame sendFrame = new StompFrame();
        sendFrame.setStompCommand("RECEIPT");
        Map<String , String> headers = new HashMap<>();
        headers.put("receipt-id" , receipt+"");
        sendFrame.setHeader(headers);
        sendFrame.setFrameBody("");

        return sendFrame;
    }
}
