package bgu.spl.net.impl.BookClubService;

import bgu.spl.net.impl.BookClubService.Messages.*;
import bgu.spl.net.impl.ConnectionsImpl;
import bgu.spl.net.srv.Connections;

import java.util.*;

public class Database {
    private Map<Integer , User> users;
    private Map<Integer, User> activeUsers;
    private Map<String, ArrayList<String>> genreBySubIdMap;
    private Map<String, ArrayList<Integer>> genreByConnectionId;

    private  ConnectionsImpl<Frame> connections = null;

    private Database(){
        users = new HashMap<>();
        activeUsers = new HashMap<>();
        genreBySubIdMap = new HashMap<>();
        genreByConnectionId = new HashMap<>();
    }



    private static class DatabaseHolder{
        private static Database instance = new Database();
    }


    public Frame connect(Connect connect, int connectionId){
        String name = connect.getUsername();
        String password = connect.getPassword();
        for(Map.Entry<Integer,User> entry : users.entrySet()){
            User u = entry.getValue();
            if(name != null && name.equals(u.getUserName())){ // users exists in the system
                if(password != null && password.equals(u.getPassword())) {
                    if (u.isLoggedIn()) {
                        ERROR error = new ERROR("User is already logged in");
                        return error;
                    }
                    else{
                        u.setId(connectionId);
                        u.setLoggedIn(true);
                        CONNECTED connected = new CONNECTED(connect.getVersion());
                        return connected; // user exists in the system but has disconnected
                    }
                }
                else {
                    ERROR error = new ERROR("Password is incorrect");
                    return error;
                }
            }
        }
        // user is not in the system
        User user = new User(name, password, connectionId);
        users.put(connectionId ,user);
        activeUsers.put(connectionId , user);
        CONNECTED connected = new CONNECTED(connect.getVersion());
        return connected; // user has been created
    }


    public Frame subscribe(Subscribe subscribe, int connectionId){
        String genre = subscribe.getGenre();
        String subId = subscribe.getSubId();
        String receipt = subscribe.getReceipt();
        boolean newGenre = true;

        User user = locateUserById(connectionId);
        if(user == null) {
            return new ERROR("the user hasnt connected in the first place"); // user hasnt logged into the system
        }
        if(user.getGenreById().values().contains(genre)) {
            return new RECEIPT(receipt); // user is already subed to genre [SHOULD HAVE NO EFFECT - NO ERROR]
        }
        user.getGenreById().put(subId, genre);
        for(Map.Entry<String , ArrayList<String>> entry : genreBySubIdMap.entrySet()){
            if(entry.getKey().equals(genre)) {
                genreBySubIdMap.get(genre).add(subId);
                genreByConnectionId.get(genre).add(user.getId());
                newGenre = false;
            }
        }
        if(newGenre) {
            ArrayList<String> subIds = new ArrayList<>();
            ArrayList<Integer> connectionsId = new ArrayList<>();
            connectionsId.add(user.getId());
            subIds.add(subId);
            genreBySubIdMap.put(genre,subIds);
            genreByConnectionId.put(genre , connectionsId);
        }
        return new RECEIPT(receipt);

    }


    public Frame exit(Unsubscribe unsubscribe , int connectionId){
        String subId = unsubscribe.getSubId();

        User user = locateUserById(connectionId);
        String genre = user.getGenreById().get(subId);

        if(user == null) return new ERROR("the user hasnt connected in the first place");
        for(Map.Entry<String , String> entry : user.getGenreById().entrySet()){
            if(entry.getValue().equals(genre)) {
                genreByConnectionId.get(genre).remove(user.getId());
                genreBySubIdMap.get(genre).remove(subId);
                user.getGenreById().remove(entry);
                return new RECEIPT(subId);
            }
        }
        return new RECEIPT(subId); // user is not subed for topic [not error]

    }

    public void newConnection(Connections<Frame> connections, int connectionId) {
        if(connections == null)
            this.connections = (ConnectionsImpl) connections;
    }

    public Frame logout(Disconnect disconnect , int connectionId) {
        String receipt = disconnect.getReceiptId();
        User user = locateUserById(connectionId);
        if(user == null) return new ERROR("the user hasnt connected in the first place");
        activeUsers.remove(user);
        user.setLoggedIn(false);
        return new RECEIPT(receipt);
    }


    public User locateUserById(int connectionId) {
        for(Map.Entry<Integer,User> entry : users.entrySet()) {
            if(connectionId == entry.getValue().getId())
                return entry.getValue();
        }
        return null;
    }
    public static Database getInstance(){
        return DatabaseHolder.instance;
    }



    public Map<Integer, User> getActiveUsers() {
        return activeUsers;
    }


    public ArrayList<Integer> getConnectionsByGenre(String topic) {
        return genreByConnectionId.get(topic);
    }
}