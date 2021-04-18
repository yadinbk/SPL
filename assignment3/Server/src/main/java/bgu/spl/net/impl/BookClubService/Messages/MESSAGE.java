package bgu.spl.net.impl.BookClubService.Messages;

import bgu.spl.net.impl.BookClubService.Frame;
import bgu.spl.net.impl.BookClubService.StompFrame;

import java.util.HashMap;
import java.util.Map;

public class MESSAGE implements Frame {
    private StompFrame frame;
    private String subId;
    private int msgId;
    private String genre;

    public MESSAGE(StompFrame frame , String subId , int msgId) {
        this.frame = frame;
        this.genre = frame.getHeader().get("destination");
        this.subId = subId;
        this.msgId = msgId;

    }

    @Override
    public int getOperationCode() {
        return -3;
    }


    @Override
    public StompFrame getBuiltFrame() {
        StompFrame sendFrame = new StompFrame();
        sendFrame.setStompCommand("MESSAGE");
        Map<String , String> headers = new HashMap<>();
        headers.put("subscription" , subId+"");
        headers.put("Message-id" , msgId+"");
        headers.put("destination" , genre);
        sendFrame.setHeader(headers);
        sendFrame.setFrameBody(frame.getFrameBody());

        return sendFrame;
    }
}
