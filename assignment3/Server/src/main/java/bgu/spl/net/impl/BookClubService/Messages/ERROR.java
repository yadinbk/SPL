package bgu.spl.net.impl.BookClubService.Messages;

import bgu.spl.net.impl.BookClubService.Frame;
import bgu.spl.net.impl.BookClubService.StompFrame;

import java.util.HashMap;
import java.util.Map;

public class ERROR implements Frame {

    private String errorMsg;

    public ERROR(String errorMsg) { // TODO ~!
        this.errorMsg = errorMsg;
    }

    @Override
    public int getOperationCode() {
        return -1;
    }

    @Override
    public StompFrame getBuiltFrame() {
        StompFrame sendFrame = new StompFrame();
        sendFrame.setStompCommand("ERROR");
        Map<String , String> headers = new HashMap<>();
        headers.put("message" , errorMsg+"");
        sendFrame.setHeader(headers);
        sendFrame.setFrameBody("");

        return sendFrame;
    }
}
