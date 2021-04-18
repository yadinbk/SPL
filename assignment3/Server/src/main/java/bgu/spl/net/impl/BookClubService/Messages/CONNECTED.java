package bgu.spl.net.impl.BookClubService.Messages;

import bgu.spl.net.impl.BookClubService.Frame;
import bgu.spl.net.impl.BookClubService.StompFrame;

import java.util.HashMap;
import java.util.Map;

public class CONNECTED implements Frame {

    private String version;

    public CONNECTED(String version) {
        this.version = version;
    }

    @Override
    public int getOperationCode() {
        return -3;
    }

    @Override
    public StompFrame getBuiltFrame() {
        StompFrame sendFrame = new StompFrame();
        sendFrame.setStompCommand("CONNECTED");
        Map<String , String> headers = new HashMap<>();
        headers.put("version" , version);

        sendFrame.setHeader(headers);
        sendFrame.setFrameBody("");

        return sendFrame;
    }
}
