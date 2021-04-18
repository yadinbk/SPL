package bgu.spl.net.impl.BookClubService;

public interface Frame {
    int getOperationCode();
    StompFrame getBuiltFrame();
}
