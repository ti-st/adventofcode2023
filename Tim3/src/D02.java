import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import utils.InputFile;

class Game{
    public int id;
    public List<Integer> r, g, b;
    Game(int id){
        this.id = id;
        this.r = new ArrayList<>();
        this.g = new ArrayList<>();
        this.b = new ArrayList<>();
    }
    void addR(int v){
        this.r.add(v);
    }
    void addG(int v){
        this.g.add(v);
    }
    void addB(int v){
        this.b.add(v);
    }
    boolean isValid(){
        for (int val : this.r) {
            if (val > 12) return false;
        }
        for (int val : this.g) {
            if (val > 13) return false;
        }
        for (int val : this.b) {
            if (val > 14) return false;
        }
        return true;
    }
    int power(){
        int maxR = 0;
        int maxG = 0;
        int maxB = 0;
        for (Integer val : this.r) {
            if (val > maxR) maxR = val;
        }
        for (Integer val : this.g) {
            if (val > maxG) maxG = val;
        }
        for (Integer val : this.b) {
            if (val > maxB) maxB = val;
        }
        return maxR*maxG*maxB;
    }
}

public class D02 {
    static List<Game> parseInput(List<String> raw){
        String gamePatStr = "Game (?<id>\\d+): (?<content>.*)";
        String colorPatStr = "(?<val>\\d+) (?<color>(?>red|green|blue)),?;?";
        Pattern colorPat = Pattern.compile(colorPatStr);
        Pattern pattern = Pattern.compile(gamePatStr);
        List<Game> games = new ArrayList<>();
        for (String line : raw) {
            //System.out.println(line);
            Matcher matcher = pattern.matcher(line);
            if (!matcher.find()){
                System.out.println("No match <"+line+">");
                continue;
            }
            int id = Integer.parseInt(matcher.group("id"));
            Game game = new Game(id);
            Matcher colMatcher = colorPat.matcher(matcher.group("content"));
            while (colMatcher.find()){
                int val = Integer.parseInt(colMatcher.group("val"));
                String color = colMatcher.group("color");
                switch (color){
                    case "red":
                        game.addR(val);
                        break;
                    case "green":
                        game.addG(val);
                        break;
                    case "blue":
                        game.addB(val);
                        break;
                    default:
                        System.out.println("Unknown color <"+color+">");
                }
            }
            games.add(game);
            //System.out.println(id+"-"+matcher.group("content"));
        }
        return games;
    }

    public static void main(String[] args){
        List<String> raw = InputFile.readFile("./Tim3/src/input/02.txt");
        List<Game> games = parseInput(raw);
        int p1Solution = 0;
        for (Game game : games) {
            if (game.isValid()) p1Solution+=game.id;
        }
        System.out.println("Solution part 1: " + p1Solution);

        int p2Solution = 0;
        for (Game game : games) {
            p2Solution+=game.power();
        }
        System.out.println("Solution part 2: " + p2Solution);
    }
}
