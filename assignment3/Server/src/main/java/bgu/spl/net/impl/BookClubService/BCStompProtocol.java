package bgu.spl.net.impl.BookClubService;

import bgu.spl.net.api.StompMessagingProtocol;
import bgu.spl.net.impl.BookClubService.Messages.*;
import bgu.spl.net.impl.ConnectionsImpl;
import bgu.spl.net.srv.Connections;

import java.util.HashMap;
import java.util.Map;

public class BCStompProtocol implements StompMessagingProtocol {

    private boolean shouldTerminate;
    private Connections connections;
    private int connectionId;
    private Database database;
    private int msgId;

    public BCStompProtocol(Database database) {
        this.database = database;
        this.shouldTerminate = false;
    }


    @Override
    public void start(int connectionId, Connections<Frame> connections) {
        this.connections = connections;
        this.connectionId = connectionId;
        database.newConnection(connections, connectionId);
    }

    @Override
    public void process(String message) {

        StompFrame frame = new StompFrame(message);
        Frame send = null;

        switch (frame.getOperationCode()) {
            case 1: // CONNECT
                Connect connect = new Connect(frame);
                send = database.connect(connect, connectionId).getBuiltFrame();
                break;


            case 2: // SUBSCRIBE

                Subscribe subscribe = new Subscribe(frame);
                send = database.subscribe(subscribe, connectionId).getBuiltFrame();

                break;

            case 3: // SEND
                Send s = new Send(frame);
                String subId = "";
                connections.send(s.getGenre(), frame); // TODO Meybe need connectionId to save the user, because we need to return the book to the original user

                break;

            case 4: // DISCONNECT
                Disconnect disconnect = new Disconnect(frame);
                send = database.logout(disconnect, connectionId).getBuiltFrame();
                connections.disconnect(connectionId, send);
                shouldTerminate = true;
                break;

            case 5: //  UNSEBSCRIBE
                Unsubscribe unsubscribe = new Unsubscribe(frame);
                database.exit(unsubscribe, connectionId).getBuiltFrame();
                break;

        }

        if (send != null && frame.getOperationCode() != 4) {
            connections.send(connectionId, send);
        }


    }


    @Override
    public boolean shouldTerminate() {
        return shouldTerminate;
    }
}
