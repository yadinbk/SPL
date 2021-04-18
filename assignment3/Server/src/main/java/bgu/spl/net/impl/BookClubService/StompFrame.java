package bgu.spl.net.impl.BookClubService;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public  class StompFrame implements Frame{
    private String stompCommand;
    private Map<String , String> header;
    private String frameBody;
    private int opCode;


    public StompFrame(String msg){
        initialize(msg);
    }

    private void initialize(String msg) {
        String [] lines = msg.split("\n");

        if(lines[0].equals("")) {
            lines = weirdBugFix(lines);
        }
        this.stompCommand = lines[0];
        this.header = new HashMap<>();
        int numOfCurrLine = 1;
        while (numOfCurrLine<lines.length&& !lines[numOfCurrLine].equals("")){
            String [] headerLine = lines[numOfCurrLine].split(":");
            if(headerLine.length == 2) {
                header.put(headerLine[0], headerLine[1]);
                numOfCurrLine++;
            }
        }
        if(numOfCurrLine < lines.length)
        frameBody = lines[numOfCurrLine  + 1];
        else frameBody = "";
        setOpCode(lines[0]);
    }

    private String[] weirdBugFix(String[] lines) {
        String [] newLines = new String[lines.length-1];
        for (int i = 0 ; i < lines.length ; i++ ){
            if(i != lines.length-1)
                newLines[i] = lines[i+1];
        }
        return newLines;
    }


    public String getStompCommand() {
        return stompCommand;
    }

    public void setStompCommand(String stompCommand) {
        this.stompCommand = stompCommand;
    }



    public Map<String, String> getHeader() {
        return header;
    }

    public void setHeader(Map<String, String> header) {
        this.header = header;
    }

    public String getFrameBody() {
        return frameBody;
    }

    public void setFrameBody(String frameBody) {
        this.frameBody = frameBody;
    }

    public StompFrame(){
        header = new HashMap<>();

    }

    @Override
    public String toString() {
        String headerS = "";
        for (Map.Entry<String , String> entry : header.entrySet()) {
            headerS += entry.getKey() + ":" + entry.getValue() + "\n";
        }
        return stompCommand + "\n" + headerS + "\n"+frameBody;
    }

    private void setOpCode(String stompCommand) {
        if(stompCommand.equals("CONNECT")) opCode = 1;
        else if (stompCommand.equals("SUBSCRIBE")) opCode = 2;
        else if (stompCommand.equals("SEND")) opCode = 3;
        else if (stompCommand.equals("DISCONNECT")) opCode = 4;
        else if (stompCommand.equals("UNSUBSCRIBE")) opCode = 5;

    }

    @Override
    public int getOperationCode() {
        return opCode;
    }

    @Override
    public StompFrame getBuiltFrame() {
        return null;
    }
}
