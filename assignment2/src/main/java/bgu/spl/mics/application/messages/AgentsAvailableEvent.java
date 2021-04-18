package bgu.spl.mics.application.messages;

import bgu.spl.mics.Event;
import bgu.spl.mics.Future;

import java.util.List;

public class AgentsAvailableEvent implements Event<Boolean>{
    private List<String> agentSerials;
    private List<String> agentNames;
    private int ID;
    private int duration;
    private Future<Boolean> isActiveMission;

    public void setID(int ID) {
        this.ID = ID;
    }

    public int getID() {
        return ID;
    }

    public List<String> getAgentNames() {
        return agentNames;
    }

    public void setAgentNames(List<String> agentNames) {
        this.agentNames = agentNames;
    }


    public AgentsAvailableEvent(List<String> agentSerials, int duration) {
        this.agentSerials = agentSerials;
        this.duration = duration;
        this.isActiveMission = new Future<>();
    }

    public List<String> getAgentSerials() {
        return agentSerials;
    }

    public void setAgentSerials(List<String> agentSerials) {
        this.agentSerials = agentSerials;
    }

    public boolean isActiveMission()
    {
        return isActiveMission.get();
    }

    public void setActiveMission(boolean activeMission) {
        isActiveMission.resolve(activeMission);
    }


    public int getDuration() {
        return duration;
    }


}
