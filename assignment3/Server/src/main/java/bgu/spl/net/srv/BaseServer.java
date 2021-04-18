package bgu.spl.net.srv;

import bgu.spl.net.api.MessageEncoderDecoder;
import bgu.spl.net.api.MessagingProtocol;
import bgu.spl.net.api.StompMessagingProtocol;
import bgu.spl.net.impl.BookClubService.BCStompEncoderDecoder;
import bgu.spl.net.impl.BookClubService.BCStompProtocol;
import bgu.spl.net.impl.BookClubService.Frame;
import bgu.spl.net.impl.ConnectionsImpl;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.function.Supplier;

public abstract class BaseServer<T> implements Server<T> {

    private final int port;
    private final Supplier<BCStompProtocol> protocolFactory;
    private final Supplier<BCStompEncoderDecoder> encdecFactory;
    private ServerSocket sock;
    private final ConnectionsImpl<T> clients;


    public BaseServer(
            int port,
            Supplier<BCStompProtocol> protocolFactory,
            Supplier<BCStompEncoderDecoder> encdecFactory) {

        this.port = port;
        this.protocolFactory = protocolFactory;
        this.encdecFactory = encdecFactory;
		this.sock = null;
        this.clients = new ConnectionsImpl<>();

    }

    @Override
    public void serve() {

        try (ServerSocket serverSock = new ServerSocket(port)) {


            this.sock = serverSock; //just to be able to close

            while (!Thread.currentThread().isInterrupted()) {

                Socket clientSock = serverSock.accept();

                BCStompProtocol protocol = protocolFactory.get();

                BlockingConnectionHandler<T> handler = new BlockingConnectionHandler<T>(
                        clientSock,
                        encdecFactory.get(),
                        protocol
                );
                AtomicInteger id = new AtomicInteger(clients.add((ConnectionHandler<Frame>) handler));

                protocol.start(id.get(), clients);

                execute(handler);
            }
        } catch (IOException ex) {
        }

    }

    @Override
    public void close() throws IOException {
		if (sock != null)
			sock.close();
		clients.disconnectAll();
    }

    protected abstract void execute(BlockingConnectionHandler<T>  handler);

}
