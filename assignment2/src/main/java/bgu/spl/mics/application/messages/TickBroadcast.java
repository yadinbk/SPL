package bgu.spl.mics.application.messages;

import bgu.spl.mics.Broadcast;

public class TickBroadcast implements Broadcast {

    private int currTime;
    private boolean timeOut;

    public TickBroadcast(int currTime){
        this.currTime = currTime;
        this.timeOut = false;
    }

    public int getCurrTime() {
        return currTime;
    }
    public  void setTimeOut(boolean timeOut){
        this.timeOut = timeOut;
    }
    public boolean isTimeout(){
        return timeOut;
    }

}
