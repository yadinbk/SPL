package bgu.spl.net.impl.stomp;

import bgu.spl.net.impl.BookClubService.BCStompEncoderDecoder;
import bgu.spl.net.impl.BookClubService.BCStompProtocol;
import bgu.spl.net.impl.BookClubService.Database;
import bgu.spl.net.srv.Server;

import java.util.HashMap;
import java.util.Map;

public class StompServer {

    public static void main(String[] args) {

        Database database = Database.getInstance();

        if (args.length != 0) {
            if (args[1].equals("tpc")) {
                Server.threadPerClient(
                        Integer.parseInt(args[0]), //port
                        () -> new BCStompProtocol(database), //protocol factory
                        BCStompEncoderDecoder::new //message encoder decoder factory
                ).serve();
            }
            if (args[1].equals("reactor")) {

                Server.reactor(
                        Runtime.getRuntime().availableProcessors(),
                        Integer.parseInt(args[0]), //port
                        () -> new BCStompProtocol(database), //protocol factory
                        BCStompEncoderDecoder::new//message encoder decoder factory
                ).serve();

            }
        } else {
            Server.threadPerClient(
                    7878, //port
                    () -> new BCStompProtocol(database), //protocol factory
                    BCStompEncoderDecoder::new //message encoder decoder factory
            ).serve();
        }

    }
}
