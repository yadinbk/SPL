package bgu.spl.mics.application.messages;

import bgu.spl.mics.Event;

public class GadgetAvailableEvent implements Event<Boolean>{
    private String gadget;
    private int QTime;


    public int getQTime() {
        return QTime;
    }

    public void setQTime(int QTime) {
        this.QTime = QTime;
    }


    public void setGadget(String gadget) {
        this.gadget = gadget;
    }

    public GadgetAvailableEvent(String gadget) {
        this.gadget = gadget;


    }

    public String getGadget() {
        return gadget;
    }

}
