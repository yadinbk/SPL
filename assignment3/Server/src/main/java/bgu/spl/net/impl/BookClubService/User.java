package bgu.spl.net.impl.BookClubService;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class User {
    private int id;
    private String userName;
    private String password;
    private boolean loggedIn;
    private List<String> genres;
    private HashMap<String, String> genreById;

    public User() {
        this.genreById = new HashMap<>();
        loggedIn = true;
    }

    public User(String userName , String password , int id) {
        this.id = id;
        this.userName = userName;
        this.password = password;
        this.loggedIn = true;
        this.genres = new ArrayList<>();
        this.genreById = new HashMap<>();
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getUserName() {
        return userName;
    }

    public void setUserName(String userName) {
        this.userName = userName;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public boolean isLoggedIn() {
        return loggedIn;
    }

    public void setLoggedIn(boolean loggedIn) {
        this.loggedIn = loggedIn;
    }

    public List<String> getGenres() {
        return genres;
    }

    public void setGenres(List<String> genres) {
        this.genres = genres;
    }

    public HashMap<String, String> getGenreById() {
        return genreById;
    }

    public void setGenreById(HashMap<String, String> genreById) {
        this.genreById = genreById;
    }


}
