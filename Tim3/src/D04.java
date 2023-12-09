import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import utils.InputFile;

class Card{
    int id;
    List<Integer> winningNumbers;
    List<Integer> numbers;
    int amount;
    Card(int id){
        this.id = id;
        this.winningNumbers = new ArrayList<>();
        this.numbers = new ArrayList<>();
        this.amount = 1;
    }
    int calcPoints(){
        int points = 0;
        for (int num : this.numbers){
            if (this.winningNumbers.contains(num)){
                if (points == 0){
                    points = 1;
                }else{
                    points *= 2;
                }
            }
        }
        return points;
    }
    int getWins(){
        int wins = 0;
        for (int num : this.numbers){
            if (this.winningNumbers.contains(num)) wins++;
        }
        return wins;
    }
}

public class D04 {
    public static void main(String[] args) {
        List<String> raw = InputFile.readFile("./Tim3/src/input/04.txt");
        //List<String> raw = InputFile.readFile("./Tim3/src/input/04Sample.txt");
        List<Card> cards = new ArrayList<>();
        Pattern cardPattern = Pattern.compile("Card\\s+(?<id>\\d+):\\s+(?<winning>[\\d\\s]+)\\s+\\|\\s+(?<numbers>[\\d\\s]+)");
        for (String line: raw){
            Matcher matcher = cardPattern.matcher(line);
            if (!matcher.find()){
                System.out.println("No match <"+line+">");
                continue;
            }
            int id = Integer.parseInt(matcher.group("id"));
            Card card = new Card(id);
            String[] winningNumbers = matcher.group("winning").split("\\s+");
            for (String num : winningNumbers){
                card.winningNumbers.add(Integer.parseInt(num));
            }
            String[] numbers = matcher.group("numbers").split("\\s+");
            for (String num : numbers){
                card.numbers.add(Integer.parseInt(num));
            }
            cards.add(card);
        }

        int p1Solution = 0;
        for (Card card : cards){
            p1Solution += card.calcPoints();
        }
        System.out.println("Solution part 1: " + p1Solution);

        int p2Solution = 0;
        for (int i=0; i<cards.size(); i++){
            Card card = cards.get(i);
            int wins = card.getWins();
            for (int n = 0; n<card.amount; n++){
                for (int j = i+1; j<=i+wins; j++){
                    cards.get(j).amount++;
                }
            }
            p2Solution += card.amount;
        }

        System.out.println("Solution part 2: " + p2Solution);

    }
}
