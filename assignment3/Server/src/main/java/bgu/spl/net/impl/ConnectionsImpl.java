package bgu.spl.net.impl;

import bgu.spl.net.impl.BookClubService.Database;
import bgu.spl.net.impl.BookClubService.Frame;
import bgu.spl.net.impl.BookClubService.Messages.MESSAGE;
import bgu.spl.net.impl.BookClubService.StompFrame;
import bgu.spl.net.impl.BookClubService.User;
import bgu.spl.net.srv.ConnectionHandler;
import bgu.spl.net.srv.Connections;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class ConnectionsImpl<T> implements Connections<Frame> {

        //        private List<ConnectionHandler> connectionHandlerList;
        private HashMap<Integer , ConnectionHandler<Frame>> clients;
        private AtomicInteger connectionId;
        private Database database = Database.getInstance();
        private ReadWriteLock lock;
        private AtomicInteger msgId;



        public ConnectionsImpl(){
                clients = new HashMap<>();
                connectionId = new AtomicInteger(0);
                lock = new ReentrantReadWriteLock();
                msgId = new AtomicInteger(0);
        }


        @Override
        public boolean send(int connectionId, Frame msg) {
                try{
                        lock.readLock().lock();
                        ConnectionHandler<Frame> handler = clients.get(connectionId);
                        lock.readLock().unlock();
                        handler.send(msg);
                        return true;
                }catch (Exception e){
                        return false;
                }
        }

        @Override
        public void send(String topic, Frame msg) {

                lock.readLock().lock();
                ArrayList<Integer> subs = database.getConnectionsByGenre(topic);
                Map<Integer , User> activeUser = database.getActiveUsers();
                if(subs != null) {
                        for (int id : subs) {
                                if(clients.get(id) != null) {
                                        MESSAGE sendF = new MESSAGE((StompFrame) msg, id + "", msgId.getAndIncrement());
                                        StompFrame sendStompFrame = sendF.getBuiltFrame();
                                        if(sendStompFrame != null)
                                        clients.get(id).send(sendStompFrame);
                                }

                        }
                }
                lock.readLock().unlock();
        }


        @Override
        public void disconnect(int connectionId , Frame msg) {
                lock.writeLock().lock();
                ConnectionHandler<Frame> handler = clients.remove(connectionId);
                handler.send(msg);
                lock.writeLock().unlock();
        }

        @Override
        public int add(ConnectionHandler<Frame> handler) {
                connectionId.getAndIncrement();
                this.clients.put(connectionId.get(), (ConnectionHandler<Frame>) handler);
                return connectionId.get();
        }


        public void disconnectAll() {
                lock.writeLock().lock();
                for (ConnectionHandler<Frame> tConnectionHandler : clients.values())
                        try {
                                tConnectionHandler.close();
                        }
                        catch (IOException ignored) {
                        }
                clients.clear();
                lock.writeLock().unlock();
        }
}
