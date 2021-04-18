package bgu.spl.mics.application;

import bgu.spl.mics.MessageBrokerImpl;
import bgu.spl.mics.application.passiveObjects.Diary;
import bgu.spl.mics.application.passiveObjects.Inventory;
import bgu.spl.mics.application.passiveObjects.Squad;
import bgu.spl.mics.application.publishers.TimeService;
import bgu.spl.mics.application.subscribers.Intelligence;
import bgu.spl.mics.application.subscribers.M;
import bgu.spl.mics.application.subscribers.Moneypenny;
import bgu.spl.mics.application.subscribers.Q;
import com.google.gson.Gson;
import com.google.gson.stream.JsonReader;

import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/** This is the Main class of the application. You should parse the input file,
 * create the different instances of the objects, and run the system.
 * In the end, you should output serialized objects.
 */
public class MI6Runner {
    public static void main(String[] args) throws IOException {
        Gson gson = new Gson();
        JsonReader reader = new JsonReader(new FileReader(args[0]));
        GsonObject gsonObject = gson.fromJson(reader , GsonObject.class);
        Inventory inventory = Inventory.getInstance();
        inventory.load(gsonObject.inventory);
        Squad squad = Squad.getInstance();
        squad.load(gsonObject.squad);
        int numberOfThreads = gsonObject.services.M + gsonObject.services.Moneypenny + gsonObject.services.intelligence.length + 2;
        ExecutorService tp = Executors.newFixedThreadPool(numberOfThreads);
        MessageBrokerImpl messageBroker = (MessageBrokerImpl) MessageBrokerImpl.getInstance();

        for (int i = 0 ; i < gsonObject.services.M ; i++){
            M m = new M(i+1);
            tp.execute(m);
        }

        for (int i = 0 ; i < gsonObject.services.Moneypenny ; i++){
            Moneypenny moneypenny = new Moneypenny(i+1);
            tp.execute(moneypenny);
        }

        for (int i = 0 ; i < gsonObject.services.intelligence.length ; i++){
            Intelligence intelligence = new Intelligence(gsonObject.services.intelligence[i].getMissions(), i+1);
            tp.execute(intelligence);
        }

        Q q = new Q();
        tp.execute(q);

        TimeService ts = new TimeService(gsonObject.services.time);
        tp.execute(ts);

        try {
            Thread.sleep(100*(gsonObject.services.time+2));
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        Inventory.getInstance().printToFile("inventoryOutputFile.json");
        try {
            Diary.getInstance().printToFile("diaryOutputFile.json");
        } catch (IOException e) {
            e.printStackTrace();
        }

        System.exit(0);


    }
}
