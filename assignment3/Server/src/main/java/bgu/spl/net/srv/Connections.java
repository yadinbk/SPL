package bgu.spl.net.srv;


import java.io.IOException;

public interface Connections<T> {

    boolean send(int connectionId, T msg);

    void send(String topic, T msg); //topic instead of chanel

    void disconnect(int connectionId , T msg);

    int add(ConnectionHandler<T> handler);

}
