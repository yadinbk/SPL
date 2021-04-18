package bgu.spl.mics.application.messages;

import bgu.spl.mics.Event;

import java.util.List;

public class MissionReceivedEvent implements Event<Boolean> {


    private String missionName;
    private List<String> agentsSerial;
    private String gadget;
    private int duration;
    private int timeExpired;
    private int timeIssued;


    public MissionReceivedEvent(String missionName) {
        this.missionName = missionName;
    }

    public String getMissionName() {
        return missionName;
    }

    public void setMissionName(String missionName) {
        this.missionName = missionName;
    }

    public List<String> getAgentsSerial() {
        return agentsSerial;
    }

    public void setAgentsSerial(List<String> agentsSerial) {
        this.agentsSerial = agentsSerial;
    }

    public String getGadget() {
        return gadget;
    }

    public void setGadget(String gadget) {
        this.gadget = gadget;
    }

    public int getDuration() {
        return duration;
    }

    public void setDuration(int duration) {
        this.duration = duration;
    }

    public int getTimeExpired() {
        return timeExpired;
    }

    public void setTimeExpired(int timeExpired) {
        this.timeExpired = timeExpired;
    }

    public int getTimeIssued() {
        return timeIssued;
    }

    public void setTimeIssued(int timeIssued) {
        this.timeIssued = timeIssued;
    }
}
