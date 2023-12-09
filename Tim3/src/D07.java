import java.util.ArrayList;
import java.util.List;

import utils.InputFile;

import java.util.HashMap;

class Hand implements Comparable<Hand>{
    char[] cards;
    int bid;
    int type;
    Hand(char[] cards, int bid){
        this.cards = cards;
        this.bid = bid;
        this.type = getType();
    }
    int getCardValue(char card){
        switch (card){
            case 'T': return 10;
            case 'J': return 11;
            case 'Q': return 12;
            case 'K': return 13;
            case 'A': return 14;
            default: return Character.getNumericValue(card);
        }
    }
    int getType(){
        HashMap<Character, Integer> cardCount = new HashMap<>();
        for (char card: cards){
            if (cardCount.containsKey(card)){
                cardCount.put(card, cardCount.get(card)+1);
            }else{
                cardCount.put(card, 1);
            }
        }
        if (cardCount.size() == 1) return 7; // Five of a kind
        if (cardCount.size() == 2) {
            for (char card: cardCount.keySet()){
                if (cardCount.get(card) == 4 || cardCount.get(card) == 1) return 6; // Four of a kind
                if (cardCount.get(card) == 2 || cardCount.get(card) == 3) return 5; // Full house
            }
        }
        if (cardCount.size() == 3) {
            for (char card: cardCount.keySet()){
                if (cardCount.get(card) == 3) return 4; // Three of a kind
                if (cardCount.get(card) == 2) return 3; // Two pairs
            }
        }
        if (cardCount.size() == 4) return 2; // One pair
        return 1; // High card
    }
    Hand getWinner(Hand other){
        if (this.type > other.type) return this;
        if (this.type < other.type) return other;
        // this.type == other.type
        for (int i=0; i<5; i++){
            if (this.getCardValue(this.cards[i]) > this.getCardValue(other.cards[i])) return this;
            if (this.getCardValue(this.cards[i]) < this.getCardValue(other.cards[i])) return other;
        }
        throw new Error("Invalid hands");
        //return null;
    }
    public int compareTo(Hand other){
        if (this == this.getWinner(other)) return 1;
        else return -1;
    }
    public String toString(){
        String result = "";
        for (char card: cards){
            result += card;
        }
        return "<cards: "+result+", bid: "+bid+", type: "+type+">";
    }
}

class HandP2 extends Hand{
    HandP2(char[] cards, int bid){
        super(cards, bid);
    }
    @Override
    int getCardValue(char card){
        switch (card){
            case 'T': return 10;
            case 'J': return 1;
            case 'Q': return 12;
            case 'K': return 13;
            case 'A': return 14;
            default: return Character.getNumericValue(card);
        }
    }
    @Override
    int getType(){
        HashMap<Character, Integer> cardCount = new HashMap<>();
        for (char card: this.cards){
            if (cardCount.containsKey(card)){
                cardCount.put(card, cardCount.get(card)+1);
            }else{
                cardCount.put(card, 1);
            }
        }
        if (cardCount.size() == 1) return 7; // Five of a kind
        Integer jokerCount = cardCount.get('J');
        if (jokerCount == null) jokerCount = 0;
        if (cardCount.size() == 2) {
            if (jokerCount >= 1) return 7; // Five of a kind with joker
            // No Jokers in hand, two types of cards
            for (char card: cardCount.keySet()){
                if (cardCount.get(card) == 4 || cardCount.get(card) == 1) return 6; // Four of a kind
                if (cardCount.get(card) == 2 || cardCount.get(card) == 3) return 5; // Full house
            }
        }
        if (cardCount.size() == 3) {
            if (jokerCount >= 2) return 6; // Four of a kind with joker
            for (char card: cardCount.keySet()){
                if (cardCount.get(card) == 3) {
                    if (jokerCount == 1) return 6; // Four of a kind with joker
                    return 4; // Three of a kind
                }
                if (cardCount.get(card) == 2) {
                    if (jokerCount == 1) return 5; // Full house with joker
                    return 3; // Two pairs
                }
            }
        }
        if (cardCount.size() == 4) {
            if (jokerCount >= 1) return 4; // Three of a kind with joker
            // No Jokers in hand, four types of cards
            for (char card: cardCount.keySet()){
                if (cardCount.get(card) == 2) return 2; // One pair
            }
        }
        if (jokerCount >= 1) return 2; // One pair with joker
        return 1; // High card

    }

}

public class D07 {
    static List<String> raw;
    static List<Hand> hands;
    static void parseInput(){
        raw = InputFile.readFile("./Tim3/src/input/07.txt");
        //raw = InputFile.readFile("./Tim3/src/input/07Sample.txt");
        hands = new ArrayList<>();
        for (String line: raw){
            String[] tmp = line.split(" ");
            char[] cards = new char[5];
            for (int i=0; i<tmp[0].length(); i++){
                cards[i] = tmp[0].charAt(i);
            }
            int bid = Integer.parseInt(tmp[1]);
            hands.add(new Hand(cards, bid));
        }
    }
    static int part1(){
        hands.sort(null);
        int result = 0;
        for (int i=0; i<hands.size(); i++){
            Hand hand = hands.get(i);
            result += hand.bid*(i+1);
        }
        return result;
    }
    static int part2(){
        List<HandP2> handsP2 = new ArrayList<>();
        for (Hand hand: hands){
            handsP2.add(new HandP2(hand.cards, hand.bid));
        }
        handsP2.sort(null);
        int result = 0;
        for (int i=0; i<handsP2.size(); i++){
            Hand hand = handsP2.get(i);
            result += hand.bid*(i+1);
        }
        return result;
    }
    public static void main(String[] args) {
        parseInput();
        System.out.println("Part 1: "+part1());
        System.out.println("Part 2: "+part2());
    }

}
