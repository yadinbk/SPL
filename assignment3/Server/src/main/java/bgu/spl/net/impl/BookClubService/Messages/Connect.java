package bgu.spl.net.impl.BookClubService.Messages;

import bgu.spl.net.impl.BookClubService.Database;
import bgu.spl.net.impl.BookClubService.Frame;
import bgu.spl.net.impl.BookClubService.StompFrame;
import bgu.spl.net.impl.ConnectionsImpl;
import bgu.spl.net.srv.Connections;

public class Connect {

    private StompFrame frame;
    private String username;
    private String password;
    private String version;


    public Connect(StompFrame frame){
//        System.out.println("Connect / : " +" ^^^^^");
        this.frame = frame;
        this.username = frame.getHeader().get("login");
        this.password = frame.getHeader().get("passcode");
        this.version = frame.getHeader().get("accept-version");
    }


    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getVersion() {
        return version;
    }
}
